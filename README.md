# MIDI Patch Box

A programmable MIDI controller based on the RP2040 microcontroller, designed for selecting MIDI programs using buttons and rotary encoder. The controller sends MIDI program change messages to musical instruments and other MIDI devices, with the selected program displayed on the controller's screen.

## Features

- **RP2040-based**: Built on the powerful Raspberry Pi Pico microcontroller
- **USB MIDI Interface**: Native USB MIDI communication using TinyUSB
- **Program Selection**: Navigate through predefined MIDI programs using buttons and rotary encoder
- **Programmable Song List**: Configure custom lists of compositions with program numbers and names
- **Real-time Display**: Shows currently selected program on the controller screen
- **Modular Architecture**: Clean separation of concerns with interface-based design
- **Unit Testing**: Comprehensive test suite for reliable operation

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

The project follows a modular, interface-based architecture:

### Core Components

- **[`MidiPatchBoxApplication`](src/app/MidiPatchBoxApplication.h)**: Main application controller coordinating all components
- **[`ProgramSelector`](src/app/ProgramSelector.h)**: Manages program list and selection logic
- **[`UserInput`](src/hardware/UserInput.h)**: Handles button and rotary encoder input for user interaction
- **[`MidiController`](src/hardware/MidiController.h)**: Manages USB MIDI communication

### Interface Layer

- **[`ProgramSelectorInterface`](src/app/ProgramSelectorInterface.h)**: Abstract interface for program selection
- **[`UserInputInterface`](src/app/UserInputInterface.h)**: Abstract interface for user input handling
- **[`MidiControllerInterface`](src/app/MidiControllerInterface.h)**: Abstract interface for MIDI communication
- **[`ProgramSelectionViewInterface`](src/app/ProgramSelectionViewInterface.h)**: Abstract interface for program display

This design enables easy testing, component swapping, and future extensions.

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
```

## Configuration

### Program Setup

Programs are configured in [`main.cpp`](src/main.cpp):

```cpp
// Example: Set up three MIDI programs
programSelector.setPrograms({0, 41, 112});
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

- **Startup Screen**: Shows "MIDI Patch Box" on initialization
- **Program Display**: Large program number with "PROGRAM" label
- **Auto-centering**: Text automatically centers for optimal readability
- **Real-time Updates**: Display updates immediately when program changes

## Usage

1. **Power On**: Connect the device via USB
2. **Program Navigation**: Use buttons or rotary encoder to cycle through available programs
3. **Program Selection**: The current program is automatically sent via MIDI
4. **Display**: View the selected program number on the screen

### MIDI Communication

The device sends MIDI Program Change messages when a new program is selected:
- **Message Type**: Program Change (0xC0 + channel)
- **Data**: Program number (0-127)
- **Interface**: USB MIDI Class Compliant

## Development

### Project Structure

```
├── src/
│   ├── main.cpp                 # Application entry point
│   ├── app/                     # Application logic layer
│   │   ├── MidiPatchBoxApplication.*
│   │   ├── ProgramSelector.*
│   │   └── *Interface.h         # Abstract interfaces
│   └── hardware/                # Hardware abstraction layer
│       ├── UserInput.*
│       ├── MidiController.*
│       └── DisplayProgramSelectionView.*
├── test/                        # Unit tests
├── lib/                         # External libraries
└── include/                     # Global headers
```

### Testing

The project includes comprehensive unit tests:

```bash
# Run all tests
pio test -e native

# Run specific test
pio test -e native -f test_program_selector
```

### Adding New Features

1. **New Hardware**: Implement the appropriate interface (e.g., `UserInputInterface`)
2. **New Functionality**: Extend existing classes or create new interface implementations
3. **Testing**: Add corresponding unit tests in the `test/` directory

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