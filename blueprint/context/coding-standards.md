# Coding Standards

> C++ embedded project for Raspberry Pi Pico MIDI controller

## C++ Standards

- C++17 standard (`-std=c++17`)
- Follow Arduino framework conventions for Raspberry Pi Pico
- Use PlatformIO build system
- Header files (.h) for declarations, source files (.cpp) for implementations
- Include guards in header files

## Architecture

- Interface-based design with abstract base classes
- Clean separation between hardware abstraction and application logic
- Dependency injection for testability
- Modular components with single responsibility

## Naming Conventions

- Classes: PascalCase (`MidiPatchBoxApplication`, `ProgramSelector`)
- Methods: camelCase (`selectNextProgram`, `sendMidiMessage`)
- Variables: camelCase (`currentProgram`, `buttonState`)
- Constants: SCREAMING_SNAKE_CASE (`MAX_PROGRAMS`, `DISPLAY_WIDTH`)
- Files: Match class names (`MidiPatchBoxApplication.h`, `MidiPatchBoxApplication.cpp`)

## File Organization

- Application logic: `src/app/`
- Hardware abstraction: `src/hardware/`
- Interfaces: `src/app/*Interface.h`
- Tests: `test/` with matching directory structure
- PlatformIO configuration: `platformio.ini`

## Memory Management

- Stack allocation preferred for embedded systems
- Avoid dynamic memory allocation when possible
- Use `const` for read-only data
- Preprocessor constants for configuration values

## Testing

- Unity test framework for unit tests
- Test files in `test/` directory mirroring source structure
- Hardware interfaces mocked for unit testing
- Run tests with `pio test -e native`
- Test naming: `test_` prefix (`test_program_selector.cpp`)

## Documentation

- Doxygen-style comments for public APIs
- Brief descriptions of class responsibilities
- Document hardware dependencies and assumptions
- Keep README.md up to date with build instructions

## Build Commands

- Build: `pio run -e pico`
- Upload: `pio run -e pico -t upload`
- Tests: `pio test -e native`
- Clean: `pio run -t clean`

This is an embedded system project focusing on reliability and testability for MIDI controller functionality.