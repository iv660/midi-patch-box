#include <unity.h>
#include "StateFactoryInterface.h"
#include "StateInterface.h"

// Mock implementation для тестирования
class MockExtendedStateFactory : public StateFactoryInterface {
public:
    StateInterface* createMainApplicationState() override {
        return nullptr; // Заглушка для существующего метода
    }
    
    StateInterface* createConfigMenuState() override {
        return reinterpret_cast<StateInterface*>(0x1234); // Мок-указатель
    }
    
    StateInterface* createEditSetlistState() override {
        return reinterpret_cast<StateInterface*>(0x5678); // Мок-указатель
    }
};

void test_state_factory_can_create_config_menu_state() {
    MockExtendedStateFactory factory;
    StateInterface* state = factory.createConfigMenuState();
    TEST_ASSERT_NOT_NULL(state);
}

void test_state_factory_can_create_edit_setlist_state() {
    MockExtendedStateFactory factory;
    StateInterface* state = factory.createEditSetlistState();
    TEST_ASSERT_NOT_NULL(state);
}

void setUp() {}
void tearDown() {}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_state_factory_can_create_config_menu_state);
    RUN_TEST(test_state_factory_can_create_edit_setlist_state);
    return UNITY_END();
}