# MIDI Patch Box

A programmable USB MIDI controller based on the RP2040 microcontroller, designed for selecting MIDI programs using buttons and rotary encoder. The controller sends MIDI program change messages to musical instruments and other MIDI devices, with the selected program displayed on the controller's screen.

## Features

- **RP2040-based**: Built on the powerful Raspberry Pi Pico microcontroller
- **USB MIDI Interface**: Native USB MIDI communication using TinyUSB
- **State Pattern Architecture**: Clean state-based UI flow with DI container dependency injection
- **Program Selection**: Navigate through MIDI programs using buttons and rotary encoder
- **Setlist Management**: Create and edit custom setlists with program selection and ordering
- **Menu System**: Unified menu architecture using MenuController pattern for consistent navigation
- **Program Editing**: Edit program names and numbers directly on the device with dual-mode interface
- **Real-time Display**: Shows currently selected program and menu navigation on OLED screen
- **Modular Architecture**: Clean separation of concerns with interface-based design
- **Test-Driven Development**: Comprehensive unit test suite with Unity framework and mock objects

## Hardware Requirements

- **Microcontroller**: Raspberry Pi Pico (RP2040)
- **Input**: Push buttons and rotary encoder for program navigation
- **Display**: OLED SSD1306 128x64 (I2C) for program information display
- **USB Connection**: For MIDI communication with host devices

### Display Specifications

- **Model**: SSD1306 OLED Display
- **Resolution**: 128x64 pixels
- **Interface**: I2C (4-pin connection)
- **Voltage**: 3.3V/5V compatible
- **Size**: 0.96" diagonal (typical)

## Software Architecture

The project follows a modern embedded software architecture with clear separation of concerns, dependency injection, and comprehensive testability.

### Architectural Patterns

- **State Pattern**: The application uses a state machine (`StateMachine`) to manage different operating modes (Splash, Main, Configuration, Setlist Editing)
- **Dependency Injection**: A DI container (`DiContainer`) manages component dependencies for easy testing and configuration
- **Interface-Based Design**: All cross-layer communication happens through abstract interfaces
- **Unified Menu Controller**: Navigation menus use consistent MenuController pattern for maintainable menu architecture
- **Test-Driven Development**: Logic is developed test-first with Unity framework on native platform

### Core Components

#### Application Layer (src/app/)
- **[`MidiPatchBoxApplication`](src/app/MidiPatchBoxApplication.h)**: Main application controller
- **[`StateMachine`](src/app/StateMachine.h)**: Manages state transitions and lifecycle
- **[`DiContainer`](src/app/DiContainer.h)**: Dependency injection container
- **[`ProgramsBank`](src/app/ProgramsBank.h)**: Stores and manages MIDI programs with names
- **[`ProgramSelector`](src/app/ProgramSelector.h)**: Program selection logic
- **[`MenuController`](src/app/MenuController.h)**: Unified menu navigation and item management
- **[`SetlistManager`](src/app/SetlistManager.h)**: Manages program lists for setlists
- **[`Context`](src/app/Context.h)**: Shared data structure for application context
- **[`SetlistMenuViewDecorator`](src/app/SetlistMenuViewDecorator.h)**: View decorator for setlist menu display

#### State Management
- **[`MainApplicationState`](src/app/MainApplicationState.h)**: Performance mode for program selection
- **[`ConfigMenuState`](src/app/ConfigMenuState.h)**: Configuration menu navigation using MenuController
- **[`SetlistMenuState`](src/app/SetlistMenuState.h)**: Setlist management interface with dual-mode editing
- **[`EditSetlistState`](src/app/EditSetlistState.h)**: Setlist item editing with specialized interface
- **[`SplashScreenState`](src/app/SplashScreenState.h)**: Startup splash screen

#### Hardware Abstraction (src/hardware/)
- **[`UserInput`](src/app/UserInput.h)**: Button and encoder input handling
- **[`MidiController`](src/hardware/MidiController.h)**: USB MIDI communication
- **[`ArduinoIoDriver`](src/hardware/ArduinoIoDriver.h)**: GPIO operations for RP2040
- **Display Views**: Various display renderers for different states

### Interface Layer

The project defines clear interfaces for testability and hardware independence:

- **State Interfaces**: `StateInterface`, `StateMachineInterface`, `StateFactoryInterface`
- **Input Interfaces**: `UserInputInterface`, `ButtonInterface`, `EncoderInterface`
- **Display Interfaces**: `ProgramSelectionViewInterface`, `SplashScreenViewInterface`, `ConfigMenuViewInterface`, `EditSetlistViewInterface`, `MenuLayoutViewInterface`
- **Data Interfaces**: `ProgramsBankInterface`, `ProgramSelectorInterface`, `SetlistManagerInterface`
- **Hardware Interfaces**: `MidiControllerInterface`, `IoDriverInterface`
- **Menu Interfaces**: `MenuControllerInterface`, `MenuLayoutViewInterface`
- **DI Interface**: `DiContainerInterface`

