# Cooperative Development Reference Templates

This directory contains minimal contract templates for subagent communication. Each template defines exactly what information is needed for a task and what format the response must follow.

## Purpose

Minimize token usage by:
- Providing clear, structured contracts for each delegation
- Eliminating unnecessary context in subagent invocations
- Standardizing response formats for easy parsing
- Keeping each template under 500 tokens

## Template Pairs

Each delegation has two templates:

### Phase 1: Specification Preparation
- `feature-request-template.md` → `feature-response-template.md`

### Phase 2: Specification Review & Approval
- `critic-request-template.md` → `critic-feedback-template.md`
- `p1-fix-request-template.md` → `p1-fix-response-template.md`

### Phase 3: Linear Implementation (TDD Cycle)
- `red-phase-request-template.md` → `red-phase-response-template.md`
- `test-review-request-template.md` → `test-review-response-template.md`
- `green-phase-request-template.md` → `green-phase-response-template.md`
- `code-review-request-template.md` → `code-review-response-template.md`

### Phase 4: Quality Gates
- `check-request-template.md` → `check-response-template.md`

### Phase 5: Completion
- `complete-request-template.md` → `complete-response-template.md`

## Usage

**Coordinator:**
1. Fill in request template with minimal required information
2. Pass to subagent with context files listed in template
3. Receive response matching response template structure
4. Parse response and proceed to next step

**Subagent:**
1. Receive request following request template format
2. Access only files listed in request
3. Complete task
4. Return response following response template format

## Legacy Templates

- `review-request-template.md` / `reviewer-report-template.md` - Superseded by minimal templates above
- `task-context-template.md` - Coordinator's own context, not for subagents

## Token Budget

Target for each template pair:
- Request template: ~200-300 tokens
- Response template: ~150-250 tokens
- Total per delegation cycle: ~400-500 tokens overhead
