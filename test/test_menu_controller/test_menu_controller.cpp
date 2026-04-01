#include <unity.h>
#include <cstring>
#include "app/MenuController.h"
#include "app/DiContainer.h"
#include "../../test/mocks/MockMenuLayoutView.h"

// Mock DiContainer for testing
class MockDiContainer : public DiContainerInterface {
private:
    MenuLayoutViewInterface* mockView = nullptr;
    
public:
    MenuLayoutViewInterface* getSetlistMenuLayoutView() const override {
        return mockView;
    }
    
    void setMockView(MenuLayoutViewInterface* view) {
        mockView = view;
    }
    
    // Other methods - stubs
    SplashScreenViewInterface* getSplashScreenView() const override { return nullptr; }
    IoDriverInterface* getIoDriver() const override { return nullptr; }
    StateFactoryInterface* getStateFactory() const override { return nullptr; }
    UserInputInterface* getUserInput() const override { return nullptr; }
    ProgramSelectorInterface* getProgramSelector() const override { return nullptr; }
    MidiControllerInterface* getMidiController() const override { return nullptr; }
    ProgramSelectionViewInterface* getProgramSelectionView() const override { return nullptr; }
    StateMachineInterface* getStateMachine() const override { return nullptr; }
    ProgramsBankInterface* getProgramsBank() const override { return nullptr; }
    ConfigMenuViewInterface* getConfigMenuView() const override { return nullptr; }
    EditSetlistViewInterface* getEditSetlistView() const override { return nullptr; }
    MenuControllerInterface* getSetlistMenuController() const override { return nullptr; }
    StateMachineInterface* getStateMachineInterface() const override { return nullptr; }
};

void setUp(void) {
}

void tearDown(void) {
}

void testShouldSetTitle() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    char expectedTitle[] = "Test Menu";
    
    menuController.setTitle(expectedTitle);
    
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expectedTitle, mockView.getTitle(), 
                                     "Expected to set menu title for view");
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(testShouldSetTitle);
    return UNITY_END();
}
