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

void testAddMenuItemDisplaysSingleItem() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    MenuController menuController(&mockContainer);
    
    mockContainer.setMockView(&mockView);
    
    char itemTitle[] = "Some title";
    bool callback1HasRun = false;
    auto itemAction = [&callback1HasRun]() { callback1HasRun = true; };
    
    menuController.addMenuItem(itemTitle, itemAction);
    
    TEST_ASSERT_EQUAL(1, mockView.getItemCount());
    TEST_ASSERT_EQUAL_STRING(itemTitle, mockView.getItemCaption(0));
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(0));
}

void testAddMenuItemDisplaysTwoItemsFirstSelected() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    MenuController menuController(&mockContainer);
    
    mockContainer.setMockView(&mockView);
    
    char item1Title[] = "First item";
    char item2Title[] = "Second item";
    bool callback1HasRun = false;
    bool callback2HasRun = false;
    auto item1Action = [&callback1HasRun]() { callback1HasRun = true; };
    auto item2Action = [&callback2HasRun]() { callback2HasRun = true; };
    
    menuController.addMenuItem(item1Title, item1Action)
        ->addMenuItem(item2Title, item2Action);
    
    TEST_ASSERT_EQUAL(2, mockView.getItemCount());
    TEST_ASSERT_EQUAL_STRING(item1Title, mockView.getItemCaption(0));
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(0));
    TEST_ASSERT_EQUAL_STRING(item2Title, mockView.getItemCaption(1));
    TEST_ASSERT_FALSE(mockView.isItemHighlighted(1));
}

void testSelectNextMovesSelectionFromFirstToSecond() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    MenuController menuController(&mockContainer);
    
    mockContainer.setMockView(&mockView);
    
    char item1Title[] = "First item";
    char item2Title[] = "Second item";
    bool callback1HasRun = false;
    bool callback2HasRun = false;
    auto item1Action = [&callback1HasRun]() { callback1HasRun = true; };
    auto item2Action = [&callback2HasRun]() { callback2HasRun = true; };
    
    menuController.addMenuItem(item1Title, item1Action)
        ->addMenuItem(item2Title, item2Action)
        ->selectNext();
    
    TEST_ASSERT_FALSE(mockView.isItemHighlighted(0));
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(1));
}

void testSelectNextCyclicReturnsToFirstAfterThreeCalls() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    MenuController menuController(&mockContainer);
    
    mockContainer.setMockView(&mockView);
    
    char item1Title[] = "First item";
    char item2Title[] = "Second item";
    char item3Title[] = "Third item";
    bool callback1HasRun = false;
    bool callback2HasRun = false;
    bool callback3HasRun = false;
    auto item1Action = [&callback1HasRun]() { callback1HasRun = true; };
    auto item2Action = [&callback2HasRun]() { callback2HasRun = true; };
    auto item3Action = [&callback3HasRun]() { callback3HasRun = true; };
    
    menuController.addMenuItem(item1Title, item1Action)
        ->addMenuItem(item2Title, item2Action)
        ->addMenuItem(item3Title, item3Action)
        ->selectNext()
        ->selectNext()
        ->selectNext();
    
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(0));
    TEST_ASSERT_FALSE(mockView.isItemHighlighted(1));
    TEST_ASSERT_FALSE(mockView.isItemHighlighted(2));
}

void testSelectPreviousCyclicMovesFromFirstToSecond() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    MenuController menuController(&mockContainer);
    
    mockContainer.setMockView(&mockView);
    
    char item1Title[] = "First item";
    char item2Title[] = "Second item";
    bool callback1HasRun = false;
    bool callback2HasRun = false;
    auto item1Action = [&callback1HasRun]() { callback1HasRun = true; };
    auto item2Action = [&callback2HasRun]() { callback2HasRun = true; };
    
    menuController.addMenuItem(item1Title, item1Action)
        ->addMenuItem(item2Title, item2Action)
        ->selectPrevious();
    
    TEST_ASSERT_FALSE(mockView.isItemHighlighted(0));
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(1));
}

void testSelectNextThenSelectPreviousSelectsSecondItem() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    MenuController menuController(&mockContainer);
    
    mockContainer.setMockView(&mockView);
    
    char item1Title[] = "First item";
    char item2Title[] = "Second item";
    char item3Title[] = "Third item";
    bool callback1HasRun = false;
    bool callback2HasRun = false;
    bool callback3HasRun = false;
    auto item1Action = [&callback1HasRun]() { callback1HasRun = true; };
    auto item2Action = [&callback2HasRun]() { callback2HasRun = true; };
    auto item3Action = [&callback3HasRun]() { callback3HasRun = true; };
    
    menuController.addMenuItem(item1Title, item1Action)
        ->addMenuItem(item2Title, item2Action)
        ->addMenuItem(item3Title, item3Action)
        ->selectNext()
        ->selectNext()
        ->selectPrevious();
    
    TEST_ASSERT_FALSE(mockView.isItemHighlighted(0));
    TEST_ASSERT_TRUE(mockView.isItemHighlighted(1));
    TEST_ASSERT_FALSE(mockView.isItemHighlighted(2));
}

void testSelectNextThenExecuteSelectedActionRunsCallback() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;
    MenuController menuController(&mockContainer);
    
    mockContainer.setMockView(&mockView);
    
    char item1Title[] = "First item";
    char item2Title[] = "Second item";
    bool callback1HasRun = false;
    bool callback2HasRun = false;
    auto item1Action = [&callback1HasRun]() { callback1HasRun = true; };
    auto item2Action = [&callback2HasRun]() { callback2HasRun = true; };
    
    menuController.addMenuItem(item1Title, item1Action)
        ->addMenuItem(item2Title, item2Action)
        ->selectNext()
        ->executeSelectedAction();
    
    TEST_ASSERT_FALSE(callback1HasRun);
    TEST_ASSERT_TRUE(callback2HasRun);
}

void testSetTitleReturnsThisForChaining() {
    MockDiContainer mockContainer;
    MockMenuLayoutView mockView;

    mockContainer.setMockView(&mockView);

    MenuController menuController(&mockContainer);

    char title[] = "Chained Title";
    char item[] = "Item";
    bool actionRan = false;
    auto action = [&actionRan]() { actionRan = true; };

    menuController.setTitle(title)
        ->addMenuItem(item, action);

    TEST_ASSERT_EQUAL_STRING(title, mockView.getTitle());
    TEST_ASSERT_EQUAL(1, mockView.getItemCount());
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(testShouldSetTitle);
    RUN_TEST(testAddMenuItemDisplaysSingleItem);
    RUN_TEST(testAddMenuItemDisplaysTwoItemsFirstSelected);
    RUN_TEST(testSelectNextMovesSelectionFromFirstToSecond);
    RUN_TEST(testSelectNextCyclicReturnsToFirstAfterThreeCalls);
    RUN_TEST(testSelectPreviousCyclicMovesFromFirstToSecond);
    RUN_TEST(testSelectNextThenSelectPreviousSelectsSecondItem);
    RUN_TEST(testSelectNextThenExecuteSelectedActionRunsCallback);
    RUN_TEST(testSetTitleReturnsThisForChaining);
    return UNITY_END();
}
