# Project Plan

> MIDI Patch Box - hardware controller for keyboard players in live performances

## 1. Problem - What problem are we solving?

Keyboard players in live performances use VST hosts with banks of instrument and effect presets. Switching between presets through computer software distracts from the performance, requires looking at the screen, and is prone to errors in stage conditions.

Solution: A specialized hardware controller with physical interface (encoder, buttons) and OLED display for quick, intuitive MIDI program switching without distraction from the instrument.

## 2. Users - Who is this for?

**Primary users:**
- Keyboard players in music bands
- Performers in live concerts
- Musicians using VST instruments through MIDI keyboards

**Usage context:**
- Concert venues (clubs, theaters, festivals)
- Rehearsal spaces
- Studio work (secondary use)

**Needs:**
- Quick preset switching during performance
- Reliability and predictable operation
- Easy configuration for specific performance setlists
- Independence from computer after setup

## 3. Features - What does the MVP need?

**Main mode (performance):**
- Display current program on OLED display
- Program navigation via encoder or forward/back buttons
- Send MIDI Program Change messages via USB
- Display program number and name

**Configuration mode:**
- Create and edit program banks (up to 128 programs)
- Create setlists (ordered lists of programs from banks)
- Assign program names (up to 16 characters)
- Menu navigation via encoder

**System functions:**
- Save banks and setlists to non-volatile memory
- Automatic state restoration after reboot
- Status indication (mode, saving)

**Not in MVP:**
- Synchronization with computer software
- Wireless connection
- Control of other MIDI messages (CC, SysEx)
- Custom theme customization
- SD card backup

## 4. Data - What are we storing?

**Program banks:**
- MIDI program number (0-127)
- Program name (up to 16 UTF-8 characters)
- Sequential number in bank

**Setlists:**
- Setlist name (up to 16 characters)
- List of references to programs from bank
- Program order in setlist

**System data:**
- Current active bank
- Current active setlist
- Currently selected program
- Operating mode (performance/configuration)

**Storage:**
- Built-in non-volatile memory of RP2040 (flash)
- No backup required for MVP
- Automatic save on changes

## 5. Tech - What stack are we using?

**Hardware platform:**
- Microcontroller: Raspberry Pi Pico (RP2040)
- Display: OLED SSD1306 128x64, I2C interface
- Input: Rotary encoder with button + 2 tactile buttons
- Output: USB MIDI via TinyUSB

**Software stack:**
- Language: C++17
- Framework: Arduino (Earle Philhower core for RP2040)
- Build system: PlatformIO
- Testing: Unity test framework

**Architecture:**
- State pattern for operating modes
- DI container for dependency injection
- Interface design for testability
- Separation of hardware abstraction and application logic

**Test environment:**
- Native target for testing without hardware
- Mock objects for hardware interfaces
- TDD development approach

## 6. Monetize - How will this make money?

**Open source:**
- Project distributed under open-source license
- Goal: create useful tool for community
- Possibility of self-assembly

**Potential models:**
- Sale of ready-made devices (long-term perspective)
- Customized builds on order
- Community donations

**Current focus:**
- Functional prototype for real-world use
- Code quality and documentation
- User and contributor community

## 7. UI/UX - How should this look and feel?

**Physical interface:**
- Encoder: menu navigation, program switching
- Encoder button: selection/confirmation
- Additional buttons: forward/back for quick switching

**Display (OLED 128x64):**
- Main mode: large program number + name
- Configuration menu: lists with highlighted item
- Mode and status indication
- Minimalist, readable font

**User experience:**
- Intuitive menu navigation
- Quick access to main functions
- Predictable behavior in stage conditions
- Low response latency

**Limitations:**
- Monochrome display
- Limited display area
- No touch input

## 8. Deployment - Where and how will this ship?

**Target platform:**
- Raspberry Pi Pico (RP2040)
- Arduino framework with TinyUSB
- PlatformIO for building and flashing

**Firmware:**
- Via USB Mass Storage Device (bootloader)
- PlatformIO upload command
- Manual flashing via BOOTSEL mode

**Distribution:**
- Source code on GitHub
- Build instructions
- Ready .uf2 files for flashing

**Operational model:**
- Standalone device
- No constant computer connection required
- State preservation between power cycles
- Direct configuration on device

## 9. Usage model and constraints

**Scale:**
- Personal use by musicians
- Small music collectives
- No multi-user access requirements

**Trust model:**
- Device physically with user
- No network access or external APIs
- All data stored locally on device

**Security requirements:**
- Protection against accidental reset
- Predictable behavior during power failures
- No data encryption requirements

**Non-requirements:**
- Multi-tenancy
- Internet access
- Cloud synchronization
- Role-based access control
- Change audit
- Regulatory compliance (HIPAA, PCI DSS, etc.)