#include <unity.h>
#include "../../src/app/EditSetlistState.h"
#include "../../src/app/EditSetlistViewInterface.h"
#include "../../src/app/DiContainer.h"
#include "../../src/app/ProgramsBankInterface.h"
#include "../../src/app/Program.h"
#include "../mocks/MockEditSetlistView.h"
#include "../mocks/MockInput.h"
#include "../mocks/MockProgramSelector.h"
#include "../mocks/MockProgramsBank.h"

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

    return UNITY_END();
}