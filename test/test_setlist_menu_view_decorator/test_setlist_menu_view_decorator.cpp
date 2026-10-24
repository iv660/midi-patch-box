#include <unity.h>
#include <cstring>

#include "app/MenuLayoutViewInterface.h"
#include "app/SetlistMenuViewDecorator.h"

class MockMenuLayoutViewForDecoratorTest : public MenuLayoutViewInterface {
private:
    bool displayTitleCalled = false;
    bool displayItemCalled = false;
    bool clearItemsCalled = false;
    bool getMaxItemsCalled = false;

    unsigned int maxItems = 2;

    int lastUpdatedItemIndex = -1;
    char lastUpdatedItemCaption[16] = {0};
    bool lastUpdatedItemHighlighted = false;

public:
    MenuLayoutViewInterface* displayTitle(char* title) override {
        (void)title;
        displayTitleCalled = true;
        return this;
    }

    MenuLayoutViewInterface* displayItem(int index, char* caption, bool highlighted) override {
        (void)index;
        (void)caption;
        (void)highlighted;
        displayItemCalled = true;

        lastUpdatedItemIndex = index;
        strncpy(lastUpdatedItemCaption, caption ? caption : (char*)"", sizeof(lastUpdatedItemCaption));
        lastUpdatedItemCaption[sizeof(lastUpdatedItemCaption) - 1] = '\0';
        lastUpdatedItemHighlighted = highlighted;
        return this;
    }

    MenuLayoutViewInterface* clearItems() override {
        clearItemsCalled = true;
        return this;
    }

    unsigned int getMaxItems() const override {
        const_cast<MockMenuLayoutViewForDecoratorTest*>(this)->getMaxItemsCalled = true;
        return maxItems;
    }

    bool displayTitleWasCalled() const { return displayTitleCalled; }
    bool displayItemWasCalled() const { return displayItemCalled; }
    bool clearItemsWasCalled() const { return clearItemsCalled; }
    bool getMaxItemsWasCalled() const { return getMaxItemsCalled; }

    int getLastUpdatedItemIndex() const { return lastUpdatedItemIndex; }
    const char* getLastUpdatedItemCaption() const { return lastUpdatedItemCaption; }
    bool getLastUpdatedItemHighlighted() const { return lastUpdatedItemHighlighted; }
};

void setUp(void) {}
void tearDown(void) {}

void testShouldDelegateMethodCallsToInnerView() {
    MockMenuLayoutViewForDecoratorTest mockView;
    SetlistMenuViewDecorator decorator(&mockView);

    char title[] = "Title";
    char itemCaption[] = "Item";

    decorator.displayTitle(title);
    decorator.displayItem(0, itemCaption, false);

    TEST_ASSERT_TRUE_MESSAGE(mockView.displayTitleWasCalled(), "Expected displayTitle to be delegated");
    TEST_ASSERT_TRUE_MESSAGE(mockView.displayItemWasCalled(), "Expected displayItem to be delegated");
}

void testShouldDelegateClearItemsToInnerView() {
    MockMenuLayoutViewForDecoratorTest mockView;
    SetlistMenuViewDecorator decorator(&mockView);

    decorator.clearItems();

    TEST_ASSERT_TRUE_MESSAGE(mockView.clearItemsWasCalled(), "Expected clearItems to be delegated");
}

void testShouldDelegateGetMaxItemsToInnerView() {
    MockMenuLayoutViewForDecoratorTest mockView;
    SetlistMenuViewDecorator decorator(&mockView);

    (void)decorator.getMaxItems();

    TEST_ASSERT_TRUE_MESSAGE(mockView.getMaxItemsWasCalled(), "Expected getMaxItems to be delegated");
}

void testShouldReplaceLastHighlightedItem() {
    MockMenuLayoutViewForDecoratorTest mockView;
    SetlistMenuViewDecorator decorator(&mockView);

    char caption1[] = "Item 1";
    char caption2[] = "Item 2";
    char caption3[] = "Item 3";
    char newCaption2[] = "New Item 2";

    decorator.displayItem(0, caption1, false)
        ->displayItem(1, caption2, true)
        ->displayItem(2, caption3, false);

    decorator.replaceLastHighlightedItem(newCaption2);

    TEST_ASSERT_TRUE_MESSAGE(mockView.displayItemWasCalled(), "Expected displayItem to be called");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, mockView.getLastUpdatedItemIndex(),
        "Expecting to update the last highlighted item");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(newCaption2, mockView.getLastUpdatedItemCaption(),
        "Expecting to update caption for the last highlighted item");
    TEST_ASSERT_TRUE_MESSAGE(mockView.getLastUpdatedItemHighlighted(),
        "Expecting updated item to stay highlighted");
}

int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(testShouldDelegateMethodCallsToInnerView);
    RUN_TEST(testShouldDelegateClearItemsToInnerView);
    RUN_TEST(testShouldDelegateGetMaxItemsToInnerView);
    RUN_TEST(testShouldReplaceLastHighlightedItem);
    return UNITY_END();
}

