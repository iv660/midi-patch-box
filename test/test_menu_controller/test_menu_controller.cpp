#include <unity.h>
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

// Navigation on empty menu
void testNavigationOnEmptyMenu() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    mockView.setMaxItems(2);
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    menuController.selectNext();
    menuController.selectPrevious();
    
    TEST_ASSERT_EQUAL(0, mockView.getItemCount());
}

// Add first menu item
void testAddFirstMenuItem() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    mockView.setMaxItems(2);
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    char caption1[] = "Item 1";
    menuController.addMenuItem(caption1, nullptr);
    
    TEST_ASSERT_EQUAL(1, mockView.getItemCount());
    TEST_ASSERT_EQUAL_STRING(caption1, mockView.getItemCaption(0));
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(0));
}

// Add second menu item
void testAddSecondMenuItem() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    mockView.setMaxItems(2);
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    char caption1[] = "Item 1";
    char caption2[] = "Item 2";
    menuController.addMenuItem(caption1, nullptr)
        ->addMenuItem(caption2, nullptr);
    
    TEST_ASSERT_EQUAL(2, mockView.getItemCount());
    TEST_ASSERT_EQUAL_STRING(caption1, mockView.getItemCaption(0));
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(0));
    TEST_ASSERT_EQUAL_STRING(caption2, mockView.getItemCaption(1));
    TEST_ASSERT_FALSE(mockView.isItemHighlighted(1));
}

// Add item beyond viewport
void testAddItemBeyondViewport() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    mockView.setMaxItems(2);
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    char caption1[] = "Item 1";
    char caption2[] = "Item 2";
    char caption3[] = "Item 3";
    menuController.addMenuItem(caption1, nullptr)
        ->addMenuItem(caption2, nullptr)
        ->addMenuItem(caption3, nullptr);
    
    TEST_ASSERT_EQUAL(2, mockView.getItemCount());
    TEST_ASSERT_EQUAL_STRING(caption1, mockView.getItemCaption(0));
    TEST_ASSERT_EQUAL_STRING(caption2, mockView.getItemCaption(1));
}

// selectNext() - move highlight within viewport
void testSelectNextMovesHighlightWithinViewport() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    mockView.setMaxItems(2);
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    char caption1[] = "Item 1";
    char caption2[] = "Item 2";
    menuController.addMenuItem(caption1, nullptr)
        ->addMenuItem(caption2, nullptr)
        ->selectNext();
    
    TEST_ASSERT_FALSE(mockView.isItemHighlighted(0));
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(1));
    TEST_ASSERT_EQUAL_STRING(caption1, mockView.getItemCaption(0));
    TEST_ASSERT_EQUAL_STRING(caption2, mockView.getItemCaption(1));
}

// selectNext() - scroll viewport down
void testSelectNextScrollsViewportDown() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    mockView.setMaxItems(2);
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    char caption1[] = "Item 1";
    char caption2[] = "Item 2";
    char caption3[] = "Item 3";
    menuController.addMenuItem(caption1, nullptr)
        ->addMenuItem(caption2, nullptr)
        ->addMenuItem(caption3, nullptr)
        ->selectNext()
        ->selectNext();
    
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(1));
    TEST_ASSERT_EQUAL_STRING(caption2, mockView.getItemCaption(0));
    TEST_ASSERT_EQUAL_STRING(caption3, mockView.getItemCaption(1));
}

// selectPrevious() - move highlight within viewport
void testSelectPreviousMovesHighlightWithinViewport() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    mockView.setMaxItems(2);
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    char caption1[] = "Item 1";
    char caption2[] = "Item 2";
    menuController.addMenuItem(caption1, nullptr)
        ->addMenuItem(caption2, nullptr)
        ->selectNext()
        ->selectPrevious();
    
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(0));
    TEST_ASSERT_FALSE(mockView.isItemHighlighted(1));
    TEST_ASSERT_EQUAL_STRING(caption1, mockView.getItemCaption(0));
    TEST_ASSERT_EQUAL_STRING(caption2, mockView.getItemCaption(1));
}

// selectPrevious() - scroll viewport up
void testSelectPreviousScrollsViewportUp() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    mockView.setMaxItems(2);
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    char caption1[] = "Item 1";
    char caption2[] = "Item 2";
    char caption3[] = "Item 3";
    menuController.addMenuItem(caption1, nullptr)
        ->addMenuItem(caption2, nullptr)
        ->addMenuItem(caption3, nullptr)
        ->selectNext()
        ->selectNext()
        ->selectPrevious()
        ->selectPrevious();
    
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(0));
    TEST_ASSERT_EQUAL_STRING(caption1, mockView.getItemCaption(0));
    TEST_ASSERT_EQUAL_STRING(caption2, mockView.getItemCaption(1));
}

// selectPrevious() - wrap around
void testSelectPreviousWrapAround() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    mockView.setMaxItems(2);
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    char caption1[] = "Item 1";
    char caption2[] = "Item 2";
    char caption3[] = "Item 3";
    menuController.addMenuItem(caption1, nullptr)
        ->addMenuItem(caption2, nullptr)
        ->addMenuItem(caption3, nullptr)
        ->selectPrevious();
    
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(1));
    TEST_ASSERT_EQUAL_STRING(caption2, mockView.getItemCaption(0));
    TEST_ASSERT_EQUAL_STRING(caption3, mockView.getItemCaption(1));
}

// selectNext() - wrap around
void testSelectNextWrapAround() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    mockView.setMaxItems(2);
    
    mockContainer.setMockView(&mockView);
    
    MenuController menuController(&mockContainer);
    
    char caption1[] = "Item 1";
    char caption2[] = "Item 2";
    char caption3[] = "Item 3";
    menuController.addMenuItem(caption1, nullptr)
        ->addMenuItem(caption2, nullptr)
        ->addMenuItem(caption3, nullptr)
        ->selectNext()
        ->selectNext()
        ->selectNext();
    
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(0));
    TEST_ASSERT_EQUAL_STRING(caption1, mockView.getItemCaption(0));
    TEST_ASSERT_EQUAL_STRING(caption2, mockView.getItemCaption(1));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(testNavigationOnEmptyMenu);
    RUN_TEST(testAddFirstMenuItem);
    RUN_TEST(testAddSecondMenuItem);
    RUN_TEST(testAddItemBeyondViewport);
    RUN_TEST(testSelectNextMovesHighlightWithinViewport);
    RUN_TEST(testSelectNextScrollsViewportDown);
    RUN_TEST(testSelectPreviousMovesHighlightWithinViewport);
    RUN_TEST(testSelectPreviousScrollsViewportUp);
    RUN_TEST(testSelectPreviousWrapAround);
    RUN_TEST(testSelectNextWrapAround);
    return UNITY_END();
}
