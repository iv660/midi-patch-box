# Feature: Unify menu organization principles

**From build-plan:** feature 2
**Build attempt:** 1
**Branch:** feature/unify-menu-organization-principles

## Goal

Standardize menu architecture to use consistent patterns across all menus. Currently, the project has two different menu approaches: ConfigMenuState uses direct view interface with manual item management, while SetlistMenuState uses MenuController as a mediator. This feature will unify all menus to use the MenuController pattern, ensuring consistent navigation, item management, and view updates throughout the application.

## Design reference

No visual design changes needed. This is an architectural unification focusing on consistency in menu implementation patterns.

## In scope

1. Refactor ConfigMenuState to use MenuController instead of direct ConfigMenuViewInterface
2. Update ConfigMenuViewInterface to align with MenuLayoutViewInterface pattern
3. Create unified MenuControllerInterface that supports all menu use cases
4. Update EditSetlistState to use unified menu patterns if applicable
5. Ensure all menu states follow consistent DI container usage
6. Maintain all existing functionality and user interactions
7. Update tests to reflect unified architecture
8. Document the unified menu architecture pattern

## Out of scope

1. Changes to user interface or visual design
2. Adding new menu features or functionality
3. Modifying non-menu related states or components
4. Changes to hardware abstraction layer
5. Performance optimizations beyond architectural unification

## Build loop

This feature will be built using TDD approach with step-by-step verification. Each step will leave the project in a working state with all tests passing.

## Build steps

### Step 1: Analyze current menu interfaces and identify unification points
- [ ] Review MenuControllerInterface and MenuLayoutViewInterface methods
- [ ] Review ConfigMenuViewInterface methods and compare with MenuLayoutViewInterface
- [ ] Document current differences and identify required interface changes
- **Done when:** Analysis document created with mapping between current and target interfaces

### Step 2: Update ConfigMenuViewInterface to extend MenuLayoutViewInterface
- [ ] Modify ConfigMenuViewInterface to inherit from MenuLayoutViewInterface
- [ ] Ensure backward compatibility for existing usage
- [ ] Update DisplayConfigMenuView implementation to support new interface
- [ ] Verify tests still pass with updated interface
- **Done when:** ConfigMenuViewInterface inherits from MenuLayoutViewInterface and all related tests pass

### Step 3: Refactor ConfigMenuState to use MenuController
- [ ] Update ConfigMenuState constructor to accept MenuControllerInterface
- [ ] Modify ConfigMenuState to use MenuController for menu item management
- [ ] Remove manual menu item tracking and view updates from ConfigMenuState
- [ ] Ensure ConfigMenuState still provides same functionality via MenuController
- **Done when:** ConfigMenuState successfully uses MenuController and all tests pass

### Step 4: Enhance MenuController to support ConfigMenuState requirements
- [ ] Add support for menu titles in MenuController
- [ ] Ensure MenuController handles edge cases (empty menus, single items)
- [ ] Verify MenuController works with both SetlistMenuState and ConfigMenuState
- [ ] Update MenuController tests for enhanced functionality
- **Done when:** MenuController supports all ConfigMenuState requirements and all tests pass

### Step 5: Update StateFactory to provide unified MenuController
- [ ] Modify StateFactory to create MenuController instances for all menu states
- [ ] Ensure DI container provides MenuController to all menu states
- [ ] Update StateFactory tests for new menu controller instantiation
- **Done when:** StateFactory provides MenuController to all menu states and tests pass

### Step 6: Verify EditSetlistState menu patterns
- [ ] Analyze EditSetlistState current menu implementation
- [ ] Determine if EditSetlistState should use unified MenuController
- [ ] Refactor EditSetlistState if needed for consistency
- [ ] Update EditSetlistState tests
- **Done when:** EditSetlistState follows unified menu patterns and all tests pass

### Step 7: Update documentation and architecture diagrams
- [ ] Update ARCHITECTURE.md with unified menu architecture
- [ ] Document menu patterns in coding standards
- [ ] Create menu subsystem documentation
- [ ] Update any affected README sections
- **Done when:** Documentation updated and reflects unified menu architecture

### Step 8: Final verification and cleanup
- [ ] Run all unit tests to ensure no regressions
- [ ] Verify build compiles successfully for both native and pico targets
- [ ] Remove deprecated code and interfaces if any
- [ ] Create summary of unification changes
- **Done when:** All tests pass, builds succeed, and project uses unified menu patterns

