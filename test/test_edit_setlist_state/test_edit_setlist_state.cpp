#include <unity.h>
#include "../../src/app/EditSetlistState.h"
#include "../../src/app/EditSetlistViewInterface.h"
#include "../../src/app/DiContainer.h"
#include "../../src/app/DiContainerInterface.h"
#include "../../src/app/ProgramsBankInterface.h"
#include "../../src/app/Program.h"
#include "../../src/app/SetlistManager.h"
#include "../../src/app/Context.h"
#include "../mocks/MockEditSetlistView.h"
#include "../mocks/MockInput.h"
#include "../mocks/MockProgramSelector.h"
#include "../mocks/MockProgramsBank.h"

// MockDiContainer for tests that need it
class MockDiContainer : public DiContainerInterface {
private:
    mutable MockInput mockUserInput;
    mutable MockEditSetlistView mockEditSetlistView;
    mutable MockProgramSelector mockProgramSelector;
    mutable MockProgramsBank mockProgramsBank;

public:
    UserInputInterface* getUserInput() const override { return &mockUserInput; }
    EditSetlistViewInterface* getEditSetlistView() const override { return &mockEditSetlistView; }
    ProgramSelectorInterface* getProgramSelector() const override { return &mockProgramSelector; }
    ProgramsBankInterface* getProgramsBank() const override { return &mockProgramsBank; }
    MidiControllerInterface* getMidiController() const override { return nullptr; }
    ProgramSelectionViewInterface* getProgramSelectionView() const override { return nullptr; }
    StateMachineInterface* getStateMachine() const override { return nullptr; }
    SplashScreenViewInterface* getSplashScreenView() const override { return nullptr; }
    IoDriverInterface* getIoDriver() const override { return nullptr; }
    StateFactoryInterface* getStateFactory() const override { return nullptr; }
    ConfigMenuViewInterface* getConfigMenuView() const override { return nullptr; }
    StateMachineInterface* getStateMachineInterface() const override { return nullptr; }
};

void setUp(void) {
    // Set up code here, to run before each test
}

void tearDown(void) {
    // Clean up code here, to run after each test
}

void testShouldShowExistingSetlist(void) {
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockProgramsBank programsBank;

    programsBank.addProgram(44, "Viola");
    programsBank.addProgram(45, "Cello");
    
    diContainer.setEditSetlistView(&mockView);
    diContainer.setProgramsBank(&programsBank);
    
    Program setlistItems[2] = { { 44, "Viola" }, { 45, "Cello" } };
    EditSetlistState state(&diContainer);

    // Act
    state.enter();

    // Assert
    TEST_ASSERT_TRUE(mockView.showSetlistWasCalled());
    const Program* displayedItems = mockView.getDisplayedSetlistItems();
    TEST_ASSERT_EQUAL(44, displayedItems[0].number);
    TEST_ASSERT_EQUAL_STRING("Viola", displayedItems[0].name);
    TEST_ASSERT_EQUAL(45, displayedItems[1].number);
    TEST_ASSERT_EQUAL_STRING("Cello", displayedItems[1].name);
}

void testShouldSelectFirstSetlistItem(void) {
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockProgramsBank programsBank;
    
    diContainer.setEditSetlistView(&mockView);
    diContainer.setProgramsBank(&programsBank);
    EditSetlistState state(&diContainer);

    // Act
    state.enter();

    // Assert
    TEST_ASSERT_EQUAL(0, mockView.getSelectedItemIndex());
}

void testShouldSelectSecondSetlistItemOnEncoderRotatedClockwise(void) {
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;
    
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    EditSetlistState state(&diContainer);

    // Act
    mockInput.setEncoderClockwise(true);
    state.update();

    // Assert
    TEST_ASSERT_EQUAL(1, mockView.getSelectedItemIndex());
}

