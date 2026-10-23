# Build Plan

List the features that make up your project, high level and in rough build order.
Keep each item to one line; the details come later in `/feature`.

## MVP for real-world use

- [ ] 1. **Update project documentation** - Update README and ARCHITECTURE documentation to reflect current project state and architecture
- [ ] 2. **Unify menu organization principles** - Standardize menu architecture to use consistent patterns across all menus (currently two different approaches in use)
- [ ] 3. **Analyze current data storage architecture** - Review existing ProgramsBank and SetlistMenuState structures, identify integration points for non-volatile storage
- [ ] 4. **Non-volatile storage interface** - Abstract interface for reading/writing banks and setlists to flash memory with mock implementation for tests
- [ ] 5. **Flash storage implementation for RP2040** - Concrete interface implementation for Pico's built-in flash memory with wear leveling consideration
- [ ] 6. **Storage integration with ProgramsBank** - Modify ProgramsBank for automatic save/load from non-volatile storage
- [ ] 7. **Complete bank editing cycle** - Enhance UI for creating, editing, and deleting programs in bank via unified device menu
- [ ] 8. **Setlist management** - Interface for creating and editing setlists: add/remove programs, rename, reorder using unified menu approach
- [ ] 9. **Setlist integration with main mode** - Use setlists in performance mode for navigation through limited program set
- [ ] 10. **Application state persistence** - Automatic save of current bank, setlist, and selected program between reboots
- [ ] 11. **Real hardware testing** - Verify entire chain: editing → saving → reboot → restoration
- [ ] 12. **Final user documentation** - Complete README with full setup, configuration, and usage instructions for end users

## Future possibilities (post-MVP)

- [ ] 13. **Import/export configuration** - Exchange banks and setlists via USB Mass Storage
- [ ] 14. **Advanced MIDI control** - Support for Control Change messages and other MIDI commands
- [ ] 15. **SD card backup** - Additional media for configuration backups
- [ ] 16. **Interface customization** - Display customization (fonts, layout) based on user preferences

## Architectural requirements (cross-cutting)

- Preserve State pattern architecture
- Maintain DI container and interface design
- Ensure testability through native target
- Follow TDD development approach
- Keep documentation up to date (README, ARCHITECTURE)
- Unified menu interaction patterns across all interfaces