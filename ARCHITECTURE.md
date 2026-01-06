# Architecture

## Overview

MIDI Patch Box is a programmable USB MIDI controller built on the RP2040 microcontroller platform. The project implements a clean, modular architecture with strict separation of concerns, enabling reliable MIDI program selection through hardware buttons and rotary encoder input.

The architecture follows modern C++ design principles with interface-based abstraction, dependency injection, and comprehensive unit testing using the Test-Driven Development (TDD) approach.

## Architectural Principles

### Core Design Principles

- **Interface Segregation**: Each interface defines a single, focused responsibility
- **Dependency Inversion**: Application layer depends on abstractions, not concrete implementations
- **Single Responsibility**: Each class has one clear purpose and reason to change
- **Test-Driven Development**: Business logic is developed test-first with comprehensive coverage
- **Fluent Interface**: Method chaining for intuitive configuration (`setUserInput()->setProgramSelector()`)

### Key Architectural Decisions

1. **Layered Architecture**: Clear separation between application logic, hardware drivers, and testing
2. **Interface-Based Design**: All cross-layer communication happens through abstract interfaces
3. **Dependency Injection**: Components receive their dependencies through setter methods
4. **Mock-Based Testing**: Hardware dependencies are mocked for isolated unit testing
5. **State Machine Pattern**: Application flow managed through discrete states with clear transitions
6. **Factory Pattern**: State creation abstracted through factory interfaces for flexible instantiation

## System Architecture

```mermaid
graph LR
    subgraph "Application Layer (src/app/)"
        APP[MidiPatchBoxApplication]
        SM[StateMachine]
        SPS[SplashScreenState]
        MAS[MainApplicationState]
        PS[ProgramSelector]
        PB[ProgramsBank]
        BTN[Button]
        ENC[Encoder]
        UI[UserInput]
        SF[StateFactory]
        MASF[MainApplicationStateFactory]
        
        subgraph "Interfaces"
            UII[UserInputInterface]
            PSI[ProgramSelectorInterface]
            MCI[MidiControllerInterface]
            IOI[IoDriverInterface]
            PSVI[ProgramSelectionViewInterface]
            SSVI[SplashScreenViewInterface]
            PBI[ProgramsBankInterface]
            SI[StateInterface]
            SMI[StateMachineInterface]
            SFI[StateFactoryInterface]
            EI[EncoderInterface]
            BI[ButtonInterface]
        end
    end
    
    subgraph "Hardware Layer (src/hardware/)"
        MC[MidiController]
        AIO[ArduinoIoDriver]
        DPSV[DisplayProgramSelectionView]
        DSSV[DisplaySplashScreenView]
        DBSSV[DisplayBitmapSplashScreenView]
    end
    
    subgraph "Test Layer (test/)"
        TESTS[Unit Tests]
        MOCKS[Mock Objects]
        MOCKIO[MockIoDriver]
        MOCKBTN[MockButton]
        MOCKENC[MockEncoder]
    end
    
    subgraph "External Dependencies"
        ARDUINO[Arduino Framework]
        TINYUSB[Adafruit TinyUSB]
        UNITY[Unity Test Framework]
        ADAFRUIT[Adafruit GFX/SSD1306]
    end
    
    APP --> SM
    APP --> UII
    APP --> PSI
    APP --> MCI
    APP --> PSVI
    SM --> SMI
    SM --> SI
    SPS --> SI
    SPS --> SSVI
    SPS --> IOI
    SPS --> SFI
    MAS --> SI
    MAS --> UII
    MAS --> PSI
    MAS --> MCI
    MAS --> PSVI
    MAS --> PBI
    UI --> UII
    UI --> BI
    UI --> EI
    BTN --> BI
    BTN --> IOI
    ENC --> EI
    ENC --> IOI
    PS --> PSI
    PB --> PBI
    SF --> SFI
    MASF --> SFI
    
    MC -.-> MCI
    AIO -.-> IOI
    DPSV -.-> PSVI
    DSSV -.-> SSVI
    DBSSV -.-> SSVI
    
    TESTS --> MOCKS
    TESTS --> MOCKIO
    TESTS --> MOCKBTN
    TESTS --> MOCKENC
    TESTS --> APP
    TESTS --> SM
    TESTS --> SPS
    TESTS --> MAS
    TESTS --> PS
    TESTS --> PB
    TESTS --> BTN
    TESTS --> ENC
    TESTS --> UI
    
    AIO --> ARDUINO
    MC --> TINYUSB
    DPSV --> ADAFRUIT
    DSSV --> ADAFRUIT
    DBSSV --> ADAFRUIT
    TESTS --> UNITY
    
    classDef appLayer fill:#e1f5fe
    classDef hardwareLayer fill:#f3e5f5
    classDef testLayer fill:#e8f5e8
    classDef external fill:#fff3e0
    
    class APP,SM,SPS,MAS,PS,PB,BTN,ENC,UI,SF,MASF,UII,PSI,MCI,IOI,PSVI,SSVI,PBI,SI,SMI,SFI,EI,BI appLayer
    class MC,AIO,DPSV,DSSV,DBSSV hardwareLayer
    class TESTS,MOCKS,MOCKIO,MOCKBTN,MOCKENC testLayer
    class ARDUINO,TINYUSB,UNITY,ADAFRUIT external
```

