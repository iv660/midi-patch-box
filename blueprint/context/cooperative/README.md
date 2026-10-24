# Cooperative Development Context

This directory contains temporary context files for the cooperative development workflow.

## Files

- `current-task-context.md` - Current task description and overall status
- `architect-output.md` - Specifications from architect
- `critic-feedback.md` - Feedback from critic  
- `qa-tests.md` - Acceptance tests from QA engineer
- `implementation-status.md` - Step-by-step implementation status
- `review-feedback.md` - Review feedback from reviewer

## Lifecycle

1. Files are created when a cooperative development task starts
2. Updated throughout the workflow as agents produce outputs
3. Archived or cleaned up when task is complete
4. Never committed to Git (should be in .gitignore)

## Usage

The coordinator agent manages these files to pass context between specialized sub-agents while keeping each agent's context limited and focused.