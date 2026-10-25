#include <unity.h>
#include <cstring>
#include "app/MenuLayoutViewInterface.h"
#include "app/ConfigMenuViewInterface.h"
#include "app/MenuControllerInterface.h"

// Mock classes for testing interface differences
class MockMenuLayoutView : public MenuLayoutViewInterface {
private:
    char title[32];
    char itemCaptions[10][32];
    bool itemHighlighted[10];
    int itemCount;
    unsigned int maxItems;
    int displayItemCallCount;
    int displayTitleCallCount;
    int clearItemsCallCount;

public:
    MockMenuLayoutView() : itemCount(0), maxItems(4), displayItemCallCount(0), 
                           displayTitleCallCount(0), clearItemsCallCount(0) {
        title[0] = '\0';
        for (int i = 0; i < 10; i++) {
            itemCaptions[i][0] = '\0';
            itemHighlighted[i] = false;
        }
    }

    void setMaxItems(unsigned int value) {
        maxItems = value;
    }

    MenuLayoutViewInterface* displayTitle(char* newTitle) override {
        strncpy(title, newTitle, 32);
        title[31] = '\0';
        displayTitleCallCount++;
        return this;
    }

    MenuLayoutViewInterface* displayItem(int index, char* caption, bool highlighted) override {
        if (index >= 0 && index < 10) {
            strncpy(itemCaptions[index], caption, 32);
            itemCaptions[index][31] = '\0';
            itemHighlighted[index] = highlighted;
            displayItemCallCount++;
            if (index + 1 > itemCount) {
                itemCount = index + 1;
            }
        }
        return this;
    }

    unsigned int getMaxItems() const override { 
        return maxItems; 
    }

    MenuLayoutViewInterface* clearItems() override {
        itemCount = 0;
        clearItemsCallCount++;
        for (int i = 0; i < 10; i++) {
            itemCaptions[i][0] = '\0';
            itemHighlighted[i] = false;
        }
        return this;
    }

    // Test helper methods
    const char* getTitle() const { return title; }
    const char* getItemCaption(int index) const {
        return (index >= 0 && index < itemCount) ? itemCaptions[index] : nullptr;
    }
    bool isItemHighlighted(int index) const {
        return (index >= 0 && index < itemCount) ? itemHighlighted[index] : false;
    }
    int getItemCount() const { return itemCount; }
    int getDisplayItemCallCount() const { return displayItemCallCount; }
    int getDisplayTitleCallCount() const { return displayTitleCallCount; }
    int getClearItemsCallCount() const { return clearItemsCallCount; }
};

class MockConfigMenuView : public ConfigMenuViewInterface {
private:
    bool showMenuCalled;
    int setSelectedItemCalledCount;
    int selectedItemIndex;
    int displayMenuItemCallCount;
    int displayedItemIndices[10];
    const char* displayedItemNames[10];

public:
    MockConfigMenuView() : showMenuCalled(false), setSelectedItemCalledCount(0), 
                          selectedItemIndex(-1), displayMenuItemCallCount(0) {
        for (int i = 0; i < 10; i++) {
            displayedItemIndices[i] = -1;
            displayedItemNames[i] = nullptr;
        }
    }

    ConfigMenuViewInterface* showMenu() override {
        showMenuCalled = true;
        return this;
    }

    ConfigMenuViewInterface* setSelectedItem(int itemIndex) override {
        selectedItemIndex = itemIndex;
        setSelectedItemCalledCount++;
        return this;
    }

    ConfigMenuViewInterface* displayMenuItem(int itemIndex, const char* itemName) override {
        if (displayMenuItemCallCount < 10) {
            displayedItemIndices[displayMenuItemCallCount] = itemIndex;
            displayedItemNames[displayMenuItemCallCount] = itemName;
            displayMenuItemCallCount++;
        }
        return this;
    }

    // Test helper methods
    bool showMenuWasCalled() const { return showMenuCalled; }
    int getSetSelectedItemCallCount() const { return setSelectedItemCalledCount; }
    int getSelectedItemIndex() const { return selectedItemIndex; }
    int getDisplayMenuItemCallCount() const { return displayMenuItemCallCount; }
    const char* getDisplayedItemName(int callIndex) const {
        return (callIndex < displayMenuItemCallCount) ? displayedItemNames[callIndex] : nullptr;
    }
    int getDisplayedItemIndex(int callIndex) const {
        return (callIndex < displayMenuItemCallCount) ? displayedItemIndices[callIndex] : -1;
    }
    bool itemWasDisplayed(const char* itemName) const {
        for (int i = 0; i < displayMenuItemCallCount; i++) {
            if (displayedItemNames[i] && strcmp(displayedItemNames[i], itemName) == 0) {
                return true;
            }
        }
        return false;
    }
};