## Layers

### Application Layer (`src/app/`)

The application layer contains the core business logic and is designed to be platform-independent. All components in this layer are thoroughly tested using TDD methodology.

**Key Characteristics:**
- Platform-agnostic business logic
- Interface-based communication with hardware
- Comprehensive unit test coverage
- No direct hardware dependencies

**Components:**
- [`MidiPatchBoxApplication`](src/app/MidiPatchBoxApplication.h) - Main application coordinator
- [`StateMachine`](src/app/StateMachine.h) - State management and transitions
- [`SplashScreenState`](src/app/SplashScreenState.h) - Initial application state with splash screen
- [`MainApplicationState`](src/app/MainApplicationState.h) - Main operational state handling user input
- [`ProgramSelector`](src/app/ProgramSelector.h) - Program list management and selection logic
- [`ProgramsBank`](src/app/ProgramsBank.h) - Program name management
- [`UserInput`](src/app/UserInput.h) - User input coordination and button management
- [`Button`](src/app/Button.h) - Button state management with debouncing
- [`Encoder`](src/app/Encoder.h) - Rotary encoder input handling
- [`StateFactory`](src/app/StateFactory.h) - Abstract factory for state creation
- [`MainApplicationStateFactory`](src/app/MainApplicationStateFactory.h) - Concrete factory for main state
- Abstract interfaces for hardware abstraction

### Hardware Layer (`src/hardware/`)

The hardware layer provides concrete implementations of the application interfaces, handling direct interaction with the RP2040 hardware and external libraries.

**Key Characteristics:**
- Platform-specific implementations
- Direct hardware interaction
- Implements application layer interfaces
- Manual testing approach

**Components:**
- [`MidiController`](src/hardware/MidiController.h) - USB MIDI communication via Adafruit TinyUSB
- [`ArduinoIoDriver`](src/hardware/ArduinoIoDriver.h) - Arduino-specific I/O operations implementation
- [`DisplayProgramSelectionView`](src/hardware/DisplayProgramSelectionView.h) - Visual program selection feedback via display
- [`DisplaySplashScreenView`](src/hardware/DisplaySplashScreenView.h) - Text-based splash screen display
- [`DisplayBitmapSplashScreenView`](src/hardware/DisplayBitmapSplashScreenView.h) - Bitmap-based splash screen display

### Test Layer (`test/`)

The test layer provides comprehensive unit testing infrastructure with mock objects for hardware abstraction.

**Key Characteristics:**
- Unity framework-based testing
- Mock objects for hardware isolation
- Centralized mock management
- TDD workflow support

**Structure:**
- `test/mocks/` - Centralized mock object definitions ([`MockIoDriver`](test/mocks/MockIoDriver.h), [`MockButton`](test/mocks/MockButton.h), [`MockEncoder`](test/mocks/MockEncoder.h))
- `test/test_*/` - Component-specific test suites (application, state_machine, splash_screen_state, main_application_state, program_selector, programs_bank, button, encoder, user_input)
- Native platform execution for fast feedback

## Core Components

### MidiPatchBoxApplication

**Purpose**: Main application coordinator that orchestrates all system components and handles the primary application loop.

**Interfaces Used**:
- [`UserInputInterface`](src/app/UserInputInterface.h) - For reading button states
- [`ProgramSelectorInterface`](src/app/ProgramSelectorInterface.h) - For program management
- [`MidiControllerInterface`](src/app/MidiControllerInterface.h) - For MIDI communication
- [`ProgramSelectionViewInterface`](src/app/ProgramSelectionViewInterface.h) - For displaying program selection
- [`StateMachine`](src/app/StateMachine.h) - For application state management

