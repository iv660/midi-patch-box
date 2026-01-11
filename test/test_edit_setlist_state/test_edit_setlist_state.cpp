#include <unity.h>
#include "EditSetlistState.h"
#include "EditSetlistViewInterface.h"
#include "DiContainer.h"
#include "ProgramsBankInterface.h"
#include "Program.h"
#include "../mocks/MockEditSetlistView.h"
#include "../mocks/MockInput.h"
#include "../mocks/MockProgramSelector.h"

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
    TEST_ASSERT_EQUAL(setlistItems, mockView.getDisplayedSetlistItems());
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
    mockInput.setEncoderButtonPressed(true);
    state.update();
    mockInput.setEncoderButtonPressed(false);
    mockInput.setEncoderClockwise(true);
    state.update();

    // Assert
    TEST_ASSERT_EQUAL_INT(1, mockView.getSetlistEditedProgramIndex());
    TEST_ASSERT_EQUAL_INT(45, mockView.getSetlistEditedProgramNumber());
    TEST_ASSERT_EQUAL_STRING("Cello", mockView.getSetlistEditedProgramName());
}

void testShouldEndEditModeOnEncoderButtonPressed(void) {
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
    
    programsBank.addProgram(44, "Viola");
    programsBank.addProgram(45, "Cello");
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramsBank(&programsBank);
    EditSetlistState state(&diContainer);

    // Act
    mockInput.setEncoderButtonPressed(true);
    state.update();
    mockInput.setEncoderButtonPressed(false);
    mockInput.setEncoderClockwise(true);
    state.update();
    mockInput.setEncoderButtonPressed(true);
    state.update();

    // Assert
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
    diContainer.setEditSetlistView(&mockView);
    diContainer.setUserInput(&mockInput);
    diContainer.setProgramSelector(&mockProgramSelector);
    diContainer.setProgramsBank(&programsBank);
    EditSetlistState state(&diContainer);

    // Act
    mockInput.setEncoderButtonPressed(true);
    state.update();
    mockInput.setEncoderButtonPressed(false);
    mockInput.setEncoderClockwise(true);
    state.update();
    mockInput.setEncoderButtonPressed(true);
    state.update();

    // Assert
    TEST_ASSERT_EQUAL_INT(45, mockProgramSelector.getProgramsList()[0]);
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
    
    return UNITY_END();
}