#include <unity.h>
#include "app/SetlistManager.h"
#include "app/DiContainer.h"
#include "app/Context.h"
#include "app/EditSetlistState.h"
#include "app/SetlistMenuState.h"
#include "app/MenuController.h"
#include "mocks/MockInput.h"
#include "mocks/MockProgramSelector.h"
#include "mocks/MockProgramsBank.h"
#include "mocks/MockEditSetlistView.h"
#include "mocks/MockMenuLayoutView.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockStateMachine.h"

void setUp(void) {
    // Set up code here, to run before each test
}

void tearDown(void) {
    // Clean up code here, to run after each test
}

/**
 * Full integration test simulating the complete hardware flow:
 * main.cpp setup → EditSetlistState changes program → SetlistMenuState reads new value
 * 
 * This test verifies the complete data flow from SetlistManager through Context to menu display.
 * 
 * Critical end-to-end behavior:
 * - SetlistManager created
 * - Injected into DiContainer
 * - Context receives SetlistManager pointer
 * - Edit operation updates SetlistManager
 * - Menu operation reads updated data through Context
 */
void testShouldWireSetlistManagerThroughEntireStack(void) {
    // ARRANGE: Simulate main.cpp setup - create all required dependencies
    
    // 1. Create SetlistManager with initial data (mimics main.cpp initialization)
    SetlistManager setlistManager;
    TEST_ASSERT_EQUAL(0, setlistManager.getProgram(0));    // Initial: program 0
    TEST_ASSERT_EQUAL(41, setlistManager.getProgram(1));   // Initial: program 41
    TEST_ASSERT_EQUAL(112, setlistManager.getProgram(2));  // Initial: program 112
    
    // 2. Create Context and wire SetlistManager (mimics main.cpp setup)
    Context context;
    context.setSetlistManager(&setlistManager);
    TEST_ASSERT_EQUAL(setlistManager.getPrograms(), context.programs);
    TEST_ASSERT_EQUAL(3, context.programsCount);
    
    // 3. Create all mocks and real dependencies
    MockInput mockInput;
    MockProgramSelector mockProgramSelector;
    MockProgramsBank mockProgramsBank;
    MockEditSetlistView mockEditSetlistView;
    MockMenuLayoutView mockMenuLayoutView;
    MockStateFactory mockStateFactory;
    MockStateMachine mockStateMachine;
    
    // Set up programs in bank (needed for display)
    mockProgramsBank.addProgram(0, "Clean");
    mockProgramsBank.addProgram(5, "NewProg");
    mockProgramsBank.addProgram(41, "Viola");
    mockProgramsBank.addProgram(112, "Reverse");
    
    // Set up ProgramSelector with initial data (mimics main.cpp)
    int initialPrograms[] = {0, 41, 112};
    mockProgramSelector.setPrograms(initialPrograms, 3);
    
    // 4. Create DiContainer and inject all dependencies (mimics main.cpp)
    DiContainer diContainer;
    diContainer.setSetlistManager(&setlistManager)
        ->setUserInput(&mockInput)
        ->setProgramSelector(&mockProgramSelector)
        ->setProgramsBank(&mockProgramsBank)
        ->setEditSetlistView(&mockEditSetlistView)
        ->setSetlistMenuLayoutView(&mockMenuLayoutView)
        ->setStateFactory(&mockStateFactory)
        ->setStateMachine(&mockStateMachine);
    
    // 5. Create MenuController (mimics main.cpp)
    MenuController menuController(&diContainer);
    diContainer.setSetlistMenuController(&menuController);
    
    // ACT PART 1: EditSetlistState changes program 0 from 0 to 5
    
    EditSetlistState editState(&diContainer);
    editState.enter();
    
    // Simulate user editing: change program at index 0 from 0 to 5
    // Step 1: Enter edit mode (encoder button press on first item, which is already selected)
    mockInput.setEncoderButtonPressed(true);
    editState.update();  // Enter edit mode
    mockInput.setEncoderButtonPressed(false);
    
    // Step 2: Rotate encoder clockwise 5 times to change from program 0 to program 5
    for (int i = 0; i < 5; i++) {
        mockInput.setEncoderClockwise(true);
        editState.update();  // Increment program number
        mockInput.setEncoderClockwise(false);
    }
    
    // Step 3: Save the change (encoder button press)
    mockInput.setEncoderButtonPressed(true);
    editState.update();  // Save changes - this should update SetlistManager
    mockInput.setEncoderButtonPressed(false);
    
    // ASSERT PART 1: Verify SetlistManager was updated
    TEST_ASSERT_EQUAL(5, setlistManager.getProgram(0));  // Changed from 0 to 5
    TEST_ASSERT_EQUAL(41, setlistManager.getProgram(1)); // Unchanged
    TEST_ASSERT_EQUAL(112, setlistManager.getProgram(2)); // Unchanged
    
    // ASSERT PART 2: Verify Context still points to SetlistManager's data
    TEST_ASSERT_EQUAL(setlistManager.getPrograms(), context.programs);
    TEST_ASSERT_EQUAL(5, context.programs[0]);  // Data accessible through Context
    
    // ACT PART 2: SetlistMenuState enters and reads from Context
    
    SetlistMenuState menuState(&diContainer, &context);
    menuState.enter();  // This should read from context.programs (which points to SetlistManager)
    
    // ASSERT PART 3: Verify menu displays the updated program number
    // The menu reads from context.programs during enter(), which now contains the updated value
    TEST_ASSERT_EQUAL(5, context.programs[0]);   // Menu will read this updated value
    TEST_ASSERT_EQUAL(41, context.programs[1]);  // Menu will read this
    TEST_ASSERT_EQUAL(112, context.programs[2]); // Menu will read this
    
    // Additional verification: Simulate reading the way SetlistMenuState does
    // (from SetlistMenuState::addProgramMenuItems() - lines 178-184 in SetlistMenuState.cpp)
    for (int index = 0; index < context.programsCount; index++) {
        int programNumber = context.programs[index];
        
        switch(index) {
            case 0:
                TEST_ASSERT_EQUAL(5, programNumber);  // Updated value flows through
                break;
            case 1:
                TEST_ASSERT_EQUAL(41, programNumber);
                break;
            case 2:
                TEST_ASSERT_EQUAL(112, programNumber);
                break;
        }
    }
}