**Key Responsibilities**:
- Coordinate component interactions through dependency injection
- Manage application lifecycle (begin/tick)
- Provide centralized component access

**Dependencies**: Receives all dependencies through fluent setter methods

**Testing**: Comprehensive unit tests with mocked dependencies

```mermaid
graph LR
    APP[MidiPatchBoxApplication] --> SM[StateMachine]
    APP --> UII[UserInputInterface]
    APP --> PSI[ProgramSelectorInterface]
    APP --> MCI[MidiControllerInterface]
    APP --> PSVI[ProgramSelectionViewInterface]
    
    SM -.-> SPS[SplashScreenState]
    SM -.-> MAS[MainApplicationState]
    UII -.-> UI[UserInput]
    PSI -.-> PS[ProgramSelector]
    MCI -.-> MC[MidiController]
    PSVI -.-> DPSV[DisplayProgramSelectionView]
```

### ProgramSelector

**Purpose**: Manages the list of MIDI programs and handles program selection logic with wrap-around behavior.

**Interface**: Implements [`ProgramSelectorInterface`](src/app/ProgramSelectorInterface.h)

**Key Features**:
- Dynamic program list configuration
- Circular program selection (wraps to first after last)
- Memory management for program arrays
- Fluent interface for configuration

**Dependencies**: None (self-contained business logic)

**Testing**: Extensive unit tests covering all selection scenarios

### Button

**Purpose**: Provides debounced button state management with configurable timing thresholds.

**Interface**: Implements [`ButtonInterface`](src/app/ButtonInterface.h)

**Interface Used**: [`IoDriverInterface`](src/app/IoDriverInterface.h) - For GPIO operations

**Key Features**:
- 300ms debounce threshold
- State change detection
- Hardware abstraction through IoDriver
- Time-based debouncing logic

**Dependencies**: Requires IoDriverInterface implementation

**Testing**: Unit tested with MockIoDriver for time and state simulation

### UserInput

**Purpose**: Application-layer component that coordinates user input from buttons and encoder through interface abstraction.

**Interface**: Implements [`UserInputInterface`](src/app/UserInputInterface.h)

**Key Features**:
- Manages multiple button inputs (user button, right button, encoder button)
- Manages rotary encoder input
- Hardware abstraction through interface dependencies
- Configurable with ready-made control element instances

**Dependencies**: [`ButtonInterface`](src/app/ButtonInterface.h), [`EncoderInterface`](src/app/EncoderInterface.h)

**Testing**: Comprehensive unit tests with [`MockButton`](test/mocks/MockButton.h) and [`MockEncoder`](test/mocks/MockEncoder.h)

### StateMachine

**Purpose**: Manages application states and handles transitions between different operational modes.

**Interface**: Implements [`StateMachineInterface`](src/app/StateMachineInterface.h)

**Key Features**:
- State lifecycle management (enter/update/exit)
- Automatic state cleanup and memory management
- Template-based state transitions
- State machine reference injection into states

**Dependencies**: Manages [`StateInterface`](src/app/StateInterface.h) implementations

**Testing**: Unit tested with mock states for transition verification

### SplashScreenState

**Purpose**: Initial application state that displays splash screen for a configured duration before transitioning to main application.

**Interface**: Implements [`StateInterface`](src/app/StateInterface.h)

**Key Features**:
- 2-second splash screen duration
- Automatic transition to [`MainApplicationState`](src/app/MainApplicationState.h)
- Factory-based state creation
- Display abstraction through [`SplashScreenViewInterface`](src/app/SplashScreenViewInterface.h)

**Dependencies**: [`SplashScreenViewInterface`](src/app/SplashScreenViewInterface.h), [`IoDriverInterface`](src/app/IoDriverInterface.h), [`StateFactoryInterface`](src/app/StateFactoryInterface.h)

**Testing**: Unit tested with mock dependencies and time simulation

### MainApplicationState

**Purpose**: Primary operational state handling user input, program selection, and MIDI communication.

**Interface**: Implements [`StateInterface`](src/app/StateInterface.h)

**Key Features**:
- User input processing (buttons and encoder)
- Program selection logic with encoder rotation
- MIDI program change transmission
- Display updates for program selection
- Integration with [`ProgramsBank`](src/app/ProgramsBank.h) for program names

