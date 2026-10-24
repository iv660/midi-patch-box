# Feature: Unify menu organization principles

**From build-plan:** feature 2
**Build attempt:** 1
**Branch:** feature/unify-menu-organization-principles

## Goal

Standardize menu architecture to use consistent patterns across all menus. Currently, the project has two different menu approaches: ConfigMenuState uses direct view interface with manual item management, while SetlistMenuState uses MenuController as a mediator. This feature will unify all navigation menus to use the MenuController pattern, ensuring consistent navigation, item management, and view updates throughout the application.

## Design reference

No visual design changes needed. This is an architectural unification focusing on consistency in menu implementation patterns.

## In scope

1. Refactor ConfigMenuState to use MenuController instead of direct ConfigMenuViewInterface
2. Create ConfigMenuViewAdapter that implements MenuLayoutViewInterface and wraps ConfigMenuViewInterface
3. Create unified MenuControllerInterface that supports all menu use cases
4. Ensure all navigation menu states follow consistent DI container usage
5. Maintain all existing functionality and user interactions
6. Update tests to reflect unified architecture
7. Document the unified menu architecture pattern

## Out of scope

1. Changes to user interface or visual design
2. Adding new menu features or functionality
3. Modifying non-menu related states or components
4. Changes to hardware abstraction layer
5. Performance optimizations beyond architectural unification
6. **EditSetlistState unification** - Maintains specialized EditSetlistViewInterface due to unique editing requirements (blinking cursor, text editing, edit mode)

## Build loop

This feature will be built using TDD approach with step-by-step verification. Each step will leave the project in a working state with all tests passing.

## Build steps

### Step 1: Analyze current menu interfaces and create detailed mapping
- [ ] Review MenuControllerInterface and MenuLayoutViewInterface methods
- [ ] Review ConfigMenuViewInterface methods and identify semantic differences
- [ ] Create detailed interface compatibility analysis table
- [ ] Design ConfigMenuViewAdapter to bridge interface differences
- **Done when:** Analysis document created with detailed interface mapping and adapter design

**Interface Analysis Table:**
| MenuLayoutViewInterface Method | ConfigMenuViewInterface Equivalent | Adapter Strategy |
|-------------------------------|-----------------------------------|------------------|
| `displayTitle(char* title)` | No equivalent | Store title internally for reference |
| `displayItem(int index, char* caption, bool highlighted)` | `displayMenuItem(int index, const char* itemName)` + `setSelectedItem(int itemIndex)` | Call `displayMenuItem()`, then call `setSelectedItem()` if highlighted |
| `clearItems()` | No equivalent | Reset internal state, call `showMenu()` to refresh |
| `getMaxItems() const` | No equivalent | Return default value based on display constraints |

### Step 2: Implement ConfigMenuViewAdapter
- [ ] Create ConfigMenuViewAdapter class implementing MenuLayoutViewInterface
- [ ] Implement adapter methods to wrap ConfigMenuViewInterface
- [ ] Add internal state management for highlighted items and titles
- [ ] Write unit tests for adapter functionality
- [ ] Verify adapter correctly bridges interface differences
- **Done when:** ConfigMenuViewAdapter implemented and tested, correctly translating between interfaces

### Step 3: Refactor ConfigMenuState to use MenuController
- [ ] Update ConfigMenuState constructor to accept MenuControllerInterface
- [ ] Modify ConfigMenuState to use MenuController for menu item management
- [ ] Remove manual menu item tracking and view updates from ConfigMenuState
- [ ] Ensure ConfigMenuState still provides same functionality via MenuController
- [ ] Update ConfigMenuState tests to use MenuController pattern
- **Done when:** ConfigMenuState successfully uses MenuController and all tests pass

### Step 4: Enhance MenuController to support ConfigMenuState requirements
- [ ] Add support for menu titles in MenuController (optional enhancement)
- [ ] Ensure MenuController handles edge cases (empty menus, single items)
- [ ] Verify MenuController works with both SetlistMenuState and ConfigMenuState
- [ ] Update MenuController tests for enhanced functionality
- **Done when:** MenuController supports all ConfigMenuState requirements and all tests pass

### Step 5: Update DI Container and StateFactory
- [ ] Add `getConfigMenuController()` method to DiContainerInterface
- [ ] Update DiContainer implementation to provide ConfigMenuController instance
- [ ] Modify StateFactory to create MenuController instances for ConfigMenuState
- [ ] Ensure backward compatibility by keeping existing `getConfigMenuView()` method
- [ ] Update StateFactory tests for new menu controller instantiation
- **Done when:** DI container provides ConfigMenuController, StateFactory creates it, and tests pass