### Data Model

- **ProgramBank**: Stores MIDI program numbers (0-127) with names
- **Setlist**: Ordered collection of program references for performance sets managed by SetlistManager
- **SystemState**: Tracks active bank, setlist, selected program, and operating mode through Context
- **Context**: Shared data structure that connects SetlistManager with application states

This architecture enables reliable operation, easy testing through mock objects, and future extensions while maintaining clean separation between application logic and hardware dependencies.

## Dependencies

- **PlatformIO**: Build system and package manager
- **Arduino Framework**: For RP2040 development (Earle Philhower core)
- **Adafruit TinyUSB Library**: USB MIDI functionality
- **Adafruit SSD1306**: OLED display driver library
- **Adafruit GFX Library**: Graphics primitives for display rendering
- **Unity**: Unit testing framework

## Building the Project

### Prerequisites

1. Install [PlatformIO](https://platformio.org/)
2. Clone this repository
3. Navigate to the project directory

### Build Commands

```bash
# Build for Raspberry Pi Pico
pio run -e pico

# Upload to device
pio run -e pico -t upload

# Run unit tests
pio test -e native

# Clean build
pio run -t clean

# Run specific test suite
pio test -e native -f test_program_selector
pio test -e native -f test_setlist_menu_state
pio test -e native -f test_main_application_state
pio test -e native -f test_menu_controller
pio test -e native -f test_setlist_manager
```

## Configuration

### Program Setup

Programs are configured in [`main.cpp`](src/main.cpp):

```cpp
// Initialize programs bank with program names
programsBank.addProgram(0, "Clean")
    ->addProgram(41, "Viola")
    ->addProgram(112, "Reverse");

// SetlistManager automatically initialized with [0, 41, 112]
SetlistManager setlistManager;  // Static storage, initialized with [0, 41, 112]

// Configure ProgramSelector with SetlistManager
programSelector.setPrograms(setlistManager.getPrograms(), setlistManager.getProgramCount());
```

### MIDI Channel

The MIDI channel is configurable:

```cpp
const uint8_t MIDI_CHANNEL = 0;  // Channel 1 (0-based)
```

### USB Descriptors

Device identification can be customized:

```cpp
USBDevice.setManufacturerDescriptor("iv660");
USBDevice.setProductDescriptor("MIDI Patch Box");
USBDevice.setSerialDescriptor("0001");
```

## Display Setup

### Hardware Connection

Connect the OLED display to your Raspberry Pi Pico using I2C:

| OLED Pin | Pico Pin | Description |
|----------|----------|-------------|
| VCC      | 3V3      | Power (3.3V) |
| GND      | GND      | Ground |
| SDA      | GP20     | I2C Data |
| SCL      | GP21     | I2C Clock |

### Wiring Diagram

```
Raspberry Pi Pico          SSD1306 OLED
┌─────────────────┐        ┌──────────────┐
│             3V3 │────────│ VCC          │
│             GND │────────│ GND          │
│        GP20/SDA │────────│ SDA          │
│        GP21/SCL │────────│ SCL          │
└─────────────────┘        └──────────────┘
```

### Custom Pin Configuration

If you need to use different I2C pins, modify the display initialization in [`main.cpp`](src/main.cpp):

```cpp
// Default pins: SDA=20, SCL=21, I2C Address=0x3C
DisplayProgramSelectionView displayView;

// Custom pins: SDA=18, SCL=19, I2C Address=0x3D
DisplayProgramSelectionView displayView(18, 19, 0x3D);
```

### Display Features

- **Startup Screen**: Shows "MIDI Patch Box" on initialization with bitmap support
- **Program Display**: Large program number with "PROGRAM" label
- **Menu Display**: Unified menu rendering via MenuLayoutViewInterface
- **Auto-centering**: Text automatically centers for optimal readability
- **Real-time Updates**: Display updates immediately when program changes
- **Edit Mode Feedback**: Visual indication during edit mode in SetlistMenuState

## Hardware Interface

### Button and Encoder Connections

| Component | GPIO Pin | Function |
|-----------|----------|----------|
| User Button | GP24 | Left navigation / previous program |
| Right Button | GP17 | Right navigation / next program |
| Encoder Button | GP29 | Selection / configuration mode (long press) |
| Encoder A | GP27 | Rotation detection (clockwise) |
| Encoder B | GP28 | Rotation detection (counter-clockwise) |
| I2C SDA | GP20 | Display data line |
| I2C SCL | GP21 | Display clock line |

### Custom Pin Configuration

To use different pins, modify the initialization in [`main.cpp`](src/main.cpp):

```cpp
// Button pins
Button userButton(CUSTOM_USER_PIN);
Button rightButton(CUSTOM_RIGHT_PIN);
Button encoderButton(CUSTOM_ENCODER_BTN_PIN);

// Encoder pins  
encoder.setPinA(CUSTOM_ENCODER_A_PIN)
    ->setPinB(CUSTOM_ENCODER_B_PIN);

// Display pins (constructor parameters)
DisplayProgramSelectionView displayView(CUSTOM_SDA_PIN, CUSTOM_SCL_PIN, I2C_ADDRESS);
```

## Usage

### Performance Mode (Default)
1. **Power On**: Connect the device via USB - displays splash screen then enters Performance mode
2. **Program Navigation**: 
   - Rotate encoder to browse programs (display shows program number and name)
   - Press encoder button to send current program via MIDI
   - Use right/left buttons for quick program switching
3. **MIDI Output**: Selected program sends Program Change message (0xC0 + channel)

### Configuration Mode
1. **Enter Configuration**: Press and hold encoder button for 3 seconds
2. **Menu Navigation**:
   - Rotate encoder to highlight menu items (unified MenuController pattern)
   - Press encoder button to select item
   - Available menus: Setlist Management, Program Editing, System Settings
3. **Setlist Management**:
   - Create and edit performance setlists using SetlistMenuState
   - Add/remove programs from setlists
   - Reorder setlist items with dual-mode interface (navigation/edit)
4. **Program Editing**:
   - Edit program names (0-15 characters) via ProgramsBank
   - Assign MIDI program numbers (0-127)
   - Save changes to ProgramsBank

### Navigation Summary
- **Encoder rotation**: Navigate menus/programs
- **Encoder button**: Select/confirm (short press) or enter configuration (long press)
- **Right/Left buttons**: Quick program switching in Performance mode
- **Display**: Shows current mode, selection, and navigation cues

### MIDI Communication

The device sends MIDI Program Change messages when a new program is selected:
- **Message Type**: Program Change (0xC0 + channel)
- **Data**: Program number (0-127)
- **Interface**: USB MIDI Class Compliant

## Development

### Project Structure

```
├── src/
│   ├── main.cpp                 # Application entry point and component wiring
│   ├── app/                     # Application logic layer
│   │   ├── MidiPatchBoxApplication.*   # Main application controller
│   │   ├── StateMachine.*              # State pattern implementation
│   │   ├── DiContainer.*               # Dependency injection container
│   │   ├── ProgramsBank.*              # MIDI program storage
│   │   ├── ProgramSelector.*           # Program selection logic
│   │   ├── MenuController.*            # Unified menu navigation
│   │   ├── SetlistManager.*            # Setlist data management
│   │   ├── Context.*                   # Shared data structure
│   │   ├── SetlistMenuViewDecorator.*  # View decorator for menus
│   │   ├── ConfigMenuViewAdapter.*     # Interface adapter for legacy views
│   │   ├── *State.*                    # State implementations (Main, Config, Setlist, Edit, Splash)
│   │   ├── *Interface.h                # Abstract interfaces
│   │   └── experimental/               # Experimental features
│   └── hardware/                # Hardware abstraction layer
│       ├── UserInput.*          # Button and encoder input
│       ├── MidiController.*     # USB MIDI communication
│       ├── ArduinoIoDriver.*    # GPIO operations
│       ├── Display*View.*       # OLED display renderers for each state
│       └── *Interface.h         # Hardware interface implementations
├── test/                        # Unit tests with mock objects
│   ├── mocks/                   # Mock implementations for testing
│   ├── test_*/                  # Test suites for each component
│   └── README                   # Test documentation
├── lib/                         # External libraries
├── include/                     # Global headers
├── docs/                        # Documentation assets
├── blueprint/                   # Development workflow and planning
└── plans/                       # Development plans and architecture documents
```

### Testing

The project follows Test-Driven Development (TDD) methodology with comprehensive unit tests:

- **Native Testing Environment**: Fast feedback loop with `pio test -e native` on development machine
- **Mock Objects**: Hardware interfaces mocked in `test/mocks/` for isolated testing
- **State Pattern Testing**: Each state has dedicated test suite for behavior verification
- **Interface Compliance**: Tests verify interface contracts and component interactions
- **Menu Controller Testing**: Unified menu pattern tested across different use cases

#### Test Organization

```
test/
├── mocks/                           # Centralized mock objects
│   ├── MockIoDriver.h              # GPIO operations mock
│   ├── MockButton.h                # Button interface mock
│   ├── MockEncoder.h               # Encoder interface mock
│   ├── MockProgramsBank.h          # ProgramsBank interface mock
│   ├── MockProgramSelector.h       # ProgramSelector interface mock
│   ├── MockEditSetlistView.h       # EditSetlistView interface mock
│   ├── MockConfigMenuView.h        # ConfigMenuView interface mock
│   ├── MockMenuLayoutView.h        # MenuLayoutView interface mock
│   ├── MockState.h                 # State interface mock
│   ├── MockStateFactory.h          # StateFactory interface mock
│   ├── MockStateMachine.h          # StateMachine interface mock
│   └── MockInput.h                 # UserInput interface mock
├── test_button/                     # Button logic tests
├── test_encoder/                    # Encoder logic tests
├── test_program_selector/           # Program selection tests
├── test_programs_bank/              # Program name storage tests
├── test_user_input/                 # User input coordination tests
├── test_state_machine/              # State machine tests
├── test_splash_screen_state/        # Splash screen state tests
├── test_main_application_state/     # Main application state tests
├── test_config_menu_state/          # Config menu state tests
├── test_setlist_menu_state/         # Setlist menu state tests
├── test_edit_setlist_state/         # Edit setlist state tests
├── test_menu_controller/            # MenuController pattern tests
├── test_setlist_manager/            # SetlistManager tests
├── test_di_container/               # Dependency injection tests
├── test_context/                    # Context structure tests
├── test_setlist_menu_view_decorator/# View decorator tests
├── test_config_menu_view_adapter/   # Interface adapter tests
├── test_state_factory/              # State factory tests
├── test_main_integration/           # Integration tests
└── test_interface_analysis/         # Interface design analysis
```

```bash
# Run all tests (fast TDD feedback)
pio test -e native

# Run specific test suite
pio test -e native -f test_program_selector
pio test -e native -f test_setlist_menu_state
pio test -e native -f test_main_application_state
pio test -e native -f test_menu_controller
pio test -e native -f test_setlist_manager

# Build for hardware deployment
pio run -e pico

# Upload to Raspberry Pi Pico
pio run -e pico -t upload
```

### Adding New Features

1. **New Hardware**: Implement the appropriate interface (e.g., `UserInputInterface`)
2. **New Functionality**: Extend existing classes or create new interface implementations
3. **Menu Navigation**: Use MenuController pattern for consistent navigation interfaces
4. **Testing**: Add corresponding unit tests in the `test/` directory with appropriate mocks

## Development Workflow

This project uses the AI Blueprint workflow for structured development:

### Key Commands
- **`/overview`**: Generate project overview from planning documents
- **`/feature`**: Create specification for next build plan item
- **`/implement`**: Build the current feature with TDD approach
- **`/check`**: Verify behavior against the specification
- **`/audit`**: Review code quality and architecture
- **`/complete`**: Finalize and archive completed work

### Planning Documents
- **[`blueprint/project-plan.md`](blueprint/project-plan.md)**: High-level project goals and scope
- **[`blueprint/build-plan.md`](blueprint/build-plan.md)**: Sequential feature implementation plan
- **[`blueprint/context/project-overview.md`](blueprint/context/project-overview.md)**: Current project state and architecture

## Useful Links

- **[x-design](https://www.x-design.com/ai-editor)**: AI-powered graphic design tool. Used to downscale images.
- **[Wix](https://manage.wix.com)**: AI logo creator.
- **[Image2Cpp](https://javl.github.io/image2cpp/)**: Convert images to C++ bytes array.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Implement changes with appropriate tests
4. Submit a pull request

## License

This project is open source. Please refer to the license file for details.

## Technical Specifications

- **Microcontroller**: RP2040 (Dual-core ARM Cortex-M0+)
- **Clock Speed**: 133 MHz
- **Memory**: 264KB SRAM, 2MB Flash
- **USB**: Full-speed USB 1.1 with MIDI class support
- **Power**: USB powered (5V)
- **MIDI Standard**: Compliant with MIDI 1.0 specification

## Troubleshooting

### Common Issues

1. **Device Not Recognized**: Ensure proper USB cable and TinyUSB configuration
2. **No MIDI Output**: Check MIDI channel configuration and host device settings
3. **Input Not Responding**: Verify pin assignments and debouncing logic for buttons and encoder
4. **Display Not Working**:
   - Check I2C wiring (SDA/SCL connections)
   - Verify display I2C address (default: 0x3C)
   - Ensure 3.3V power supply to display
   - Check for loose connections
   - Try different I2C pins if needed

### Debug Mode

Enable debug output by modifying the build flags in [`platformio.ini`](platformio.ini).

---

**Manufacturer**: iv660  
**Product**: MIDI Patch Box  
**Version**: 1.0.0