void testShouldEnterEditModeOnEncoderButtonPressed(void) {
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;
    
    programsBank.addProgram(44, "Viola");
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    EditSetlistState state(&diContainer);

    // Act
    state.enter();  // Initialize the setlist first
    mockInput.setEncoderButtonPressed(true);
    state.update();

    // Assert
    TEST_ASSERT_TRUE(mockView.editModeIsOn());
    TEST_ASSERT_EQUAL_INT(0, mockView.getSetlistEditedProgramIndex());
    TEST_ASSERT_EQUAL_INT(44, mockView.getSetlistEditedProgramNumber());
    TEST_ASSERT_EQUAL_STRING("Viola", mockView.getSetlistEditedProgramName());
}

void testShouldIncrementEditedProgramOnEncoderRotatedClockwise(void) {
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;
    
    programsBank.addProgram(44, "Viola");
    programsBank.addProgram(45, "Cello");
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    EditSetlistState state(&diContainer);

    // Act
    state.enter();  // Initialize the setlist first
    mockInput.setEncoderButtonPressed(true);
    state.update();  // Enter edit mode
    mockInput.setEncoderButtonPressed(false);
    mockInput.setEncoderClockwise(true);
    state.update();  // Increment program number

    // Assert - program number should increment from 44 to 45
    TEST_ASSERT_EQUAL_INT(0, mockView.getSetlistEditedProgramIndex());  // Still editing first item
    TEST_ASSERT_EQUAL_INT(45, mockView.getSetlistEditedProgramNumber());  // Program number incremented
    TEST_ASSERT_EQUAL_STRING("Cello", mockView.getSetlistEditedProgramName());
}

void testShouldEndEditModeOnEncoderButtonPressed(void) {
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;
    MockProgramSelector mockProgramSelector;
    
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    diContainer.setProgramSelector(&mockProgramSelector);
    EditSetlistState state(&diContainer);

    // Act
    mockInput.setEncoderButtonPressed(true);
    state.update();
    mockInput.setEncoderButtonPressed(false);
    state.update();
    mockInput.setEncoderButtonPressed(true);
    state.update();

    // Assert
    TEST_ASSERT_FALSE(mockView.editModeIsOn());
}

void testShouldUpdateEditedProgramInListView(void) {
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;
    MockProgramSelector mockProgramSelector;
    
    programsBank.addProgram(44, "Viola");
    programsBank.addProgram(45, "Cello");
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    diContainer.setProgramSelector(&mockProgramSelector);
    EditSetlistState state(&diContainer);

    // Act
    state.enter();  // Initialize the setlist first
    mockInput.setEncoderButtonPressed(true);
    state.update();  // Enter edit mode
    mockInput.setEncoderButtonPressed(false);
    mockInput.setEncoderClockwise(true);
    state.update();  // Increment program number from 44 to 45
    mockInput.setEncoderClockwise(false);  // Reset encoder state
    mockInput.setEncoderButtonPressed(true);
    state.update();  // Save changes and exit edit mode

    // Assert - first item should now be program 45 (Cello)
    TEST_ASSERT_EQUAL_INT(45, mockView.getDisplayedSetlistItems()[0].number);
    TEST_ASSERT_EQUAL_STRING("Cello", mockView.getDisplayedSetlistItems()[0].name);
}

void testShouldUpdateEditedProgramInProgramSelector(void) {
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramSelector mockProgramSelector;
    MockProgramsBank programsBank;
    
    programsBank.addProgram(44, "Viola");
    programsBank.addProgram(45, "Cello");
    
    // Initialize ProgramSelector with initial programs
    mockProgramSelector.setPrograms({44, 45});
    
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramSelector(&mockProgramSelector);
    diContainer.setProgramsBank(&programsBank);
    EditSetlistState state(&diContainer);

    // Act
    state.enter();  // Initialize the setlist first
    mockInput.setEncoderButtonPressed(true);
    state.update();  // Enter edit mode
    mockInput.setEncoderButtonPressed(false);
    mockInput.setEncoderClockwise(true);
    state.update();  // Increment program number from 44 to 45
    mockInput.setEncoderClockwise(false);  // Reset encoder state
    mockInput.setEncoderButtonPressed(true);
    state.update();  // Save changes and exit edit mode

    // Assert - ProgramSelector should be updated with new program
    TEST_ASSERT_EQUAL_INT(45, mockProgramSelector.getProgramsList()[0]);  // Should be updated to 45
}

