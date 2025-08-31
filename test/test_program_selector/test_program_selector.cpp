#include <unity.h>
#include "app/ProgramSelector.h"


void setUp(void) 
{
    // Set up before each test
}

void tearDown(void) 
{
    // Clean up after each test
}

void testShouldInstantiateProgramSelector() 
{
    ProgramSelector programSelector;
}

void testShouldSelectNextProgram() 
{
    ProgramSelector programSelector;

    programSelector.selectNextProgram();

    TEST_ASSERT_EQUAL_INT(1, programSelector.getSelectedProgramNumber());
}

void testShouldWrapAroundProgramSelection() 
{
    ProgramSelector programSelector;

    programSelector.selectNextProgram();
    programSelector.selectNextProgram();
    programSelector.selectNextProgram();

    TEST_ASSERT_EQUAL_INT(0, programSelector.getSelectedProgramNumber());
}

int main(int argc, char** argv) 
{
    UNITY_BEGIN();

    RUN_TEST(testShouldInstantiateProgramSelector);
    RUN_TEST(testShouldSelectNextProgram);
    RUN_TEST(testShouldWrapAroundProgramSelection);

    return UNITY_END();
}