**DI Container Changes:**
```cpp
// Add to DiContainerInterface:
virtual MenuControllerInterface* getConfigMenuController() const = 0;

// Add to DiContainer implementation:
MenuControllerInterface* configMenuController = nullptr;
MenuControllerInterface* getConfigMenuController() const override {
    return configMenuController;
}
DiContainer* setConfigMenuController(MenuControllerInterface* controller) {
    this->configMenuController = controller;
    return this;
}
```

### Step 6: Decision on EditSetlistState - Document Exclusion Rationale
- [ ] Analyze EditSetlistState current implementation and requirements
- [ ] Document decision to exclude from unification
- [ ] Update scope definition to clarify exclusion
- [ ] Add architectural decision record for future reference
- **Done when:** EditSetlistState exclusion documented with clear rationale

**EditSetlistState Exclusion Rationale:**
1. **Different Purpose**: EditSetlistState is for editing setlist contents, not navigation
2. **Unique Interface**: Uses EditSetlistViewInterface with specialized methods for blinking cursor, edit mode, program editing
3. **Complex Interaction**: Requires text editing, program number selection, and save/cancel operations
4. **Architectural Fit**: Better suited to specialized pattern rather than forced into menu navigation pattern

### Step 7: Update documentation and architecture diagrams
- [ ] Update ARCHITECTURE.md with unified menu architecture
- [ ] Document menu patterns in coding standards
- [ ] Create menu subsystem documentation
- [ ] Update any affected README sections
- [ ] Add architectural decision record for adapter pattern choice
- **Done when:** Documentation updated and reflects unified menu architecture

### Step 8: Final verification and cleanup
- [ ] Run all unit tests to ensure no regressions
- [ ] Verify build compiles successfully for both native and pico targets
- [ ] Remove deprecated code and interfaces if any (with backward compatibility considerations)
- [ ] Create summary of unification changes
- **Done when:** All tests pass, builds succeed, and project uses unified menu patterns

## Files / areas

### Core application files:
- `src/app/ConfigMenuState.h` / `.cpp` - Main target for refactoring
- `src/app/ConfigMenuViewInterface.h` - Maintained for backward compatibility
- `src/app/ConfigMenuViewAdapter.h` / `.cpp` - New adapter implementation
- `src/app/MenuController.h` / `.cpp` - Enhanced for unified support
- `src/app/MenuControllerInterface.h` - Interface updates
- `src/app/MenuLayoutViewInterface.h` - Base interface for adapter
- `src/app/SetlistMenuState.h` / `.cpp` - Reference implementation
- `src/app/EditSetlistState.h` / `.cpp` - Excluded from unification
- `src/app/StateFactory.h` / `.cpp` - MenuController instantiation
- `src/app/DiContainer.h` / `DiContainerInterface.h` - Dependency management updates

### Hardware implementation:
- `src/hardware/DisplayConfigMenuView.h` / `.cpp` - Unchanged (used via adapter)
- `src/hardware/DisplayVerticalMenuLayoutView.h` / `.cpp` - Base view implementation

### Test files:
- `test/test_config_menu_state/` - Test updates for refactored state
- `test/test_menu_controller/` - Enhanced controller tests
- `test/test_setlist_menu_state/` - Reference tests
- `test/test_edit_setlist_state/` - No changes required
- `test/test_state_factory/` - Factory test updates
- `test/test_config_menu_view_adapter/` - New adapter tests

### Documentation:
- `ARCHITECTURE.md` - Updated architecture documentation
- `blueprint/context/coding-standards.md` - Menu pattern standards
- `plans/` - Reference architectural plans

## Data / contracts

### Interface contracts:
1. **MenuLayoutViewInterface** - Base interface for all menu views
   - `displayTitle(char* title)` - Display menu title
   - `displayItem(int index, char* caption, bool highlighted)` - Display menu item with highlight
   - `clearItems()` - Clear displayed items
   - `getMaxItems()` - Get maximum visible items

2. **ConfigMenuViewAdapter** - Adapter bridging to ConfigMenuViewInterface
   - Implements MenuLayoutViewInterface
   - Wraps ConfigMenuViewInterface instance
   - Manages highlighting state internally
   - Translates method calls appropriately

