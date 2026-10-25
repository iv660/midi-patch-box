#pragma once

#include "MenuLayoutViewInterface.h"
#include "ConfigMenuViewInterface.h"
#include <cstring>

/**
 * @brief Adapter that bridges MenuLayoutViewInterface to ConfigMenuViewInterface
 * 
 * This adapter allows ConfigMenuViewInterface implementations to be used
 * wherever MenuLayoutViewInterface is expected, enabling the unification
 * of menu architecture across the application.
 * 
 * Key translations:
 * - displayTitle() -> Stores title internally (ConfigMenuView has no title support)
 * - displayItem(index, caption, highlighted) -> 
 *     displayMenuItem(index, caption) + setSelectedItem(index) when highlighted
 * - clearItems() -> Resets internal state, may call showMenu() to reinitialize
 * - getMaxItems() -> Returns reasonable default (4) or configurable value
 * 
 * @note Memory usage optimized for embedded environment
 * @note Thread-safe for single-threaded embedded use case
 * @note Null-safe with graceful degradation
 */
class ConfigMenuViewAdapter : public MenuLayoutViewInterface {
private:
    // Wrapped ConfigMenuViewInterface implementation
    ConfigMenuViewInterface* wrappedView;
    
    // Internal state management
    static constexpr int MAX_TITLE_LENGTH = 31;
    static constexpr int MAX_ITEMS = 10; // Match MenuController capacity
    static constexpr int DEFAULT_MAX_VISIBLE_ITEMS = 4; // Based on DisplayConfigMenuView
    
    char storedTitle[MAX_TITLE_LENGTH + 1];
    int currentHighlightedIndex;
    unsigned int maxVisibleItems;
    bool viewInitialized;
    
    // Private helper methods
    void ensureViewInitialized();
    bool isValidIndex(int index) const;
    void updateHighlightState(int index, bool highlighted);
    
public:
    /**
     * @brief Construct a new ConfigMenuViewAdapter
     * 
     * @param view The ConfigMenuViewInterface to wrap (can be nullptr)
     * @param maxVisible Maximum number of visible items (default: 4)
     */
    explicit ConfigMenuViewAdapter(ConfigMenuViewInterface* view = nullptr, 
                                   unsigned int maxVisible = DEFAULT_MAX_VISIBLE_ITEMS);
    
    /**
     * @brief Destroy the ConfigMenuViewAdapter
     */
    virtual ~ConfigMenuViewAdapter() = default;
    
    // Prevent copying and moving
    ConfigMenuViewAdapter(const ConfigMenuViewAdapter&) = delete;
    ConfigMenuViewAdapter& operator=(const ConfigMenuViewAdapter&) = delete;
    ConfigMenuViewAdapter(ConfigMenuViewAdapter&&) = delete;
    ConfigMenuViewAdapter& operator=(ConfigMenuViewAdapter&&) = delete;
    
    // MenuLayoutViewInterface implementation
    MenuLayoutViewInterface* displayTitle(char* title) override;
    MenuLayoutViewInterface* displayItem(int index, char* caption, bool highlighted) override;
    MenuLayoutViewInterface* clearItems() override;
    unsigned int getMaxItems() const override;
    
    /**
     * @brief Set the wrapped ConfigMenuViewInterface
     * 
     * @param view The view to wrap
     * @return ConfigMenuViewAdapter* this for method chaining
     */
    ConfigMenuViewAdapter* setWrappedView(ConfigMenuViewInterface* view);
    
    /**
     * @brief Get the wrapped ConfigMenuViewInterface
     * 
     * @return ConfigMenuViewInterface* The wrapped view (may be nullptr)
     */
    ConfigMenuViewInterface* getWrappedView() const;
    
    /**
     * @brief Get the currently stored title
     * 
     * @return const char* The stored title (empty string if none)
     */
    const char* getStoredTitle() const;
    
    /**
     * @brief Get the current highlighted index
     * 
     * @return int The highlighted index (-1 if none)
     */
    int getHighlightedIndex() const;
    
    /**
     * @brief Set maximum visible items
     * 
     * @param maxItems New maximum (1-MAX_ITEMS)
     */
    void setMaxVisibleItems(unsigned int maxItems);
    
    /**
     * @brief Check if wrapped view is valid
     * 
     * @return true Wrapped view is not nullptr
     * @return false Wrapped view is nullptr
     */
    bool hasValidView() const;
    
    /**
     * @brief Check if view has been initialized via showMenu()
     * 
     * @return true View is initialized
     * @return false View needs initialization
     */
    bool isViewInitialized() const;
    
    /**
     * @brief Explicitly initialize the wrapped view
     * 
     * Calls showMenu() on wrapped view if available
     * @return ConfigMenuViewAdapter* this for method chaining
     */
    ConfigMenuViewAdapter* initializeView();
};