**Dependencies**: [`UserInputInterface`](src/app/UserInputInterface.h), [`ProgramSelectorInterface`](src/app/ProgramSelectorInterface.h), [`MidiControllerInterface`](src/app/MidiControllerInterface.h), [`ProgramSelectionViewInterface`](src/app/ProgramSelectionViewInterface.h), [`ProgramsBankInterface`](src/app/ProgramsBankInterface.h)

**Testing**: Comprehensive unit tests with mocked dependencies

### ProgramsBank

**Purpose**: Manages program names and provides lookup functionality for MIDI program numbers.

**Interface**: Implements [`ProgramsBankInterface`](src/app/ProgramsBankInterface.h)

**Key Features**:
- Program name storage (up to 128 programs)
- Fluent interface for program addition
- Name lookup by program number
- Memory-efficient storage with fixed-size names (16 characters)

**Dependencies**: None (self-contained data structure)

**Testing**: Unit tested for storage and retrieval operations

### Encoder

**Purpose**: Handles rotary encoder input with proper state tracking and rotation detection.

**Interface**: Implements [`EncoderInterface`](src/app/EncoderInterface.h)

**Key Features**:
- Dual-pin encoder reading (A and B phases)
- Clockwise and counter-clockwise rotation detection
- State change tracking with proper debouncing
- Hardware abstraction through [`IoDriverInterface`](src/app/IoDriverInterface.h)

**Dependencies**: [`IoDriverInterface`](src/app/IoDriverInterface.h)

**Testing**: Unit tested with [`MockIoDriver`](test/mocks/MockIoDriver.h) for rotation simulation

### MidiController

**Purpose**: Handles USB MIDI communication using the Adafruit TinyUSB library for program change messages.

**Interface**: Implements [`MidiControllerInterface`](src/app/MidiControllerInterface.h)

**Key Features**:
- USB MIDI device functionality
- Program change message transmission
- Configurable MIDI channel support
- USB device descriptor management

**Dependencies**: Adafruit TinyUSB Library

**Testing**: Manual testing with MIDI monitoring tools

### ArduinoIoDriver

**Purpose**: Provides Arduino-specific implementation of I/O operations for hardware abstraction.

**Interface**: Implements [`IoDriverInterface`](src/app/IoDriverInterface.h)

**Key Features**:
- Direct Arduino API mapping (digitalRead, pinMode, delay, millis)
- Pin mode configuration support
- Time-based operations for debouncing
- Hardware abstraction for cross-platform testing

**Dependencies**: Arduino Framework

**Testing**: Abstracted through [`MockIoDriver`](test/mocks/MockIoDriver.h) for unit tests

### DisplayProgramSelectionView

**Purpose**: Provides visual feedback for program selection through display output, enabling users to see the currently selected program number.

**Interface**: Implements [`ProgramSelectionViewInterface`](src/app/ProgramSelectionViewInterface.h)

**Key Features**:
- Real-time program number display updates
- OLED display integration support
- Fluent interface for method chaining
- Hardware abstraction for different display types

**Dependencies**: Display hardware libraries (OLED, LCD, etc.)

**Testing**: Unit tested through [`MockProgramSelectionView`](test/mocks/MockProgramSelectionView.h)

## Design Patterns

### State Machine Pattern

The application uses a finite state machine to manage different operational modes with clear state transitions and lifecycle management.

```cpp
class StateMachine : public StateMachineInterface {
public:
    void changeState(StateInterface* newState) override {
        if (currentState) {
            currentState->exit();
            delete currentState;
        }
        currentState = newState;
        if (currentState) {
            currentState->setStateMachine(this);
            currentState->enter();
        }
    }
};
```

**Key Benefits**:
- Clear separation of application modes
- Automatic state lifecycle management
- Memory safety with RAII principles
- Testable state transitions

### Factory Pattern

State creation is abstracted through factory interfaces, enabling flexible state instantiation and dependency injection.

```cpp
class MainApplicationStateFactory : public StateFactory {
public:
    StateInterface* createMainApplicationState() override {
        return (new MainApplicationState())
            ->setUserInput(userInput)
            ->setProgramSelector(programSelector)
            ->setMidiController(midiController)
            ->setProgramSelectionView(programSelectionView)
            ->setProgramsBank(programsBank);
    }
};
```

**Key Benefits**:
- Centralized state creation logic
- Dependency injection at creation time
- Easy testing with mock factories
- Flexible state configuration

### Dependency Injection

