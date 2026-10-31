#include <unity.h>
#include "../../src/app/DiContainer.h"
#include "../../src/app/SetlistManager.h"

DiContainer* diContainer = nullptr;

void setUp() {
    // Create DiContainer instance
    diContainer = new DiContainer();
}

void tearDown() {
    delete diContainer;
    diContainer = nullptr;
}

// Test that DiContainer provides SetlistManager instance
void testShouldInjectSetlistManagerViaDiContainer() {
    SetlistManager* manager = diContainer->getSetlistManager();
    
    TEST_ASSERT_NOT_NULL(manager);
}

// Test that multiple calls return the same SetlistManager instance (singleton behavior)
void testShouldReturnSameSetlistManagerInstance() {
    SetlistManager* manager1 = diContainer->getSetlistManager();
    SetlistManager* manager2 = diContainer->getSetlistManager();
    
    TEST_ASSERT_EQUAL(manager1, manager2);
}

// Test that injected SetlistManager has default programs initialized
void testShouldProvideInitializedSetlistManager() {
    SetlistManager* manager = diContainer->getSetlistManager();
    
    TEST_ASSERT_NOT_NULL(manager);
    
    // Verify it has the expected default program count (3 programs)
    TEST_ASSERT_EQUAL(3, manager->getProgramCount());
    
    // Verify default programs are initialized correctly
    TEST_ASSERT_EQUAL(0, manager->getProgram(0));
    TEST_ASSERT_EQUAL(41, manager->getProgram(1));
    TEST_ASSERT_EQUAL(112, manager->getProgram(2));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(testShouldInjectSetlistManagerViaDiContainer);
    RUN_TEST(testShouldReturnSameSetlistManagerInstance);
    RUN_TEST(testShouldProvideInitializedSetlistManager);
    
    return UNITY_END();
}
