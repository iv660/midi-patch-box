# Feature: Update project documentation

**From build-plan:** feature 1
**Build attempt:** 1
**Branch:** feature/update-project-documentation

## Goal

Update README.md and ARCHITECTURE.md documentation to accurately reflect the current project state, architecture, and features as described in the project overview and build plan.

## Design reference

No visual design required. Reference documentation should accurately describe the existing codebase.

## In scope

1. Update README.md to reflect the current State pattern architecture with DI container, menu system, and setlist management features
2. Update ARCHITECTURE.md to ensure consistency with the current codebase structure and implementation
3. Document the actual hardware interface components (encoder, buttons, display) and their current usage
4. Update build and test commands to reflect the current PlatformIO configuration
5. Document the menu subsystem organization principles and current implementation
6. Update feature descriptions to match the current MVP scope from the build plan
7. Ensure documentation accurately reflects the separation between application layer, hardware abstraction, and testing layers

## Out of scope

1. Rewriting code or changing implementation
2. Adding new features or functionality
3. Creating new architectural diagrams (preserve existing ones if accurate)
4. Updating in-code documentation or comments
5. Changing project structure or organization

## Build loop

Workflow configuration: stepReview="feature", checkpointCommits="disabled"
- Write the spec (this document)
- Review and approve the spec
- Implement documentation updates
- Verify documentation accuracy against codebase
- Complete the feature

## Build steps

### Step 1: Analyze documentation gaps
- [ ] Compare README.md with blueprint/context/project-overview.md to identify mismatches
- [ ] Compare ARCHITECTURE.md with actual source code structure in src/ and test/
- [ ] Identify missing or outdated sections in both documents
- [ ] Create a checklist of specific updates needed

**Done when:** Checklist of documentation gaps is documented with specific file references

### Step 2: Update README.md architecture section
- [ ] Update "Software Architecture" section to describe State pattern with DI container
- [ ] Add description of menu subsystem and unified menu organization principles
- [ ] Update component descriptions to include StateMachine, MenuController, SetlistMenuState, etc.
- [ ] Add information about setlist management and program editing features
- [ ] Update project structure to reflect current src/app/ and src/hardware/ organization
- [ ] Ensure hardware requirements match actual implementation (encoder, buttons, display)

**Done when:** README.md architecture section accurately reflects the current State pattern architecture and menu system

### Step 3: Update README.md features and usage sections
- [ ] Update "Features" section to include setlist management, program editing, and configuration menus
- [ ] Update "Usage" section to describe actual navigation through menus and setlists
- [ ] Update MIDI communication details if needed based on current implementation
- [ ] Update configuration examples to reflect current main.cpp structure
- [ ] Update display setup information if hardware configuration has changed

**Done when:** README.md features and usage sections match the current project capabilities

### Step 4: Update ARCHITECTURE.md system architecture
- [ ] Verify architectural diagrams match current component relationships
- [ ] Update component descriptions for StateMachine, DiContainer, MenuController, etc.
- [ ] Ensure interface descriptions match actual interface files in src/app/
- [ ] Update testing strategy section to reflect current Unity test structure
- [ ] Verify build environment configuration matches platformio.ini

**Done when:** ARCHITECTURE.md accurately describes the current system architecture and component relationships

### Step 5: Update ARCHITECTURE.md data model and features
- [ ] Update data model section to include ProgramsBank and Setlist structures
- [ ] Add description of non-volatile storage architecture and planned implementation
- [ ] Update features list to match MVP scope from build plan
- [ ] Add information about menu organization principles and current implementation
- [ ] Update testing organization to reflect current test directory structure

**Done when:** ARCHITECTURE.md data model and features sections reflect current and planned project capabilities

### Step 6: Verify documentation consistency
- [ ] Cross-reference README.md and ARCHITECTURE.md for consistency
- [ ] Verify all documented features exist in the codebase or build plan
- [ ] Check that build commands (pio run, pio test) work as documented
- [ ] Ensure hardware specifications match actual implementation
- [ ] Verify that interface descriptions match actual interface files

**Done when:** Documentation is internally consistent and matches the codebase

### Step 7: Run verification and final review
- [ ] Run `pio test -e native` to verify build system works
- [ ] Review updated documentation for accuracy and completeness
- [ ] Check for any remaining discrepancies between documentation and codebase
- [ ] Ensure documentation follows project coding standards for clarity

**Done when:** Tests pass and documentation accurately reflects the current project state

## Files / areas

- `README.md` - Main project documentation
- `ARCHITECTURE.md` - Detailed architectural documentation
- `blueprint/context/project-overview.md` - Source of truth for project intent
- `blueprint/build-plan.md` - Source of truth for planned features
- `src/` directory - Reference for actual implementation
- `test/` directory - Reference for testing structure
- `platformio.ini` - Reference for build configuration

## Data / contracts

No data contracts or API changes required. Documentation updates only describe existing implementation.

## Testing

- Manual verification: Read documentation and compare with actual codebase
- Build verification: Run `pio test -e native` to ensure documented commands work
- No automated tests needed for documentation updates

## Notes for the AI

1. The README.md currently describes a simpler architecture than what exists. It needs to be updated to reflect the State pattern with DI container, menu system, and setlist management.
2. ARCHITECTURE.md appears detailed but needs verification against actual source code structure.
3. Focus on accuracy - document what exists, not what might exist in the future.
4. Preserve useful existing content while updating inaccurate or missing information.
5. Reference the actual source files to ensure accuracy (e.g., check src/app/ for interfaces, src/hardware/ for implementations).
6. The project uses PlatformIO with native testing environment for fast TDD feedback.
7. Menu organization principles are important - there are currently two different approaches that need unification per feature 2.

## Open questions

None - documentation updates are based on existing codebase and project plans.