/**
 * Integration test verifying edit persists when transitioning between states.
 * Tests the scenario: EditSetlistState changes program → SetlistMenuState reads it →
 * Edit state can be re-entered and shows updated value.
 */
void testShouldPersistEditAcrossStateTransitions(void) {
    // ARRANGE: Full system setup
    SetlistManager setlistManager;
    Context context;
    context.setSetlistManager(&setlistManager);
    
    MockInput mockInput;
    MockProgramSelector mockProgramSelector;
    MockProgramsBank mockProgramsBank;
    MockEditSetlistView mockEditSetlistView;
    MockMenuLayoutView mockMenuLayoutView;
    MockStateFactory mockStateFactory;
    MockStateMachine mockStateMachine;
    
    mockProgramsBank.addProgram(0, "Clean")
        ->addProgram(7, "Prog7")
        ->addProgram(41, "Viola")
        ->addProgram(112, "Reverse");
    
    int initialPrograms[] = {0, 41, 112};
    mockProgramSelector.setPrograms(initialPrograms, 3);
    
    DiContainer diContainer;
    diContainer.setSetlistManager(&setlistManager)
        ->setUserInput(&mockInput)
        ->setProgramSelector(&mockProgramSelector)
        ->setProgramsBank(&mockProgramsBank)
        ->setEditSetlistView(&mockEditSetlistView)
        ->setSetlistMenuLayoutView(&mockMenuLayoutView)
        ->setStateFactory(&mockStateFactory)
        ->setStateMachine(&mockStateMachine);
    
    MenuController menuController(&diContainer);
    diContainer.setSetlistMenuController(&menuController);
    
    // ACT: Edit program, then transition to menu state, then verify
    
    // Step 1: Edit index 0 from 0 to 7
    EditSetlistState editState(&diContainer);
    editState.enter();
    mockInput.setEncoderButtonPressed(true);
    editState.update();  // Enter edit mode
    mockInput.setEncoderButtonPressed(false);
    
    for (int i = 0; i < 7; i++) {  // Rotate to program 7
        mockInput.setEncoderClockwise(true);
        editState.update();
        mockInput.setEncoderClockwise(false);
    }
    
    mockInput.setEncoderButtonPressed(true);
    editState.update();  // Save edit
    mockInput.setEncoderButtonPressed(false);
    
    // Step 2: Transition to SetlistMenuState (simulates user navigating back)
    editState.exit();
    
    // ASSERT: SetlistManager should have the edit
    TEST_ASSERT_EQUAL(7, setlistManager.getProgram(0));
    TEST_ASSERT_EQUAL(41, setlistManager.getProgram(1));
    TEST_ASSERT_EQUAL(112, setlistManager.getProgram(2));
    
    // Step 3: SetlistMenuState should read the updated value from Context
    SetlistMenuState menuState(&diContainer, &context);
    menuState.enter();
    
    // Verify Context points to updated data
    TEST_ASSERT_EQUAL(7, context.programs[0]);   // Updated
    TEST_ASSERT_EQUAL(41, context.programs[1]);  // Original
    TEST_ASSERT_EQUAL(112, context.programs[2]); // Original
    
    // Verify the data flows correctly through the Context
    for (int index = 0; index < context.programsCount; index++) {
        int programNumber = context.programs[index];
        
        switch(index) {
            case 0:
                TEST_ASSERT_EQUAL(7, programNumber);  // The edit persisted
                break;
            case 1:
                TEST_ASSERT_EQUAL(41, programNumber);
                break;
            case 2:
                TEST_ASSERT_EQUAL(112, programNumber);
                break;
        }
    }
}

