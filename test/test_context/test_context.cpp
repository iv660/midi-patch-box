#include <unity.h>
#include "../../src/app/Context.h"
#include "../../src/app/SetlistManager.h"

// Test setUp and tearDown
void setUp(void) {
    // Set up code here, to run before each test
}

void tearDown(void) {
    // Clean up code here, to run after each test
}

// Test 1: Should store SetlistManager pointer via setter
void testShouldStoreSetlistManagerPointer(void) {
    // Arrange
    Context context;
    SetlistManager setlistManager;
    
    // Act
    context.setSetlistManager(&setlistManager);
    
    // Assert - Context should have stored the pointer
    // (This will fail because Context doesn't have setSetlistManager() yet)
    TEST_ASSERT_NOT_NULL(context.programs);
}

// Test 2: Should provide access to programs array
void testShouldProvideAccessToProgramsArray(void) {
    // Arrange
    Context context;
    SetlistManager setlistManager;
    
    // Act
    context.setSetlistManager(&setlistManager);
    
    // Assert - context.programs should point to SetlistManager's array
    const int* expectedPrograms = setlistManager.getPrograms();
    TEST_ASSERT_EQUAL_PTR(expectedPrograms, context.programs);
}

// Test 3: Should reflect SetlistManager changes through Context.programs
void testShouldReflectSetlistManagerChanges(void) {
    // Arrange
    Context context;
    SetlistManager setlistManager;
    context.setSetlistManager(&setlistManager);
    
    // Act - Update SetlistManager
    setlistManager.updateProgram(0, 99);
    
    // Assert - Changes should be visible through context.programs
    TEST_ASSERT_EQUAL_INT(99, context.programs[0]);
    TEST_ASSERT_EQUAL_INT(41, context.programs[1]);  // Unchanged
    TEST_ASSERT_EQUAL_INT(112, context.programs[2]); // Unchanged
}

// Test 4: Should maintain stable pointer across SetlistManager updates
void testShouldMaintainStablePointerAcrossUpdates(void) {
    // Arrange
    Context context;
    SetlistManager setlistManager;
    context.setSetlistManager(&setlistManager);
    
    // Capture pointer value
    const int* initialPointer = context.programs;
    
    // Act - Update SetlistManager multiple times
    setlistManager.updateProgram(0, 10);
    setlistManager.updateProgram(1, 20);
    setlistManager.updateProgram(2, 30);
    
    // Assert - Pointer should remain stable (same address)
    TEST_ASSERT_EQUAL_PTR(initialPointer, context.programs);
    
    // Assert - Values should reflect updates
    TEST_ASSERT_EQUAL_INT(10, context.programs[0]);
    TEST_ASSERT_EQUAL_INT(20, context.programs[1]);
    TEST_ASSERT_EQUAL_INT(30, context.programs[2]);
}

// Main test runner
int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(testShouldStoreSetlistManagerPointer);
    RUN_TEST(testShouldProvideAccessToProgramsArray);
    RUN_TEST(testShouldReflectSetlistManagerChanges);
    RUN_TEST(testShouldMaintainStablePointerAcrossUpdates);
    
    return UNITY_END();
}