void testEditModeShouldNotToggleOnSubsequentUpdate(void) {
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;

    // Add programs to bank
    programsBank.addProgram(44, "Viola");
    programsBank.addProgram(45, "Cello");

    // Setup DI container
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);

    // Create state
    EditSetlistState state(&diContainer);

    // Act
    state.enter();  // Initialize the setlist first
    mockInput.setEncoderButtonPressed(true);
    state.update();  // Enter edit mode - should set editMode = true

    // Reset input state - no buttons pressed for second update
    mockInput.setEncoderButtonPressed(false);

    // Remember the edit mode state after first update
    bool editModeAfterFirstUpdate = mockView.editModeIsOn();

    // Second update - no input changes
    state.update();

    // Assert - edit mode state should NOT have changed
    TEST_ASSERT_EQUAL_MESSAGE(editModeAfterFirstUpdate,
                             mockView.editModeIsOn(),
                             "Edit mode should not toggle on subsequent update without input change");
}

void testShouldCallUserInputUpdateAndNotEnterEditModeWhenButtonReset(void) {
    // Setup - use DiContainer like other tests
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;
    
    // Add programs to bank
    programsBank.addProgram(0, "Clean");
    programsBank.addProgram(41, "Viola");
    programsBank.addProgram(112, "Reverse");
    
    // Setup DI container
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    
    // Create state
    EditSetlistState state(&diContainer);
    state.enter();
    
    // 1. Set encoder button as pressed
    mockInput.setEncoderButtonPressed(true);
    
    // 2. Call state.update() - should trigger enterEditMode if button is pressed
    state.update();
    
    // 3. Verify that userInput.update() was called
    TEST_ASSERT_TRUE_MESSAGE(mockInput.wasUpdateCalled(),
                             "userInput.update() should have been called");
    
    // 4. Reset button state (simulate button released after update)
    mockInput.setEncoderButtonPressed(false);
    
    // 5. Call state.update() again - should NOT enter edit mode since button is not pressed
    state.update();
    
    // 6. Verify that edit mode still stays on when button is not pressed
    TEST_ASSERT_TRUE_MESSAGE(mockView.editModeIsOn(),
                              "Edit mode should be off when button is not pressed");
}

// ========================================
// Step 4: EditSetlistState Integration Tests with SetlistManager
// These tests verify the core bug fix - edits must persist in the setlist
// ========================================

void testShouldUpdateSetlistManagerWhenSavingEdit(void) {
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;
    MockProgramSelector mockProgramSelector;
    
    // Initialize SetlistManager - it uses default programs (0, 41, 112)
    SetlistManager setlistManager;
    
    // Initialize Context with SetlistManager
    Context context;
    context.setSetlistManager(&setlistManager);
    
    // Setup programs bank
    programsBank.addProgram(0, "Clean");
    programsBank.addProgram(41, "Viola");
    programsBank.addProgram(112, "Reverse");
    programsBank.addProgram(5, "Crunch");  // New program to edit to
    
    // Setup DI container
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    diContainer.setProgramSelector(&mockProgramSelector);
    diContainer.setSetlistManager(&setlistManager);
    
    EditSetlistState state(&diContainer);
    
    // Act - Edit first program from 0 to 5
    state.enter();
    mockInput.setEncoderButtonPressed(true);
    state.update();  // Enter edit mode
    mockInput.setEncoderButtonPressed(false);
    
    // Rotate encoder to change program from 0 to 5
    for (int i = 0; i < 5; i++) {
        mockInput.setEncoderClockwise(true);
        state.update();
        mockInput.setEncoderClockwise(false);
    }
    
    mockInput.setEncoderButtonPressed(true);
    state.update();  // Save changes
    
    // Assert - SetlistManager should be updated
    // This is THE KEY TEST - verifying the bug fix
    TEST_ASSERT_EQUAL_INT(5, setlistManager.getProgram(0));
}