/**
 * Integration test verifying out-of-bounds edits are safely ignored throughout the stack.
 * Tests that SetlistManager bounds checking protects the entire system.
 */
void testShouldIgnoreOutOfBoundsEditsInIntegration(void) {
    // ARRANGE
    SetlistManager setlistManager;
    Context context;
    context.setSetlistManager(&setlistManager);
    
    MockInput mockInput;
    MockProgramSelector mockProgramSelector;
    MockProgramsBank mockProgramsBank;
    MockEditSetlistView mockEditSetlistView;
    MockMenuLayoutView mockMenuLayoutView;
    MockStateFactory mockStateFactory;
    MockStateMachine mockStateMachine;
    
    int initialPrograms[] = {0, 41, 112};
    mockProgramSelector.setPrograms(initialPrograms, 3);
    
    DiContainer diContainer;
    diContainer.setSetlistManager(&setlistManager)
        ->setUserInput(&mockInput)
        ->setProgramSelector(&mockProgramSelector)
        ->setProgramsBank(&mockProgramsBank)
        ->setEditSetlistView(&mockEditSetlistView)
        ->setSetlistMenuLayoutView(&mockMenuLayoutView)
        ->setStateFactory(&mockStateFactory)
        ->setStateMachine(&mockStateMachine);
    
    // ACT: Attempt out-of-bounds updates directly (these should be silently ignored)
    setlistManager.updateProgram(-1, 99);  // Invalid negative index
    setlistManager.updateProgram(3, 88);   // Invalid: beyond count (count = 3, valid indices 0-2)
    setlistManager.updateProgram(10, 77);  // Invalid: way beyond capacity
    
    // ASSERT: All original values should be unchanged
    TEST_ASSERT_EQUAL(0, setlistManager.getProgram(0));
    TEST_ASSERT_EQUAL(41, setlistManager.getProgram(1));
    TEST_ASSERT_EQUAL(112, setlistManager.getProgram(2));
    
    // Context should still reflect original values
    TEST_ASSERT_EQUAL(0, context.programs[0]);
    TEST_ASSERT_EQUAL(41, context.programs[1]);
    TEST_ASSERT_EQUAL(112, context.programs[2]);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(testShouldWireSetlistManagerThroughEntireStack);
    RUN_TEST(testShouldPersistEditAcrossStateTransitions);
    RUN_TEST(testShouldIgnoreOutOfBoundsEditsInIntegration);
    
    return UNITY_END();
}