Components receive their dependencies through setter methods, enabling flexible configuration and easy testing.

```cpp
app.setProgramSelector(&programSelector)
    ->setUserInput(&userInput)
    ->setMidiController(&midiController)
    ->begin();
```

### Interface Segregation

Each interface defines a minimal, focused contract:

```cpp
class UserInputInterface {
public:
    virtual void update() = 0;
    virtual bool userButtonIsPressed() = 0;
    virtual bool rightButtonIsPressed() = 0;
};

class ProgramSelectionViewInterface {
public:
    virtual ProgramSelectionViewInterface* setSelectedProgramNumber(int programNumber) = 0;
    virtual ~ProgramSelectionViewInterface() = default;
};
```

### Mock Objects

Test doubles provide controlled behavior for unit testing:

```cpp
class MockIoDriver : public IoDriverInterface {
public:
    int digitalRead(int pin) override {
        return pin == BUTTON_PIN ? pinState : LOW;
    }
    // ... controlled test behavior
};
```

### Fluent Interface

Method chaining provides intuitive configuration:

```cpp
app.setProgramSelector(&programSelector)
    ->setUserInput(&userInput)
    ->setMidiController(&midiController)
    ->setProgramSelectionView(&displayView)
    ->begin();
```

## Dependencies

```mermaid
graph LR
    subgraph "Application Dependencies"
        APP[MidiPatchBoxApplication] --> SM[StateMachine]
        APP --> UII[UserInputInterface]
        APP --> PSI[ProgramSelectorInterface]
        APP --> MCI[MidiControllerInterface]
        APP --> PSVI[ProgramSelectionViewInterface]
        
        SM --> SMI[StateMachineInterface]
        SM --> SI[StateInterface]
        SPS[SplashScreenState] --> SI
        SPS --> SSVI[SplashScreenViewInterface]
        SPS --> IOI[IoDriverInterface]
        SPS --> SFI[StateFactoryInterface]
        MAS[MainApplicationState] --> SI
        MAS --> UII
        MAS --> PSI
        MAS --> MCI
        MAS --> PSVI
        MAS --> PBI[ProgramsBankInterface]
        
        UI[UserInput] --> UII
        UI --> IOI
        UI --> BTN[Button]
        UI --> ENC[Encoder]
        BTN --> IOI
        ENC --> IOI
        PS[ProgramSelector] --> PSI
        PB[ProgramsBank] --> PBI
        SF[StateFactory] --> SFI
        MASF[MainApplicationStateFactory] --> SFI
    end
    
    subgraph "Hardware Dependencies"
        AIO[ArduinoIoDriver] --> IOI
        AIO --> ARDUINO[Arduino Framework]
        
        MC[MidiController] --> MCI
        MC --> TINYUSB[Adafruit TinyUSB Library]
        
        DPSV[DisplayProgramSelectionView] --> PSVI
        DPSV --> ADAFRUIT[Adafruit GFX/SSD1306]
        DSSV[DisplaySplashScreenView] --> SSVI
        DSSV --> ADAFRUIT
        DBSSV[DisplayBitmapSplashScreenView] --> SSVI
        DBSSV --> ADAFRUIT
    end
    
    subgraph "Test Dependencies"
        TESTS[Unit Tests] --> UNITY[Unity Framework]
        TESTS --> MOCKS[Mock Objects]
        MOCKS --> IOI
        MOCKS --> UII
        MOCKS --> MCI
        MOCKS --> PSI
        MOCKS --> PSVI
        MOCKS --> SSVI
        MOCKS --> PBI
        MOCKS --> SI
        MOCKS --> SMI
        MOCKS --> SFI
    end
    
    classDef interface fill:#fff2cc
    classDef concrete fill:#d5e8d4
    classDef external fill:#f8cecc
    
    class UII,PSI,MCI,IOI,PSVI,SSVI,PBI,SI,SMI,SFI interface
    class APP,SM,SPS,MAS,BTN,ENC,PS,PB,UI,AIO,MC,DPSV,DSSV,DBSSV,SF,MASF,TESTS,MOCKS concrete
    class ARDUINO,TINYUSB,UNITY,ADAFRUIT external
```

### Dependency Flow

1. **Application Layer**: Depends only on abstract interfaces
2. **Hardware Layer**: Implements interfaces and depends on external libraries
3. **Test Layer**: Uses mock implementations of interfaces for isolation

### External Dependencies