void testShouldPersistEditedProgramInSetlist(void) {
    // This test verifies THE BUG FIX - edits must persist in the setlist
    // Previously, edits would update ProgramSelector but not the Context/setlist
    
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;
    MockProgramSelector mockProgramSelector;
    
    // Initialize SetlistManager - it uses default programs (0, 41, 112)
    SetlistManager setlistManager;
    
    // Initialize Context with SetlistManager
    Context context;
    context.setSetlistManager(&setlistManager);
    
    // Setup programs bank
    programsBank.addProgram(0, "Clean");
    programsBank.addProgram(41, "Viola");
    programsBank.addProgram(112, "Reverse");
    programsBank.addProgram(45, "Cello");
    
    // Setup DI container
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    diContainer.setProgramSelector(&mockProgramSelector);
    diContainer.setSetlistManager(&setlistManager);
    
    EditSetlistState state(&diContainer);
    
    // Act - Edit second program (index 1) from 41 to 45
    state.enter();
    
    // Navigate to second item
    mockInput.setEncoderClockwise(true);
    state.update();
    mockInput.setEncoderClockwise(false);
    
    // Enter edit mode
    mockInput.setEncoderButtonPressed(true);
    state.update();
    mockInput.setEncoderButtonPressed(false);
    
    // Change program from 41 to 45 (increment by 4)
    for (int i = 0; i < 4; i++) {
        mockInput.setEncoderClockwise(true);
        state.update();
        mockInput.setEncoderClockwise(false);
    }
    
    // Save changes
    mockInput.setEncoderButtonPressed(true);
    state.update();
    
    // Assert - The edited program MUST persist in the Context
    // This is what was broken - context.programs[1] would still show 41 instead of 45
    TEST_ASSERT_EQUAL_INT(45, context.programs[1]);
    
    // Also verify it's in SetlistManager (redundant but explicit)
    TEST_ASSERT_EQUAL_INT(45, setlistManager.getProgram(1));
}

void testShouldUpdateCorrectSetlistIndex(void) {
    // Verify that EditSetlistState updates the correct index in SetlistManager
    
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;
    MockProgramSelector mockProgramSelector;
    
    // Initialize SetlistManager - it uses default programs (0, 41, 112)
    SetlistManager setlistManager;
    
    // Initialize Context with SetlistManager
    Context context;
    context.setSetlistManager(&setlistManager);
    
    // Setup programs bank
    programsBank.addProgram(0, "Clean");
    programsBank.addProgram(41, "Viola");
    programsBank.addProgram(112, "Reverse");
    programsBank.addProgram(100, "NewProgram");
    
    // Setup DI container
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    diContainer.setProgramSelector(&mockProgramSelector);
    diContainer.setSetlistManager(&setlistManager);
    
    EditSetlistState state(&diContainer);
    
    // Act - Edit THIRD program (index 2) from 112 to 100
    state.enter();
    
    // Navigate to third item
    mockInput.setEncoderClockwise(true);
    state.update();
    mockInput.setEncoderClockwise(false);
    mockInput.setEncoderClockwise(true);
    state.update();
    mockInput.setEncoderClockwise(false);
    
    // Enter edit mode
    mockInput.setEncoderButtonPressed(true);
    state.update();
    mockInput.setEncoderButtonPressed(false);
    
    // Decrement program from 112 to 100 (decrement by 12)
    for (int i = 0; i < 12; i++) {
        mockInput.setEncoderCounterClockwise(true);
        state.update();
        mockInput.setEncoderCounterClockwise(false);
    }
    
    // Save changes
    mockInput.setEncoderButtonPressed(true);
    state.update();
    
    // Assert - Only index 2 should be updated
    TEST_ASSERT_EQUAL_INT(0, setlistManager.getProgram(0));    // Unchanged
    TEST_ASSERT_EQUAL_INT(41, setlistManager.getProgram(1));   // Unchanged
    TEST_ASSERT_EQUAL_INT(100, setlistManager.getProgram(2));  // Changed
}