3. **MenuControllerInterface** - Unified menu controller
   - `setTitle(char* title)` - Set menu title (optional)
   - `addMenuItem(char* caption, std::function<void()> action)` - Add menu item
   - `selectNext()` / `selectPrevious()` - Navigation
   - `executeSelectedAction()` - Execute selected item action
   - `resetMenuItems()` - Clear all items

4. **State contracts** - All navigation menu states must:
   - Use MenuController for menu management
   - Delegate navigation to MenuController
   - Use DI container for dependency injection
   - Maintain state pattern architecture

### Architectural constraints:
- Preserve State pattern architecture
- Maintain DI container and interface design
- Ensure testability through native target
- Follow TDD development approach
- Unified menu interaction patterns across all interfaces
- **Backward compatibility** for existing ConfigMenuViewInterface usage

## Testing

### Unit testing strategy:
1. **ConfigMenuViewAdapter tests** - Verify correct interface translation
2. **MenuController tests** - Verify enhanced functionality
3. **ConfigMenuState tests** - Verify refactored state uses MenuController
4. **Integration tests** - Verify menu transitions and interactions
5. **View implementation tests** - Verify display updates

### Test commands:
- Run all tests: `pio test -e native`
- Run menu-specific tests: `pio test -e native -f test_menu_controller`
- Run config menu tests: `pio test -e native -f test_config_menu_state`
- Run adapter tests: `pio test -e native -f test_config_menu_view_adapter`

### Test coverage requirements:
- All menu navigation scenarios
- Edge cases (empty menus, single items)
- State transitions
- Action execution
- View updates through adapter
- Backward compatibility verification

## Notes for the AI

### Key architectural decisions:
1. **Adapter Pattern**: Use ConfigMenuViewAdapter instead of inheritance to bridge interface differences
2. **Instance Management**: Separate MenuController instances per menu state for clarity
3. **DI Container Updates**: Add getConfigMenuController() while maintaining backward compatibility
4. **EditSetlistState Exclusion**: Keep specialized interface due to unique editing requirements
5. **Backward Compatibility**: Maintain existing ConfigMenuViewInterface for gradual migration

### Implementation guidance:
- Start with adapter implementation (Step 2) to validate interface bridging
- Use TDD: Write failing tests first, then implement
- Keep changes incremental and test at each step
- Maintain backward compatibility where possible
- Update documentation alongside code changes

### Risk areas:
- Adapter complexity in managing highlighting state
- DI container changes affecting other states
- MenuController enhancements must not break existing SetlistMenuState functionality
- Backward compatibility testing for existing ConfigMenuViewInterface usage

### Verification points:
- All existing tests must pass after each step
- Build must succeed for both native and pico targets
- Menu functionality must remain identical from user perspective
- Adapter correctly translates all interface methods

## Open questions (Resolved)

1. **EditSetlistState approach**: EditSetlistState will NOT use MenuController. It maintains its specialized EditSetlistViewInterface due to unique editing requirements (blinking cursor, text editing, edit mode). This is documented in Step 6.

2. **Interface approach**: Use Adapter pattern instead of inheritance. ConfigMenuViewAdapter implements MenuLayoutViewInterface and wraps ConfigMenuViewInterface.

3. **DI Container strategy**: Add getConfigMenuController() method. Maintain existing getConfigMenuView() for backward compatibility. Use separate MenuController instances per menu state.

4. **Deprecated methods**: No immediate removal of deprecated methods. Maintain backward compatibility during transition period.

## Architectural Decision Records

### ADR-001: Adapter Pattern for Interface Unification
**Context:** Need to unify ConfigMenuViewInterface with MenuLayoutViewInterface despite semantic differences.
**Decision:** Use Adapter pattern with ConfigMenuViewAdapter instead of inheritance.
**Consequences:** More complex but preserves backward compatibility and handles semantic differences correctly.

### ADR-002: EditSetlistState Exclusion
**Context:** EditSetlistState has unique editing requirements different from navigation menus.
**Decision:** Exclude EditSetlistState from menu unification, maintain specialized interface.
**Consequences:** Consistent navigation patterns for menus, specialized editing for setlists.

### ADR-003: DI Container Strategy
**Context:** Need to provide MenuController instances to ConfigMenuState while maintaining existing interface.
**Decision:** Add getConfigMenuController() method, keep existing getConfigMenuView() for compatibility.
**Consequences:** Clear dependency injection, backward compatible, separate instances per state.