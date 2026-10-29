#include <unity.h>
#include "../../src/app/DiContainer.h"
#include "../../src/app/ConfigMenuState.h"
#include "../../src/app/SetlistMenuState.h"
#include "../../src/app/MenuController.h"

MenuController* configController = nullptr;
MenuController* setlistController = nullptr;
DiContainer* diContainer = nullptr;

void setUp() {
    // Create controller instances
    configController = new MenuController(nullptr);
    setlistController = new MenuController(nullptr);
    
    // Create and configure DiContainer
    diContainer = new DiContainer();
    diContainer->setConfigMenuController(configController);
    diContainer->setSetlistMenuController(setlistController);
}

void tearDown() {
    delete configController;
    delete setlistController;
    delete diContainer;
    configController = nullptr;
    setlistController = nullptr;
    diContainer = nullptr;
}

// Test that DiContainer provides separate MenuController instances
void testDiContainerProvidesSeparateConfigMenuController() {
    MenuControllerInterface* configCtrl = diContainer->getConfigMenuController();
    MenuControllerInterface* setlistCtrl = diContainer->getSetlistMenuController();
    
    TEST_ASSERT_NOT_NULL(configCtrl);
    TEST_ASSERT_NOT_NULL(setlistCtrl);
    TEST_ASSERT_NOT_EQUAL(configCtrl, setlistCtrl);
}

// Test that ConfigMenuState receives correct controller from DiContainer
void testConfigMenuStateReceivesCorrectController() {
    // Get the config menu controller that should be used by ConfigMenuState
    MenuControllerInterface* expectedController = diContainer->getConfigMenuController();
    TEST_ASSERT_NOT_NULL(expectedController);
    
    // Create ConfigMenuState and verify it can be constructed with the DiContainer
    ConfigMenuState configState(diContainer);
    
    // This test verifies the interface exists and can be called
    // The actual usage verification happens in ConfigMenuState's own tests
}

// Test that SetlistMenuState still uses its dedicated controller
void testSetlistMenuStateUsesCorrectController() {
    MenuControllerInterface* setlistCtrl = diContainer->getSetlistMenuController();
    TEST_ASSERT_NOT_NULL(setlistCtrl);
    
    // Verify it's distinct from config controller
    MenuControllerInterface* configCtrl = diContainer->getConfigMenuController();
    TEST_ASSERT_NOT_EQUAL(configCtrl, setlistCtrl);
}

// Test that multiple calls return the same instance (singleton behavior)
void testDiContainerReturnsSameSingletonInstances() {
    MenuControllerInterface* configController1 = diContainer->getConfigMenuController();
    MenuControllerInterface* configController2 = diContainer->getConfigMenuController();
    
    TEST_ASSERT_EQUAL(configController1, configController2);
    
    MenuControllerInterface* setlistController1 = diContainer->getSetlistMenuController();
    MenuControllerInterface* setlistController2 = diContainer->getSetlistMenuController();
    
    TEST_ASSERT_EQUAL(setlistController1, setlistController2);
}

// Test that each controller maintains independent state
void testControllersMaintainIndependentState() {
    MenuControllerInterface* configCtrl = diContainer->getConfigMenuController();
    MenuControllerInterface* setlistCtrl = diContainer->getSetlistMenuController();
    
    // Verify we have two distinct controller instances
    TEST_ASSERT_NOT_NULL(configCtrl);
    TEST_ASSERT_NOT_NULL(setlistCtrl);
    TEST_ASSERT_NOT_EQUAL(configCtrl, setlistCtrl);
    
    // Independent state verification happens through actual usage in state classes
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(testDiContainerProvidesSeparateConfigMenuController);
    RUN_TEST(testConfigMenuStateReceivesCorrectController);
    RUN_TEST(testSetlistMenuStateUsesCorrectController);
    RUN_TEST(testDiContainerReturnsSameSingletonInstances);
    RUN_TEST(testControllersMaintainIndependentState);
    
    return UNITY_END();
}
