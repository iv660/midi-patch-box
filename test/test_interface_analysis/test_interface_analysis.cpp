#include <unity.h>
#include <cstring>
#include "app/MenuLayoutViewInterface.h"
#include "app/ConfigMenuViewInterface.h"
#include "app/MenuControllerInterface.h"
#include "app/ConfigMenuViewAdapter.h"
#include "../../test/mocks/MockConfigMenuView.h"

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
    
    TEST_ASSERT_TRUE(configMenuView.wasShowMenuCalled());
    
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
    TEST_ASSERT_TRUE(configMenuView.wasSetSelectedItemCalled());
    TEST_ASSERT_EQUAL(0, configMenuView.getLastSelectedItem());
    TEST_ASSERT_EQUAL_STRING("Config Item 1", configMenuView.getLastDisplayMenuItemName());
    
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
void test_adapter_implementation_verification() {
    // This test verifies that the adapter correctly bridges the interface differences
    
    // Create a ConfigMenuView mock
    MockConfigMenuView configView;
    
    // Create the adapter
    ConfigMenuViewAdapter adapter(&configView);
    
    // Test 1: Title storage (ConfigMenuView has no title support)
    char title[] = "Test Menu";
    adapter.displayTitle(title);
    TEST_ASSERT_EQUAL_STRING("Test Menu", adapter.getStoredTitle());
    TEST_ASSERT_FALSE(configView.wasDisplayMenuItemCalled()); // No view calls for title
    
    // Test 2: Item display without highlighting
    char item1[] = "Item 1";
    adapter.displayItem(0, item1, false);
    TEST_ASSERT_TRUE(configView.wasDisplayMenuItemCalled());
    TEST_ASSERT_EQUAL(0, configView.getLastDisplayMenuItemIndex());
    TEST_ASSERT_EQUAL_STRING("Item 1", configView.getLastDisplayMenuItemName());
    TEST_ASSERT_FALSE(configView.wasSetSelectedItemCalled()); // Not highlighted
    
    configView.reset();
    
    // Test 3: Item display with highlighting
    char item2[] = "Item 2";
    adapter.displayItem(1, item2, true);
    TEST_ASSERT_TRUE(configView.wasDisplayMenuItemCalled());
    TEST_ASSERT_EQUAL(1, configView.getLastDisplayMenuItemIndex());
    TEST_ASSERT_EQUAL_STRING("Item 2", configView.getLastDisplayMenuItemName());
    TEST_ASSERT_TRUE(configView.wasSetSelectedItemCalled());
    TEST_ASSERT_EQUAL(1, configView.getLastSelectedItem());
    
    configView.reset();
    
    // Test 4: Clear items (should reinitialize view)
    adapter.clearItems();
    TEST_ASSERT_TRUE(configView.wasShowMenuCalled());
    TEST_ASSERT_EQUAL(-1, adapter.getHighlightedIndex()); // Reset highlighted index
    
    // Test 5: Maximum items
    TEST_ASSERT_EQUAL(4, adapter.getMaxItems()); // Default from DisplayConfigMenuView
    
    // Test 6: Verify adapter implements correct interface
    // (Compile-time check - if this compiles, adapter implements MenuLayoutViewInterface)
    MenuLayoutViewInterface* interfacePtr = &adapter;
    TEST_ASSERT_NOT_NULL(interfacePtr);
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
    RUN_TEST(test_adapter_implementation_verification);
    
    return UNITY_END();
}