#include <unity.h>
#include "app/ConfigMenuViewAdapter.h"
#include "../../test/mocks/MockConfigMenuView.h"
#include <cstring>

// Setup and teardown
void setUp(void) {
}

void tearDown(void) {
}

// Interface method translation tests (RED PHASE - WILL FAIL)
void testAdapterConstructionWithNullView() {
    // Should create adapter even with null view (for graceful degradation)
    ConfigMenuViewAdapter adapter(nullptr);
    TEST_ASSERT_FALSE(adapter.hasValidView());
    TEST_ASSERT_EQUAL(4, adapter.getMaxItems()); // Default max items
    TEST_ASSERT_EQUAL_STRING("", adapter.getStoredTitle()); // Empty title initially
}

void testAdapterConstructionWithValidView() {
    MockConfigMenuView mockView;
    ConfigMenuViewAdapter adapter(&mockView);
    
    TEST_ASSERT_TRUE(adapter.hasValidView());
    TEST_ASSERT_FALSE(adapter.isViewInitialized()); // Not initialized yet
    TEST_ASSERT_EQUAL(4, adapter.getMaxItems());
    TEST_ASSERT_EQUAL_STRING("", adapter.getStoredTitle());
}

void testDisplayTitleStorage() {
    MockConfigMenuView mockView;
    ConfigMenuViewAdapter adapter(&mockView);
    
    char title[] = "Test Menu";
    adapter.displayTitle(title);
    
    // Title should be stored internally (ConfigMenuView has no title support)
    TEST_ASSERT_EQUAL_STRING("Test Menu", adapter.getStoredTitle());
    // No ConfigMenuView methods should be called for title display
    TEST_ASSERT_FALSE(mockView.wasShowMenuCalled());
    TEST_ASSERT_FALSE(mockView.wasDisplayMenuItemCalled());
}

void testDisplayItemTranslation() {
    MockConfigMenuView mockView;
    ConfigMenuViewAdapter adapter(&mockView);
    
    // First item - not highlighted
    char item1[] = "Item 1";
    adapter.displayItem(0, item1, false);
    
    TEST_ASSERT_EQUAL(0, mockView.getLastDisplayMenuItemIndex());
    TEST_ASSERT_EQUAL_STRING("Item 1", mockView.getLastDisplayMenuItemName());
    TEST_ASSERT_FALSE(mockView.wasSetSelectedItemCalled()); // Not highlighted
    
    mockView.reset();
    
    // Second item - highlighted
    char item2[] = "Item 2";
    adapter.displayItem(1, item2, true);
    
    TEST_ASSERT_EQUAL(1, mockView.getLastDisplayMenuItemIndex());
    TEST_ASSERT_EQUAL_STRING("Item 2", mockView.getLastDisplayMenuItemName());
    TEST_ASSERT_TRUE(mockView.wasSetSelectedItemCalled());
    TEST_ASSERT_EQUAL(1, mockView.getLastSelectedItem());
}

void testClearItemsTranslation() {
    MockConfigMenuView mockView;
    ConfigMenuViewAdapter adapter(&mockView);
    
    // ConfigMenuView has no clearItems equivalent
    // Adapter should handle this by resetting internal state
    adapter.clearItems();
    
    // Should call showMenu() to reinitialize the view
    TEST_ASSERT_TRUE(mockView.wasShowMenuCalled());
    TEST_ASSERT_EQUAL(-1, adapter.getHighlightedIndex()); // Reset highlighted index
}

void testGetMaxItemsDefault() {
    MockConfigMenuView mockView;
    ConfigMenuViewAdapter adapter(&mockView);
    
    // Default should be 4 based on DisplayConfigMenuView constraints
    TEST_ASSERT_EQUAL(4, adapter.getMaxItems());
}

void testSetMaxVisibleItems() {
    MockConfigMenuView mockView;
    ConfigMenuViewAdapter adapter(&mockView);
    
    // Change max visible items
    adapter.setMaxVisibleItems(6);
    TEST_ASSERT_EQUAL(6, adapter.getMaxItems());
    
    // Should validate bounds
    // Note: Implementation should handle invalid values gracefully
}

void testAdapterWithNullWrappedViewGracefulDegradation() {
    ConfigMenuViewAdapter adapter(nullptr);
    
    // Methods should not crash when wrapped view is null
    char title[] = "Title";
    adapter.displayTitle(title);
    
    char item[] = "Item";
    adapter.displayItem(0, item, false);
    
    adapter.clearItems();
    
    // Should still store title internally
    TEST_ASSERT_EQUAL_STRING("Title", adapter.getStoredTitle());
}