## Files / areas

### Core application files:
- `src/app/ConfigMenuState.h` / `.cpp` - Main target for refactoring
- `src/app/ConfigMenuViewInterface.h` - Interface unification
- `src/app/MenuController.h` / `.cpp` - Enhanced for unified support
- `src/app/MenuControllerInterface.h` - Interface updates
- `src/app/MenuLayoutViewInterface.h` - Base interface
- `src/app/SetlistMenuState.h` / `.cpp` - Reference implementation
- `src/app/EditSetlistState.h` / `.cpp` - Potential updates
- `src/app/StateFactory.h` / `.cpp` - MenuController instantiation
- `src/app/DiContainer.h` - Dependency management

### Hardware implementation:
- `src/hardware/DisplayConfigMenuView.h` / `.cpp` - View implementation updates
- `src/hardware/DisplayVerticalMenuLayoutView.h` / `.cpp` - Base view implementation

### Test files:
- `test/test_config_menu_state/` - Test updates for refactored state
- `test/test_menu_controller/` - Enhanced controller tests
- `test/test_setlist_menu_state/` - Reference tests
- `test/test_edit_setlist_state/` - Potential test updates
- `test/test_state_factory/` - Factory test updates

### Documentation:
- `ARCHITECTURE.md` - Updated architecture documentation
- `blueprint/context/coding-standards.md` - Menu pattern standards
- `plans/` - Reference architectural plans

## Data / contracts

### Interface contracts:
1. **MenuLayoutViewInterface** - Base interface for all menu views
   - `displayTitle(char* title)` - Display menu title
   - `displayItem(int index, char* caption, bool highlighted)` - Display menu item
   - `getMaxItems()` - Get maximum visible items

2. **MenuControllerInterface** - Unified menu controller
   - `setTitle(char* title)` - Set menu title
   - `addMenuItem(char* caption, std::function<void()> action)` - Add menu item
   - `selectNext()` / `selectPrevious()` - Navigation
   - `executeSelectedAction()` - Execute selected item action
   - `resetMenuItems()` - Clear all items

3. **State contracts** - All menu states must:
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

## Testing

### Unit testing strategy:
1. **MenuController tests** - Verify enhanced functionality
2. **ConfigMenuState tests** - Verify refactored state uses MenuController
3. **Integration tests** - Verify menu transitions and interactions
4. **View implementation tests** - Verify display updates

### Test commands:
- Run all tests: `pio test -e native`
- Run menu-specific tests: `pio test -e native -f test_menu_controller`
- Run config menu tests: `pio test -e native -f test_config_menu_state`

### Test coverage requirements:
- All menu navigation scenarios
- Edge cases (empty menus, single items)
- State transitions
- Action execution
- View updates

## Notes for the AI

### Key architectural decisions:
1. **Unified pattern**: All menus will use MenuController as mediator between state and view
2. **Interface hierarchy**: ConfigMenuViewInterface extends MenuLayoutViewInterface for consistency
3. **DI container**: MenuController instances provided via DI container to all menu states
4. **State pattern preservation**: Menu states remain State pattern implementations, delegating menu management to MenuController

### Implementation guidance:
- Start with interface analysis (Step 1) to understand exact differences
- Use TDD: Write failing tests first, then implement
- Keep changes incremental and test at each step
- Maintain backward compatibility where possible
- Update documentation alongside code changes

### Risk areas:
- Breaking changes to ConfigMenuViewInterface may affect hardware implementations
- MenuController enhancements must not break existing SetlistMenuState functionality
- StateFactory changes must maintain existing state creation patterns

### Verification points:
- All existing tests must pass after each step
- Build must succeed for both native and pico targets
- Menu functionality must remain identical from user perspective

## Open questions

1. **EditSetlistState approach**: Should EditSetlistState use MenuController or maintain its current specialized editing interface? Current analysis suggests it has unique editing requirements that may not fit the standard menu pattern.

2. **View interface naming**: Should ConfigMenuViewInterface be renamed to align with naming conventions, or is the current name acceptable for historical reasons?

3. **Deprecated methods**: Are there any deprecated methods in current interfaces that should be removed as part of this unification?

These questions should be resolved during Step 1 analysis before proceeding with implementation.