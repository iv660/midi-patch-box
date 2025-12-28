#include <unity.h>
#include "app/ProgramsBankInterface.h"
#include "app/ProgramsBank.h"

void setUp(void) {
    // Set up before each test
}

void tearDown(void) {
    // Clean up after each test
}

void testShouldInstantiateProgramsBank() {
    ProgramsBankInterface* programsBank = new ProgramsBank();

    TEST_ASSERT_NOT_NULL(programsBank);

    delete programsBank;
}

void testShouldAddPrograms() {
    ProgramsBankInterface* programsBank = new ProgramsBank();
    
    TEST_ASSERT_NOT_NULL(
        programsBank->addProgram(0, "Piano")
            ->addProgram(1, "Concert Grand")
    ); // programNumber: uint8, programName: char[16]
}

void testShouldGetProgramNameByProgramNumber() {
    ProgramsBankInterface* programsBank = new ProgramsBank();

    programsBank->addProgram(41, "Cello");

    TEST_ASSERT_EQUAL_STRING("Cello", programsBank->getProgramName(41));
}

void testShouldFindProperProgramNameByProgramNumber() {
    ProgramsBankInterface* programsBank = new ProgramsBank();

    programsBank->addProgram(1, "Grand Piano");
    programsBank->addProgram(41, "Viola");
    programsBank->addProgram(112, "Tubular Bells");
    
    TEST_ASSERT_EQUAL_STRING("Viola", programsBank->getProgramName(41));
}

int main(int argc, char** argv) {
    UNITY_BEGIN();

    RUN_TEST(testShouldInstantiateProgramsBank);
    RUN_TEST(testShouldAddPrograms);
    RUN_TEST(testShouldGetProgramNameByProgramNumber);
    RUN_TEST(testShouldFindProperProgramNameByProgramNumber);

    return UNITY_END();
}