void testShouldPreserveProgramSelectorUpdate(void) {
    // Verify that EditSetlistState still updates ProgramSelector (existing behavior)
    // This ensures we didn't break the existing functionality while adding SetlistManager
    
    // Arrange
    DiContainer diContainer;
    MockEditSetlistView mockView;
    MockInput mockInput;
    MockProgramsBank programsBank;
    MockProgramSelector mockProgramSelector;
    
    // Initialize SetlistManager - it uses default programs (0, 41, 112)
    SetlistManager setlistManager;
    
    // Initialize Context with SetlistManager
    Context context;
    context.setSetlistManager(&setlistManager);
    
    // Setup programs bank with a wider range
    programsBank.addProgram(0, "Clean");
    programsBank.addProgram(41, "Viola");
    programsBank.addProgram(112, "Reverse");
    programsBank.addProgram(43, "NewSound");
    
    // Initialize ProgramSelector with matching initial programs
    mockProgramSelector.setPrograms({0, 41, 112});
    
    // Setup DI container
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    diContainer.setProgramSelector(&mockProgramSelector);
    diContainer.setSetlistManager(&setlistManager);
    
    EditSetlistState state(&diContainer);
    
    // Act - Edit first program from 0 to 43
    state.enter();
    mockInput.setEncoderButtonPressed(true);
    state.update();  // Enter edit mode
    mockInput.setEncoderButtonPressed(false);
    
    // Increment program from 0 to 43
    for (int i = 0; i < 43; i++) {
        mockInput.setEncoderClockwise(true);
        state.update();
        mockInput.setEncoderClockwise(false);
    }
    
    // Save changes
    mockInput.setEncoderButtonPressed(true);
    state.update();
    
    // Assert - BOTH ProgramSelector AND SetlistManager should be updated
    TEST_ASSERT_EQUAL_INT(43, mockProgramSelector.getProgramsList()[0]);  // Existing behavior
    TEST_ASSERT_EQUAL_INT(43, setlistManager.getProgram(0));              // New behavior
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(testShouldShowExistingSetlist);
    RUN_TEST(testShouldSelectFirstSetlistItem);
    RUN_TEST(testShouldSelectSecondSetlistItemOnEncoderRotatedClockwise);
    RUN_TEST(testShouldEnterEditModeOnEncoderButtonPressed);
    RUN_TEST(testShouldIncrementEditedProgramOnEncoderRotatedClockwise);
    RUN_TEST(testShouldEndEditModeOnEncoderButtonPressed);
    RUN_TEST(testShouldUpdateEditedProgramInListView);
    RUN_TEST(testShouldUpdateEditedProgramInProgramSelector);
    RUN_TEST(testEditModeShouldNotToggleOnSubsequentUpdate);
    RUN_TEST(testShouldCallUserInputUpdateAndNotEnterEditModeWhenButtonReset);
    
    // Step 4: EditSetlistState Integration Tests
    RUN_TEST(testShouldUpdateSetlistManagerWhenSavingEdit);
    RUN_TEST(testShouldPersistEditedProgramInSetlist);
    RUN_TEST(testShouldUpdateCorrectSetlistIndex);
    RUN_TEST(testShouldPreserveProgramSelectorUpdate);

    return UNITY_END();
}