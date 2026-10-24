# Project Overview

<!-- blueprint:source-hash 43ab529a303f0180c14cc6cace40afe525cb3d0f7aaec3fd76aa56a280d2ed0c -->

> **Generated file. Don't hand-edit.** Run `/overview` once you've filled in
> [../project-plan.md](../project-plan.md) and
> [../build-plan.md](../build-plan.md). It replaces
> this file with your project's overview, the single source of truth the AI reads
> each session. When the plans change, re-run `/overview` rather than editing here.

## Product

**MIDI Patch Box** - hardware controller for keyboard players in live performances.

Keyboard players in live performances need quick, reliable preset switching for VST hosts without computer distraction. This device provides physical interface (encoder, buttons) with OLED display for intuitive MIDI program switching.

### Users

- **Primary**: Keyboard players in music bands, live performers
- **Context**: Concert venues, rehearsal spaces, studio work (secondary)
- **Needs**: Quick preset switching, reliability, easy setlist configuration, independence from computer after setup

## Data model

### ProgramBank
- `programNumber`: int (0-127) - MIDI program number
- `programName`: string[16] - UTF-8 program name
- `bankIndex`: int - sequential position in bank
- Up to 128 programs per bank

### Setlist  
- `setlistName`: string[16] - name of setlist
- `programReferences`: ProgramBank[] - ordered list of program references from bank
- `programOrder`: int[] - display order in setlist

### SystemState
- `activeBank`: ProgramBank - currently selected bank
- `activeSetlist`: Setlist - currently selected setlist  
- `selectedProgram`: ProgramBank - currently selected program
- `operatingMode`: enum{Performance, Configuration}

### Storage
- Built-in RP2040 flash memory
- Automatic save on changes
- No backup required for MVP

## Features (in build order)

### MVP for real-world use
1. **Update project documentation** - Update README and ARCHITECTURE to reflect current project state
2. **Unify menu organization principles** - Standardize menu architecture with consistent patterns (currently two different approaches)
3. **Analyze current data storage architecture** - Review ProgramsBank and SetlistMenuState, identify non-volatile storage integration points
4. **Non-volatile storage interface** - Abstract interface for reading/writing banks and setlists to flash with mock implementation
5. **Flash storage implementation for RP2040** - Concrete implementation for Pico's flash with wear leveling consideration
6. **Storage integration with ProgramsBank** - Modify ProgramsBank for automatic save/load from non-volatile storage
7. **Complete bank editing cycle** - Enhanced UI for creating, editing, deleting programs via unified device menu
8. **Setlist management** - Interface for creating/editing setlists: add/remove programs, rename, reorder using unified menu
9. **Setlist integration with main mode** - Use setlists in performance mode for navigation through limited program set
10. **Application state persistence** - Automatic save of current bank, setlist, selected program between reboots
11. **Real hardware testing** - Verify editing → saving → reboot → restoration chain
12. **Final user documentation** - Complete README with setup, configuration, usage instructions

### Future possibilities (post-MVP)
13. **Import/export configuration** - Exchange banks and setlists via USB Mass Storage
14. **Advanced MIDI control** - Support Control Change messages and other MIDI commands
15. **SD card backup** - Additional media for configuration backups
16. **Interface customization** - Display customization (fonts, layout) based on user preferences

## Tech stack

### Hardware
- Microcontroller: Raspberry Pi Pico (RP2040)
- Display: OLED SSD1306 128x64, I2C
- Input: Rotary encoder with button + 2 tactile buttons
- Output: USB MIDI via TinyUSB

### Software
- Language: C++17
- Framework: Arduino (Earle Philhower core for RP2040)
- Build: PlatformIO
- Testing: Unity test framework

### Architecture
- State pattern for operating modes
- DI container for dependency injection
- Interface design for testability
- Separation of hardware abstraction and application logic
- Native target for testing without hardware
- Mock objects for hardware interfaces
- TDD development approach

## UI/UX

### Physical interface
- Encoder: menu navigation, program switching
- Encoder button: selection/confirmation  
- Additional buttons: forward/back for quick switching

### Display (OLED 128x64)
- Main mode: large program number + name
- Configuration menu: lists with highlighted item
- Mode and status indication
- Minimalist, readable font

### Constraints
- Monochrome display
- Limited display area (128x64)
- No touch input
- Low response latency requirement

## Deployment

### Target platform
- Raspberry Pi Pico (RP2040) with Arduino framework
- PlatformIO for building and flashing
- USB Mass Storage Device (bootloader) for firmware updates

### Distribution
- Source code on GitHub
- Build instructions
- Ready .uf2 files for flashing
- Standalone device operation

## Usage model and constraints

### Scale
- Personal use by musicians
- Small music collectives
- No multi-user access requirements

### Trust model
- Device physically with user
- No network access or external APIs
- All data stored locally on device

### Security requirements
- Protection against accidental reset
- Predictable behavior during power failures
- No data encryption requirements

### Non-requirements
- Multi-tenancy
- Internet access
- Cloud synchronization
- Role-based access control
- Change audit
- Regulatory compliance (HIPAA, PCI DSS, etc.)

## Architectural requirements (cross-cutting)

- Preserve State pattern architecture
- Maintain DI container and interface design
- Ensure testability through native target
- Follow TDD development approach
- Keep documentation up to date (README, ARCHITECTURE)
- Unified menu interaction patterns across all interfaces

## Monetization

- Open source project
- Potential: ready-made device sales (long-term), customized builds, community donations
- Current focus: functional prototype for real-world use, code quality, documentation, community