# Revision Request #001

**Task:** Build Plan Item #2 - Unify menu organization principles  
**Request Date:** 2026-10-24  
**From:** Coordinator (based on critic feedback)  
**To:** Architect  
**Priority:** High  
**Revision Cycle:** 1 of 3 maximum

## Summary

Critic review identified critical issues requiring specification revision before proceeding. The current specification has architectural incompatibilities that must be resolved.

## Critic Feedback Summary

**Overall Status:** Specification Needs Revision

### Critical Issues (Must Address):

#### P1: Interface Semantics Mismatch
**Problem:** `ConfigMenuViewInterface` and `MenuLayoutViewInterface` have fundamentally different semantics and method signatures that cannot be resolved through simple inheritance.

**Critic Recommendation:** Use Adapter pattern instead of inheritance. Create `ConfigMenuViewAdapter` that implements `MenuLayoutViewInterface` while wrapping `ConfigMenuViewInterface`.

**Required Changes:**
1. Replace inheritance approach with Adapter pattern in specification
2. Update interface mapping in Step 1 analysis
3. Modify Step 2 to focus on Adapter creation instead of interface extension

#### P2: DI Container Strategy Undefined
**Problem:** Specification doesn't define how DI Container will be updated to support unified MenuController.

**Critic Questions:**
1. Will there be one `MenuController` instance for all states or separate instances?
2. How will `getConfigMenuView()` method change in `DiContainerInterface`?
3. Will `configMenuView` need to implement `MenuLayoutViewInterface`?

**Required Changes:**
1. Add explicit DI Container changes to specification Step 5
2. Define DI Container interface modifications
3. Specify instance management strategy

#### P3: EditSetlistState Ambiguity
**Problem:** Specification leaves EditSetlistState approach as "if applicable" without clear criteria.

**Critic Concern:** EditSetlistState has unique editing requirements (blinking cursor, text editing) that may not fit standard menu pattern.

**Required Changes:**
1. Make explicit decision about EditSetlistState inclusion/exclusion
2. Document decision rationale
3. Update scope definition accordingly

## Specific Revision Tasks

### Task 1: Update Interface Approach
- [ ] Change from inheritance to Adapter pattern
- [ ] Create `ConfigMenuViewAdapter` design
- [ ] Update method mapping analysis
- [ ] Modify affected build steps

### Task 2: Define DI Container Strategy
- [ ] Specify DI Container interface changes
- [ ] Define MenuController instance management
- [ ] Document migration approach for existing code
- [ ] Update affected tests strategy

### Task 3: Resolve EditSetlistState Ambiguity
- [ ] Make explicit inclusion/exclusion decision
- [ ] Document decision rationale
- [ ] Update scope definition
- [ ] Adjust affected steps if needed

## Expected Deliverables

1. **Updated Specification:** Revised `current-feature.md` addressing all critical issues
2. **Architectural Notes:** Document decisions made during revision
3. **Impact Analysis:** Assessment of changes on implementation complexity
4. **Ready for Re-review:** Confirmation that issues are addressed

## Timeline

**Requested Completion:** Within this iteration  
**Re-review:** Immediate after revision completion  
**Maximum Cycles:** 3 (this is cycle 1)

## Quality Criteria for Revision

The revised specification should:
- Resolve all P1 critical issues
- Address P2 major concerns with clear solutions
- Make explicit decisions for P3 ambiguity
- Maintain architectural compliance with project standards
- Preserve all original functional requirements
- Remain implementable within reasonable complexity

---

**Coordinator Note:** This revision request is based on comprehensive critic feedback. Focus on architectural soundness and practical implementability. After revision, the specification will return to critic for re-review.