// Test: Verify interface semantic differences
void test_interface_semantic_differences() {
    // Test 1: MenuLayoutViewInterface has title support
    MockMenuLayoutView menuLayoutView;
    char title[] = "Test Menu";
    menuLayoutView.displayTitle(title);
    
    TEST_ASSERT_EQUAL_STRING("Test Menu", menuLayoutView.getTitle());
    TEST_ASSERT_EQUAL(1, menuLayoutView.getDisplayTitleCallCount());
    
    // Test 2: ConfigMenuViewInterface has showMenu() method
    MockConfigMenuView configMenuView;
    configMenuView.showMenu();
    
    TEST_ASSERT_TRUE(configMenuView.showMenuWasCalled());
    
    // Test 3: MenuLayoutViewInterface combines display and highlighting
    char item1[] = "Item 1";
    menuLayoutView.displayItem(0, item1, true);
    
    TEST_ASSERT_EQUAL_STRING("Item 1", menuLayoutView.getItemCaption(0));
    TEST_ASSERT_TRUE(menuLayoutView.isItemHighlighted(0));
    TEST_ASSERT_EQUAL(1, menuLayoutView.getDisplayItemCallCount());
    
    // Test 4: ConfigMenuViewInterface separates selection from display
    char configItem1[] = "Config Item 1";
    configMenuView.displayMenuItem(0, configItem1);
    configMenuView.setSelectedItem(0);
    
    TEST_ASSERT_EQUAL(1, configMenuView.getDisplayMenuItemCallCount());
    TEST_ASSERT_EQUAL(1, configMenuView.getSetSelectedItemCallCount());
    TEST_ASSERT_EQUAL(0, configMenuView.getSelectedItemIndex());
    TEST_ASSERT_EQUAL_STRING("Config Item 1", configMenuView.getDisplayedItemName(0));
    
    // Test 5: MenuLayoutViewInterface has clearItems() method
    menuLayoutView.clearItems();
    TEST_ASSERT_EQUAL(1, menuLayoutView.getClearItemsCallCount());
    TEST_ASSERT_EQUAL(0, menuLayoutView.getItemCount());
    
    // Test 6: MenuLayoutViewInterface has getMaxItems() method
    menuLayoutView.setMaxItems(4);
    TEST_ASSERT_EQUAL(4, menuLayoutView.getMaxItems());
    
    // This demonstrates the semantic differences that require an adapter
    TEST_ASSERT_MESSAGE(true, "Interface semantic differences identified - adapter required");
}

// Test: Verify adapter requirements (This test should fail - RED PHASE)
void test_adapter_requirements_failing() {
    // This test demonstrates what an adapter needs to do
    // It should fail because the adapter doesn't exist yet
    
    // Create a ConfigMenuView
    MockConfigMenuView configView;
    
    // The adapter would need to:
    // 1. Implement MenuLayoutViewInterface
    // 2. Wrap a ConfigMenuViewInterface
    // 3. Translate method calls
    
    // Expected adapter behavior:
    // - displayTitle() should store title internally (ConfigMenuView has no title support)
    // - displayItem(index, caption, highlighted) should call:
    //   - configView.displayMenuItem(index, caption)
    //   - configView.setSelectedItem(index) if highlighted is true
    // - clearItems() should reset internal state (ConfigMenuView has no clearItems)
    // - getMaxItems() should return a reasonable default
    
    // Since adapter doesn't exist, this test should fail
    TEST_FAIL_MESSAGE("Adapter implementation required - ConfigMenuViewAdapter needed to bridge MenuLayoutViewInterface and ConfigMenuViewInterface");
}

void setUp(void) {
    // Set up code if needed
}

void tearDown(void) {
    // Clean up code if needed
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_interface_semantic_differences);
    RUN_TEST(test_adapter_requirements_failing);
    
    return UNITY_END();
}