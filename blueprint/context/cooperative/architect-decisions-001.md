# Architectural Decisions - Revision 001

**Task:** Build Plan Item #2 - Unify menu organization principles  
**Revision Date:** 2026-10-24  
**Architect:** Harvi Code  
**Based On:** Critic feedback from cooperative/critic-feedback.md

## Summary of Changes

This revision addresses all critical issues identified by the critic:

1. **P1 (Critical) - Interface Semantics Mismatch**: Replaced inheritance approach with Adapter pattern
2. **P2 (High) - DI Container Strategy Undefined**: Added explicit DI container design and interface changes
3. **P3 (Medium) - EditSetlistState Ambiguity**: Made explicit decision to exclude with documented rationale

## Detailed Decision Rationale

### 1. Adapter Pattern Selection (vs Inheritance)

**Problem:** ConfigMenuViewInterface and MenuLayoutViewInterface have fundamentally different semantics:
- Method signature differences (`displayMenuItem(int, const char*)` vs `displayItem(int, char*, bool)`)
- Missing methods in ConfigMenuViewInterface (`displayTitle()`, `clearItems()`, `getMaxItems()`)
- Different highlighting approach (internal vs parameter)

**Decision:** Use ConfigMenuViewAdapter implementing MenuLayoutViewInterface and wrapping ConfigMenuViewInterface.

**Rationale:**
1. **Preserves Backward Compatibility**: Existing ConfigMenuViewInterface implementations remain unchanged
2. **Handles Semantic Differences**: Adapter can manage highlighting state internally
3. **Gradual Migration**: Allows step-by-step transition without breaking existing code
4. **Clear Separation**: Adapter responsibility is clearly defined - interface translation

**Implementation Approach:**
- Adapter tracks current highlighted item internally
- Translates `displayItem(index, caption, highlighted)` to `displayMenuItem(index, caption)` + `setSelectedItem(index)`
- Stores titles internally for reference (ConfigMenuViewInterface has no title support)
- Returns reasonable defaults for missing methods like `getMaxItems()`

### 2. DI Container Strategy

**Problem:** Specification lacked concrete DI container design for unified MenuController.

**Decision:** Add `getConfigMenuController()` to DiContainerInterface while maintaining backward compatibility.

**Rationale:**
1. **Clear Dependency Injection**: Each menu state gets its own MenuController instance
2. **Backward Compatibility**: Keep `getConfigMenuView()` during transition period
3. **Consistent Pattern**: Follows existing SetlistMenuState pattern with `getSetlistMenuController()`
4. **Testability**: Separate instances allow independent testing

**DI Container Changes:**
```cpp
// Add to DiContainerInterface:
virtual MenuControllerInterface* getConfigMenuController() const = 0;

// Implementation maintains:
MenuControllerInterface* configMenuController = nullptr;  // New
ConfigMenuViewInterface* configMenuView = nullptr;        // Existing (kept)
```

**Instance Management Strategy:**
- Separate MenuController instances per menu state
- StateFactory responsible for creating appropriate instances
- ConfigMenuController configured with ConfigMenuViewAdapter

### 3. EditSetlistState Exclusion Decision

**Problem:** Specification was ambiguous about EditSetlistState inclusion.

**Decision:** Explicitly exclude EditSetlistState from menu unification.

**Rationale:**
1. **Different Purpose**: EditSetlistState is for editing setlist contents, not navigation
2. **Unique Interface Requirements**:
   - Blinking cursor for edit mode
   - Text editing capabilities
   - Program number selection
   - Save/cancel operations
3. **Architectural Fit**: EditSetlistViewInterface is specialized for editing, not navigation
4. **Complexity Avoidance**: Forcing into menu pattern would add unnecessary complexity

**Documentation Impact:**
- Updated scope definition to clarify exclusion
- Added architectural decision record
- Documented rationale for future reference

## Impact Analysis

### Positive Impacts:
1. **Architectural Consistency**: All navigation menus use same pattern
2. **Backward Compatibility**: Existing code continues to work
3. **Testability**: Adapter pattern enables comprehensive testing
4. **Maintainability**: Clear separation of concerns

### Implementation Complexity:
1. **Adapter Implementation**: Medium complexity for correct interface translation
2. **DI Container Changes**: Low complexity, follows existing patterns
3. **Test Updates**: Medium complexity for new adapter tests
4. **Documentation**: Low complexity for clear documentation

### Risk Mitigation:
1. **Step-by-Step Implementation**: TDD approach with verification at each step
2. **Backward Compatibility**: Maintain existing interfaces during transition
3. **Comprehensive Testing**: New adapter tests ensure correct behavior
4. **Documentation**: Clear decisions and rationale for future reference

## Verification of Critic Feedback Resolution

### ✅ P1: Interface Semantics Mismatch
- **Resolution**: Adapter pattern implemented instead of inheritance
- **Evidence**: Step 2 in specification dedicated to ConfigMenuViewAdapter
- **Verification**: Detailed interface mapping table created

### ✅ P2: DI Container Strategy Undefined
- **Resolution**: Explicit DI container design with interface changes
- **Evidence**: Step 5 defines exact DI container modifications
- **Verification**: Code examples provided for implementation

### ✅ P3: EditSetlistState Ambiguity
- **Resolution**: Explicit exclusion decision with rationale
- **Evidence**: Step 6 documents exclusion decision
- **Verification**: Clear scope definition updated

## Ready for Re-review

The revised specification addresses all critical issues with:
1. **Architecturally Sound Solutions**: Adapter pattern, clear DI design, explicit decisions
2. **Practical Implementability**: Step-by-step approach with TDD
3. **Project Standards Compliance**: Maintains state pattern, DI container, testability
4. **Documentation**: Clear decisions, rationale, and implementation guidance

**Next Step:** Submit to critic for re-review per cooperative development workflow.