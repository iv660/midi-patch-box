# Review Request Template

**File:** `blueprint/context/cooperative/review-request-###.md`  
**Created by:** Coordinator  
**Used by:** Reviewer (subagent)

## Purpose
Standardized template for requesting code review of an implementation step. Provides all necessary context for a reviewer to perform comprehensive assessment.

## Template Structure

```markdown
# Review Request #[number]

## Review Information

**Step:** [Step number and description]  
**Commit:** [Commit hash]  
**Reviewer:** [To be assigned / Assigned]  
**Due:** [Date or timeframe]  
**Priority:** [Normal / High / Critical]  
**Status:** [Awaiting assignment / Active review / Completed]

## Implementation Context

**Task:** [Task name from build plan]  
**Developer:** [Developer name/role]  
**Branch:** [Feature branch name]  
**Specification:** [Reference to current-feature.md or relevant spec section]

## Specification Requirements (Step [number])

From `current-feature.md`:

### Red Phase:
- [ ] [Red phase requirement 1]
- [ ] [Red phase requirement 2]

### Green Phase:
- [ ] [Green phase requirement 1]
- [ ] [Green phase requirement 2]

### Refactor Phase:
- [ ] [Refactor requirement 1]
- [ ] [Refactor requirement 2]

### Verification:
- [ ] [Verification requirement]

**Done when:** [Done-when criteria from specification]

## Files to Review

### Analysis Documents
1. `[path/to/analysis.md]` - [Brief description]
2. `[path/to/compatibility-analysis.md]` - [Brief description]

### Implementation Files
1. `[path/to/implementation.h]` - [Brief description]
2. `[path/to/implementation.cpp]` - [Brief description]

### Test Files
1. `[path/to/test_file.cpp]` - [Brief description]

### Context Files
1. `[path/to/task-context.md]` - Updated task progress

## Review Focus Areas

### 1. TDD Compliance (Quality Gates Requirement)
- Verify that tests actually fail before implementation (red phase confirmed)
- Check that test names follow TDD naming conventions
- Ensure test failures demonstrate actual requirements

### 2. Specification Alignment
- Verify all Step requirements from specification are met
- Check that implementation matches specification details
- Confirm design aligns with architectural decisions

### 3. Code Quality Standards
- Code follows project coding standards
- Consistent naming conventions
- Proper comments and documentation
- Appropriate error handling

### 4. Architecture Consistency
- Maintains project architecture patterns
- Preserves existing design approaches
- Ensures testability and maintainability

### 5. Quality Gate Compliance
- Review compliance with `quality-gates.md` requirements
- TDD red phase verification ✓
- Test failure confirmation ✓
- Architecture pattern compliance ✓
- Code quality standards ✓

## Quality Gate Reference

From `quality-gates.md`:

### TDD (Test-Driven Development)
- **Red Phase Verification:** All tests must fail initially and be confirmed before proceeding
- **Test Failure Confirmation:** Must demonstrate actual test failure with clear messages
- **Green Phase:** Only implement enough to make tests pass
- **Refactor Phase:** Clean up code while keeping tests passing

### Code Quality Standards
- [Project language] standards compliance
- Error handling for edge cases
- Memory safety considerations
- Proper documentation and comments

## Verification Commands

Reviewer should verify:

1. **Test execution (red phase verification):**
   ```bash
   [project test command for specific test]
   ```

2. **Full test suite (regression check):**
   ```bash
   [project full test command]
   ```

3. **Build verification (if applicable):**
   ```bash
   [project build command]
   ```

## Expected Output from Reviewer

Please use the **Reviewer Report Template** from `reviewer-role.md`:

1. Overall assessment (Approved/Needs Revision/Rejected)
2. Code quality review with specific findings
3. Architecture compliance assessment
4. Specification alignment verification
5. Testing review and TDD compliance
6. Issues identified (P1/P2/P3 with locations)
7. Risk assessment
8. Verification performed
9. Next steps recommendations

## Risk Areas to Consider

1. **[Risk area 1]:** [Description]
2. **[Risk area 2]:** [Description]
3. **[Risk area 3]:** [Description]

## Success Criteria

The review is successful when:

- [ ] All P1 issues are addressed (if any)
- [ ] Implementation meets specification requirements
- [ ] TDD compliance verified (red phase confirmed)
- [ ] Architecture patterns preserved
- [ ] Quality gate requirements satisfied
- [ ] No regression in existing functionality

---

**Coordinator:** [Coordinator name]  
**Date:** [YYYY-MM-DD]  
**Status:** [Current status]
```

## Usage Instructions

### For Coordinator:
1. Copy this template to `blueprint/context/cooperative/review-request-###.md`
2. Fill in all `[bracketed]` sections with specific details
3. Increment the `###` number for each review request
4. Launch reviewer subagent with this file as context

### For Reviewer:
1. Read the entire review request before starting review
2. Follow the structure in reviewer-role.md for reporting
3. Save report as `blueprint/context/cooperative/reviewer-report-###-actual.md`
4. Include references to this review request in the report

## Example Reference

See actual example from Step 1 review:
- `blueprint/context/cooperative/review-request-001.md`
- `blueprint/context/cooperative/reviewer-report-001-actual.md`

## Best Practices

1. **Be Specific:** Include exact file paths, commit hashes, and requirements
2. **Provide Context:** Reference relevant specification sections
3. **Set Clear Expectations:** Define success criteria and focus areas
4. **Include Verification Steps:** Provide exact commands for validation
5. **Maintain Consistency:** Use same template across all reviews