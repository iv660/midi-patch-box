# Reference Templates - Cooperative Development

This directory contains standardized templates and examples for the cooperative development workflow. These templates are based on practical experience from real task execution.

## Purpose

Provide reusable, project-agnostic templates that:
1. Ensure consistency across cooperative development tasks
2. Capture best practices identified through real usage
3. Make the workflow repeatable and predictable
4. Serve as reference implementations for customization

## Templates Overview

### 1. Task Management Templates

| Template | Purpose | Used By | Output Location |
|----------|---------|---------|-----------------|
| `task-context-template.md` | Track task progress and agent assignments | Coordinator | `blueprint/context/cooperative/current-task-context.md` |
| `review-request-template.md` | Request code review for implementation steps | Coordinator → Reviewer | `blueprint/context/cooperative/review-request-###.md` |

### 2. Review & Assessment Templates

| Template | Purpose | Used By | Output Location |
|----------|---------|---------|-----------------|
| `reviewer-report-template.md` | Report code review findings and recommendations | Reviewer | `blueprint/context/cooperative/reviewer-report-###-actual.md` |

### 3. Process Templates (Planned)
- `architect-spec-template.md` - Architectural specification template
- `critic-feedback-template.md` - Critic review feedback template  
- `developer-report-template.md` - Developer implementation report template
- `revision-request-template.md` - Revision request template

## Usage Guidelines

### For New Projects
1. Review all templates to understand the workflow
2. Customize templates for project-specific needs
3. Reference templates in your project's `SKILL.md` file
4. Use as-is for consistent, proven patterns

### For Template Customization
1. Copy template to your project directory
2. Modify bracketed `[sections]` with project specifics
3. Maintain core structure for interoperability
4. Document customizations for team reference

### For Skill Integration
Reference these templates in skill files:
```markdown
## Process Documentation

For review requests, use: `reference/review-request-template.md`
For reviewer reports, use: `reference/reviewer-report-template.md`
For task context, use: `reference/task-context-template.md`
```

## Template Design Principles

1. **Project-Agnostic:** No project-specific details in templates
2. **Placeholder-Based:** Use `[bracketed]` sections for customization
3. **Structured Consistency:** Same sections in same order across templates
4. **Evidence-Based:** Include verification and evidence sections
5. **Action-Oriented:** Clear next steps and recommendations

## Real-World Examples

Actual files from cooperative development task execution:

### From MIDI Patch Box Project:
- `blueprint/context/cooperative/current-task-context.md` - Live task context
- `blueprint/context/cooperative/review-request-001.md` - Step 1 review request
- `blueprint/context/cooperative/reviewer-report-001-actual.md` - Actual reviewer output

### Key Observations from Practice:
1. **Context is Critical:** Reviewer needs complete context to work independently
2. **Structure Enables Automation:** Consistent templates enable subagent execution
3. **Evidence Matters:** Include actual test outputs, commit hashes, file references
4. **Quality Gates Work:** Explicit compliance checks improve output quality

## File Naming Conventions

### Coordinator-Created Files:
- `review-request-###.md` - Review requests (### = sequential number)
- `current-task-context.md` - Active task context

### Agent-Created Files:
- `reviewer-report-###-actual.md` - Actual reviewer output
- `architect-output.md` - Architectural specification
- `critic-feedback.md` - Critic review feedback

### Archive Files:
- Add `-archive` suffix or move to `archive/` subdirectory
- Include date in filename for historical tracking

## Integration with Blueprint

These templates complement Blueprint workflow:

1. **Current Feature:** Templates work with `current-feature.md`
2. **Quality Gates:** Templates include quality gate compliance sections
3. **Context Management:** Templates maintain Blueprint context directory structure
4. **Verification:** Templates include project-specific verification commands

## Contribution Guidelines

When improving templates based on new experience:

1. **Document the Change:** What problem does it solve?
2. **Maintain Backward Compatibility:** Don't break existing usage
3. **Update Examples:** Ensure examples reflect template changes
4. **Test in Practice:** Verify with actual cooperative development task

## Getting Started

1. Read `SKILL.md` for overall workflow
2. Review role definitions in role files
3. Study these templates to understand expected outputs
4. Start with `task-context-template.md` for new tasks
5. Use `review-request-template.md` for first review cycle

## Support

For questions or issues with templates:
1. Check actual examples in `blueprint/context/cooperative/`
2. Review decision log in `current-task-context.md`
3. Reference role definitions for agent responsibilities
4. Consult `SKILL.md` for coordinator workflow