void testErrorConditionNullPointerHandling() {
    ConfigMenuViewAdapter adapter(nullptr);
    
    // Test with null caption
    adapter.displayItem(0, nullptr, false);
    // Should not crash
    
    // Test with null title
    adapter.displayTitle(nullptr);
    // Should not crash, should store empty string
    TEST_ASSERT_EQUAL_STRING("", adapter.getStoredTitle());
}

void testEdgeCaseEmptyMenu() {
    MockConfigMenuView mockView;
    ConfigMenuViewAdapter adapter(&mockView);
    
    // Clear items on empty menu
    adapter.clearItems();
    TEST_ASSERT_TRUE(mockView.wasShowMenuCalled());
}

void testEdgeCaseMaximumItems() {
    MockConfigMenuView mockView;
    ConfigMenuViewAdapter adapter(&mockView);
    
    // Try to display at maximum index
    char item[] = "Max Item";
    adapter.displayItem(adapter.getMaxItems() - 1, item, true);
    
    TEST_ASSERT_EQUAL(adapter.getMaxItems() - 1, mockView.getLastDisplayMenuItemIndex());
    TEST_ASSERT_TRUE(mockView.wasSetSelectedItemCalled());
    TEST_ASSERT_EQUAL(adapter.getMaxItems() - 1, mockView.getLastSelectedItem());
}

void testMemorySafety() {
    // Test constructor with various parameters
    MockConfigMenuView mockView;
    
    // Test with different max visible values
    ConfigMenuViewAdapter adapter1(&mockView, 2);
    TEST_ASSERT_EQUAL(2, adapter1.getMaxItems());
    
    ConfigMenuViewAdapter adapter2(&mockView, 10);
    TEST_ASSERT_EQUAL(10, adapter2.getMaxItems());
}

void testSetWrappedView() {
    ConfigMenuViewAdapter adapter(nullptr);
    TEST_ASSERT_FALSE(adapter.hasValidView());
    
    MockConfigMenuView mockView;
    adapter.setWrappedView(&mockView);
    
    TEST_ASSERT_TRUE(adapter.hasValidView());
    TEST_ASSERT_FALSE(adapter.isViewInitialized());
}

void testInitializeView() {
    MockConfigMenuView mockView;
    ConfigMenuViewAdapter adapter(&mockView);
    
    TEST_ASSERT_FALSE(adapter.isViewInitialized());
    TEST_ASSERT_FALSE(mockView.wasShowMenuCalled());
    
    adapter.initializeView();
    
    TEST_ASSERT_TRUE(adapter.isViewInitialized());
    TEST_ASSERT_TRUE(mockView.wasShowMenuCalled());
}

void testHighlightStateManagement() {
    MockConfigMenuView mockView;
    ConfigMenuViewAdapter adapter(&mockView);
    
    // Display first item highlighted
    char item1[] = "Item 1";
    adapter.displayItem(0, item1, true);
    TEST_ASSERT_EQUAL(0, adapter.getHighlightedIndex());
    TEST_ASSERT_EQUAL(0, mockView.getLastSelectedItem());
    
    mockView.reset();
    
    // Display second item not highlighted (previous highlight should remain)
    char item2[] = "Item 2";
    adapter.displayItem(1, item2, false);
    TEST_ASSERT_EQUAL(0, adapter.getHighlightedIndex()); // Still first item highlighted
    TEST_ASSERT_FALSE(mockView.wasSetSelectedItemCalled()); // No selection change
    
    mockView.reset();
    
    // Change highlight to second item
    adapter.displayItem(1, item2, true);
    TEST_ASSERT_EQUAL(1, adapter.getHighlightedIndex());
    TEST_ASSERT_TRUE(mockView.wasSetSelectedItemCalled());
    TEST_ASSERT_EQUAL(1, mockView.getLastSelectedItem());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    // Interface method translation tests
    RUN_TEST(testAdapterConstructionWithNullView);
    RUN_TEST(testAdapterConstructionWithValidView);
    RUN_TEST(testDisplayTitleStorage);
    RUN_TEST(testDisplayItemTranslation);
    RUN_TEST(testClearItemsTranslation);
    RUN_TEST(testGetMaxItemsDefault);
    
    // Error condition tests
    RUN_TEST(testAdapterWithNullWrappedViewGracefulDegradation);
    RUN_TEST(testErrorConditionNullPointerHandling);
    
    // Edge case tests
    RUN_TEST(testEdgeCaseEmptyMenu);
    RUN_TEST(testEdgeCaseMaximumItems);
    
    // Memory safety tests
    RUN_TEST(testMemorySafety);
    
    // Additional functionality tests
    RUN_TEST(testSetWrappedView);
    RUN_TEST(testInitializeView);
    RUN_TEST(testSetMaxVisibleItems);
    RUN_TEST(testHighlightStateManagement);
    
    return UNITY_END();
}