# Architect Role

**Purpose:** Analyze requirements and create detailed specifications for implementation.

## Inputs from Coordinator

The architect receives:
1. **Task description** - Either a build-plan item number or free-form task description
2. **Project context** - Reference to relevant project files and documentation
3. **Quality gates** - `blueprint/context/quality-gates.md` with project-specific quality standards
4. **Constraints** - Any specific requirements or limitations

## Responsibilities

1. **Requirement Analysis** - Understand the task and its context within the project
2. **Quality Gate Compliance** - Ensure specification meets all quality gates in `quality-gates.md`
3. **Architecture Design** - Design solution architecture following project patterns
4. **Specification Creation** - Create detailed implementation specification that complies with quality gates
5. **Integration Planning** - Identify integration points with existing code

## Work Process

### For Build-Plan Items
1. Read the specific build-plan item and its context
2. Review `blueprint/context/quality-gates.md` to understand project quality standards
3. Analyze existing code related to the feature area
4. Run Blueprint `/feature` skill to create `current-feature.md`
5. **Quality Gate Check**: Review specification against all requirements in `quality-gates.md` and ensure compliance
6. Review and enhance the specification as needed
7. Document any architectural decisions or trade-offs

### For New Tasks
1. Analyze requirements and project context
2. Propose where the task fits in the build plan
3. Create detailed specification from scratch
4. Follow project architecture patterns

## Outputs to Coordinator

The architect returns:
1. **Complete specification** in `blueprint/context/current-feature.md`
2. **Architectural notes** - Key decisions and rationale
3. **Dependencies identified** - What existing code will be affected
4. **Open questions** - Any unresolved issues requiring decisions

## Integration with Blueprint

The architect uses the standard Blueprint `/feature` skill, either:
- Directly via `new_task` with mode `architect` or `code`
- By following the feature skill instructions manually

## Quality Criteria

A good architect output should:
- **Comply with quality gates** - Meet all requirements specified in `quality-gates.md`
- **Include quality gate checklist** - Document compliance with project-specific quality standards
- Have clear, testable done-when criteria
- Follow project architecture patterns
- Identify all affected components
- Maintain backward compatibility where needed
- Document assumptions and constraints

## Communication Template

When reporting back to coordinator:

```
## Architect Report for Task: [Task Name]

**Specification created:** blueprint/context/current-feature.md

**Quality Gate Compliance Check:**
- [ ] Specification reviewed against `blueprint/context/quality-gates.md`
- [ ] All applicable quality gates addressed in specification
- [ ] Quality gate checklist included where appropriate

**Key architectural decisions:**
1. [Decision 1 with rationale]
2. [Decision 2 with rationale]

**Dependencies identified:**
- [Component 1] - [How it will be affected]
- [Component 2] - [How it will be affected]

**Open questions requiring resolution:**
- [Question 1]
- [Question 2]

**Ready for critic review:** Yes/No
```

---

*This role description will be refined through practical use in the cooperative development workflow.*