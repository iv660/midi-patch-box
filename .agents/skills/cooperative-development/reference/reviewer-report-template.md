# Reviewer Report Template

**File:** `blueprint/context/cooperative/reviewer-report-###-actual.md`  
**Created by:** Reviewer (subagent)  
**Used by:** Coordinator for workflow progression

## Purpose
Standardized template for reporting code review results. Provides structured assessment of implementation quality, issues, and recommendations.

## Template Structure

```markdown
# Reviewer Report #[number]

## Review Information

**Step:** [Step number and description]  
**Commit:** [Commit hash]  
**Branch:** [Feature branch name]  
**Reviewer:** [Reviewer name/role]  
**Date:** [YYYY-MM-DD]  
**Review ID:** [Review identifier]

## Executive Summary

**Overall Assessment:** ✅ **APPROVED** / ⚠️ **NEEDS REVISION** / ❌ **REJECTED** [with optional qualifiers]

[Brief summary of review findings, key strengths, and major issues]

## Review Findings by Category

### 1. Code Standards Compliance

**Status:** ✅ **Compliant** / ⚠️ **Partial** / ❌ **Non-compliant**

#### Strengths:
- [Strength 1]
- [Strength 2]

#### Concerns:
- [Concern 1]
- [Concern 2]

#### Code Quality Score: [X]/10

### 2. TDD Compliance (Red Phase Verification)

**Status:** ✅ **Fully Compliant** / ⚠️ **Partial** / ❌ **Non-compliant**

#### Verification Performed:
1. **Test Execution:** [Command and results]
   - [Test name]: ✅ PASSED / ❌ FAILED
   - [Test name]: ✅ PASSED / ❌ FAILED

#### TDD Process Verification:
- ✅ **Red Phase:** Test created to demonstrate requirements
- ✅ **Test Failure Confirmation:** Test output documented
- ✅ **Existing Tests:** [X] of [Y] tests pass

#### TDD Compliance Score: [X]/10

### 3. Architecture Compliance

**Status:** ✅ **Compliant** / ⚠️ **Partial** / ❌ **Non-compliant**

#### Architecture Validation:
- [Architecture aspect 1]: ✅ Maintained / ⚠️ Partial / ❌ Violated
- [Architecture aspect 2]: ✅ Maintained / ⚠️ Partial / ❌ Violated

#### Architecture Score: [X]/10

### 4. Specification Alignment

**Status:** ✅ **Fully Aligned** / ⚠️ **Partial** / ❌ **Misaligned**

#### Requirements Verification:
| Requirement | Status | Evidence |
|-------------|--------|----------|
| [Requirement 1] | ✅ / ⚠️ / ❌ | [Evidence location] |
| [Requirement 2] | ✅ / ⚠️ / ❌ | [Evidence location] |

**Specification Compliance Score: [X]/10**

### 5. Test Quality Assessment

**Status:** ✅ **High Quality** / ⚠️ **Adequate** / ❌ **Poor**

#### Test Structure:
- **Mock Implementations:** [Quality assessment]
- **Helper Methods:** [Quality assessment]
- **Assertion Clarity:** [Quality assessment]
- **Test Coverage:** [Quality assessment]

#### Test Effectiveness:
- **Demonstrates Requirements:** [Assessment]
- **Edge Cases Considered:** [Assessment]
- **Project Considerations:** [Assessment]

#### Test Quality Score: [X]/10

### 6. Documentation & Analysis Quality

**Status:** ✅ **Excellent** / ⚠️ **Adequate** / ❌ **Poor**

#### Analysis Documents:
- **Completeness:** [Assessment]
- **Clarity:** [Assessment]
- **Technical Depth:** [Assessment]
- **Decision Rationale:** [Assessment]

#### Documentation Score: [X]/10

## Issues Identified

### P1 (Critical) Issues: [Number]
[If any]
1. **[Issue title]**
   - **Impact:** [What's wrong]
   - **Suggestion:** [How to fix]
   - **Location:** [File:line]

### P2 (Major) Issues: [Number]
[If any]
1. **[Issue title]**
   - **Impact:** [What's wrong]
   - **Suggestion:** [How to fix]
   - **Location:** [File:line]

### P3 (Minor) Issues: [Number]
[If any]
1. **[Issue title]**
   - **Suggestion:** [Improvement]
   - **Location:** [File:line]

## Risk Assessment

### Low Risk Areas (Well-handled):
1. [Area 1]
2. [Area 2]

### Medium Risk Areas (Require Attention):
1. [Area 1] - [Mitigation strategy]
2. [Area 2] - [Mitigation strategy]

### High Risk Areas (None Identified):
- [If any, list with urgent mitigation]

## Verification Performed

### Test Verification:
1. **[Test type]:** ✅ Executed and verified
   ```
   [Test output]
   ```
2. **[Test type]:** ✅ [X]/[Y] tests pass

### Build Verification:
1. **[Build type]:** ✅ Build successful / ⚠️ Issues / ❌ Failed
   - **Note:** [Additional context]

### Code Quality Verification:
1. **[Quality check 1]:** ✅ Passed
2. **[Quality check 2]:** ✅ Passed

## Architectural Decisions Validation

### [Decision 1]: ✅ **Validated** / ⚠️ **Questionable** / ❌ **Invalid**
- **Rationale:** [Decision rationale]
- **Alternative Considered:** [Alternative]
- **Decision Quality:** [Assessment]

### [Decision 2]: ✅ **Validated** / ⚠️ **Questionable** / ❌ **Invalid**
- **Rationale:** [Decision rationale]
- **Alternative Considered:** [Alternative]
- **Decision Quality:** [Assessment]

## Quality Gate Compliance Assessment

### Development Methodology Gates:
- ✅ **Red Phase Verification:** Failing test created and confirmed
- ✅ **Test Failure Confirmation:** Test output documented
- ✅ **Test Commands Defined:** [Command]
- ✅ **All Tests Pass:** [X]/[Y] (only expected failures)

### Architectural Quality Gates:
- ✅ **Architecture Pattern Preserved:** [Pattern] followed
- ✅ **Design Approach:** [Approach] maintained
- ✅ **Interface-Based Design:** Maintains abstraction
- ✅ **Separation of Concerns:** Clear responsibilities

### Project-Specific Requirements:
- ✅ **[Requirement 1]:** [Assessment]
- ✅ **[Requirement 2]:** [Assessment]

## Recommendations for Next Steps

### Immediate Actions (Next Step):
1. **[Action 1]**
2. **[Action 2]**

### Code Quality Improvements:
1. **[Improvement 1]**
2. **[Improvement 2]**

### Process Improvements:
1. **[Process improvement 1]**
2. **[Process improvement 2]**

## Final Assessment

### Overall Score: [X.X]/10

| Category | Score | Weight | Weighted Score |
|----------|-------|--------|----------------|
| Code Standards | [X]/10 | 15% | [X.X] |
| TDD Compliance | [X]/10 | 25% | [X.X] |
| Architecture | [X]/10 | 20% | [X.X] |
| Specification | [X]/10 | 15% | [X.X] |
| Test Quality | [X]/10 | 15% | [X.X] |
| Documentation | [X]/10 | 10% | [X.X] |
| **Total** | | **100%** | **[X.X]** |

### Approval Status: ✅ **APPROVED** / ⚠️ **NEEDS REVISION** / ❌ **REJECTED**

**Rationale:** [Detailed rationale for approval decision]

### Conditions for Approval:
1. [Condition 1] to be addressed in [timeline]
2. [Condition 2] to be addressed in [timeline]

## Reviewer Signature

**Reviewer:** [Reviewer name]  
**Role:** [Reviewer role]  
**Date:** [YYYY-MM-DD]  
**Confidence Level:** [High / Medium / Low] (based on verification completeness)  

**Next Action:** [Recommended next step for coordinator]

---

*This report follows the reviewer-role.md template structure adapted for [Step] assessment*
```

## Usage Instructions

### For Reviewer:
1. Copy this template to `blueprint/context/cooperative/reviewer-report-###-actual.md`
2. Fill in all sections based on actual review findings
3. Use `-actual` suffix to distinguish from test templates
4. Reference the corresponding `review-request-###.md` file

### For Coordinator:
1. Read the report to determine next steps
2. Update `current-task-context.md` with review results
3. If approved: Proceed to next step
4. If needs revision: Create revision request for developer

## Example Reference

See actual example from Step 1 review:
- `blueprint/context/cooperative/reviewer-report-001-actual.md`
- Corresponding `review-request-001.md`

## Best Practices

1. **Be Objective:** Base assessments on evidence, not opinion
2. **Provide Evidence:** Include file references and test outputs
3. **Prioritize Issues:** Use P1/P2/P3 classification for clear prioritization
4. **Offer Solutions:** Don't just identify problems, suggest fixes
5. **Maintain Consistency:** Use same scoring system across reviews
6. **Include Verification:** Document what was actually tested/verified