- **Arduino Framework**: RP2040 hardware abstraction and GPIO operations
- **Adafruit TinyUSB Library**: USB MIDI device functionality
- **Unity Framework**: Unit testing infrastructure

## Testing Strategy

### Test-Driven Development (TDD)

The application layer follows strict TDD methodology:

1. **Red**: Write failing test for new functionality
2. **Green**: Implement minimal code to pass the test
3. **Refactor**: Improve code while maintaining test coverage

### Unit Testing Architecture

```mermaid
graph TB
    subgraph "Test Environment"
        TEST[Test Suite]
        UNITY[Unity Framework]
        NATIVE[Native Platform]
    end
    
    subgraph "Application Under Test"
        APP[Application Components]
        INTERFACES[Abstract Interfaces]
    end
    
    subgraph "Test Doubles"
        MOCKS[Mock Objects]
        STUBS[Test Stubs]
    end
    
    TEST --> UNITY
    TEST --> APP
    TEST --> MOCKS
    
    APP --> INTERFACES
    MOCKS -.-> INTERFACES
    
    NATIVE --> TEST
```

### Mock Strategy

- **Centralized Mocks**: All mock objects stored in `test/mocks/` directory
- **Interface Compliance**: Mocks implement the same interfaces as real components
- **Controlled Behavior**: Mocks provide predictable, testable behavior
- **State Simulation**: Time and hardware state can be controlled for testing

### Test Organization

```
test/
├── mocks/
│   ├── MockIoDriver.h              # GPIO operations mock
│   ├── MockButton.h                # Button interface mock
│   └── MockEncoder.h               # Encoder interface mock
├── test_button/
│   └── test_button.cpp             # Button logic tests
├── test_encoder/
│   └── test_encoder.cpp            # Encoder logic tests
├── test_program_selector/
│   └── test_program_selector.cpp   # Program selection tests
├── test_programs_bank/
│   └── test_programs_bank.cpp      # Program name storage tests
├── test_user_input/
│   └── test_user_input.cpp         # User input coordination tests
├── test_state_machine/
│   └── test_state_machine.cpp      # State machine tests
├── test_splash_screen_state/
│   └── test_splash_screen_state.cpp # Splash screen state tests
├── test_main_application_state/
│   └── test_main_application_state.cpp # Main application state tests
├── test_splash_screen_view/
│   └── test_splash_screen_view.cpp  # Splash screen view tests
└── test_midi_patch_box_application/
    └── test_midi_patch_box_application.cpp  # Main app tests
```

### Testing Scope

- **Unit Tests**: Application layer components (100% coverage goal)
- **Manual Tests**: Hardware layer functionality and system integration

**Note**: System and integration testing is performed manually due to hardware dependencies and real-time MIDI communication requirements.

## Build and Development

### Platform Configuration

**Target Platform**: RP2040 (Raspberry Pi Pico)
- **Framework**: Arduino with Earle Philhower core
- **Build System**: PlatformIO
- **Language Standard**: C++17

**Test Platform**: Native
- **Framework**: Unity
- **Execution**: Local development machine
- **Purpose**: Fast feedback for TDD workflow

### Build Environments

```ini
[env:pico]
platform = https://github.com/maxgerhardt/platform-raspberrypi.git
board = pico
framework = arduino
board_build.core = earlephilhower
lib_deps = adafruit/Adafruit TinyUSB Library
build_flags = -DUSE_TINYUSB

[env:native]
platform = native
build_flags = -std=c++17
test_framework = unity
lib_deps = throwtheswitch/Unity@^2.6.0
test_build_src = yes
build_src_filter = +<app/*>
```

### Development Workflow

1. **TDD Cycle**: Write tests first for application logic
2. **Native Testing**: Run tests on development machine for fast feedback
3. **Hardware Integration**: Test on actual RP2040 hardware
4. **MIDI Validation**: Verify MIDI output with external tools

### Build Commands

```bash
# Run unit tests (fast feedback)
pio test -e native

# Build for hardware
pio run -e pico

# Upload to device
pio run -e pico -t upload

# Clean build
pio run -t clean
```

### Code Organization

- **Header Guards**: All headers use `#pragma once`
- **Interface Naming**: Interfaces end with "Interface" suffix
- **File Structure**: Logical grouping by layer and responsibility
- **Dependency Direction**: Always from concrete to abstract

This architecture ensures maintainable, testable, and extensible code that can evolve with changing requirements while maintaining reliability and performance.