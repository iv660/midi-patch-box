# Build Plan

List the features that make up your project, high level and in rough build order.
Keep each item to one line; the details come later in `/feature`.

## MVP for real-world use

- [x] 1. **Update project documentation** - Update README and ARCHITECTURE documentation to reflect current project state and architecture
- [x] 2. **Unify menu organization principles** - Standardize menu architecture to use consistent patterns across all menus (currently two different approaches in use)
- [ ] 3. **Add item to end of setlist** - Implement functionality to append a program to the end of the current setlist
- [ ] 4. **Save setlist to non-volatile memory** - Automatically save setlist after each modification and restore it on device startup
- [ ] 5. **Delete arbitrary setlist item** - Remove any selected item from the setlist
- [ ] 6. **Fast bank loading via MIDI SysEx** - Implement rapid program bank loading through MIDI SysEx messages

## Architectural requirements (cross-cutting)

- Preserve State pattern architecture
- Maintain DI container and interface design
- Ensure testability through native target
- Follow TDD development approach
- Keep documentation up to date (README, ARCHITECTURE)
- Unified menu interaction patterns across all interfaces