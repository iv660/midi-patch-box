#include <unity.h>
#include "../../src/app/SetlistManager.h"

// Test setUp and tearDown
void setUp(void) {
    // Set up code here, to run before each test
}

void tearDown(void) {
    // Clean up code here, to run after each test
}

// Test 1: Should initialize with default programs
void testShouldInitializeWithDefaultPrograms(void) {
    // Arrange & Act
    SetlistManager manager;
    
    // Assert - default programs should be [0, 41, 112]
    TEST_ASSERT_EQUAL_INT(0, manager.getProgram(0));
    TEST_ASSERT_EQUAL_INT(41, manager.getProgram(1));
    TEST_ASSERT_EQUAL_INT(112, manager.getProgram(2));
}

// Test 2: Should update program at valid index
void testShouldUpdateProgramAtValidIndex(void) {
    // Arrange
    SetlistManager manager;
    
    // Act - update program at index 0 from 0 to 5
    manager.updateProgram(0, 5);
    
    // Assert
    TEST_ASSERT_EQUAL_INT(5, manager.getProgram(0));
    TEST_ASSERT_EQUAL_INT(41, manager.getProgram(1));  // Others unchanged
    TEST_ASSERT_EQUAL_INT(112, manager.getProgram(2));
}

// Test 3: Should get program at valid index
void testShouldGetProgramAtValidIndex(void) {
    // Arrange
    SetlistManager manager;
    manager.updateProgram(1, 64);
    
    // Act
    int programNumber = manager.getProgram(1);
    
    // Assert
    TEST_ASSERT_EQUAL_INT(64, programNumber);
}

// Test 4: Should return program count
void testShouldReturnProgramCount(void) {
    // Arrange
    SetlistManager manager;
    
    // Act
    int count = manager.getProgramCount();
    
    // Assert - default setlist has 3 programs
    TEST_ASSERT_EQUAL_INT(3, count);
}

// Test 5: Should provide const array access
void testShouldProvideConstArrayAccess(void) {
    // Arrange
    SetlistManager manager;
    manager.updateProgram(0, 10);
    manager.updateProgram(1, 20);
    manager.updateProgram(2, 30);
    
    // Act
    const int* programs = manager.getPrograms();
    
    // Assert - should return pointer to internal array
    TEST_ASSERT_NOT_NULL(programs);
    TEST_ASSERT_EQUAL_INT(10, programs[0]);
    TEST_ASSERT_EQUAL_INT(20, programs[1]);
    TEST_ASSERT_EQUAL_INT(30, programs[2]);
}

// Test 6: Should ignore out of bounds update (NEW P1 requirement)
void testShouldIgnoreOutOfBoundsUpdate(void) {
    // Arrange
    SetlistManager manager;
    int originalProgram0 = manager.getProgram(0);
    int originalProgram1 = manager.getProgram(1);
    int originalProgram2 = manager.getProgram(2);
    
    // Act - try to update at negative index
    manager.updateProgram(-1, 99);
    
    // Assert - all programs should remain unchanged
    TEST_ASSERT_EQUAL_INT(originalProgram0, manager.getProgram(0));
    TEST_ASSERT_EQUAL_INT(originalProgram1, manager.getProgram(1));
    TEST_ASSERT_EQUAL_INT(originalProgram2, manager.getProgram(2));
    
    // Act - try to update beyond count (index 3 when count is 3)
    manager.updateProgram(3, 99);
    
    // Assert - all programs should remain unchanged
    TEST_ASSERT_EQUAL_INT(originalProgram0, manager.getProgram(0));
    TEST_ASSERT_EQUAL_INT(originalProgram1, manager.getProgram(1));
    TEST_ASSERT_EQUAL_INT(originalProgram2, manager.getProgram(2));
    
    // Act - try to update way beyond capacity (index 20)
    manager.updateProgram(20, 99);
    
    // Assert - all programs should remain unchanged
    TEST_ASSERT_EQUAL_INT(originalProgram0, manager.getProgram(0));
    TEST_ASSERT_EQUAL_INT(originalProgram1, manager.getProgram(1));
    TEST_ASSERT_EQUAL_INT(originalProgram2, manager.getProgram(2));
}

// Main test runner
int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(testShouldInitializeWithDefaultPrograms);
    RUN_TEST(testShouldUpdateProgramAtValidIndex);
    RUN_TEST(testShouldGetProgramAtValidIndex);
    RUN_TEST(testShouldReturnProgramCount);
    RUN_TEST(testShouldProvideConstArrayAccess);
    RUN_TEST(testShouldIgnoreOutOfBoundsUpdate);
    
    return UNITY_END();
}
