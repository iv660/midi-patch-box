#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include "app/MidiPatchBoxApplication.h"
#include "app/ProgramSelector.h"
#include "app/UserInput.h"
#include "app/Button.h"
#include "app/Encoder.h"
#include "app/StateMachine.h"
#include "app/SplashScreenState.h"
#include "app/StateFactory.h"
#include "app/ProgramsBank.h"
#include "app/DiContainer.h"
#include "hardware/MidiController.h"
#include "hardware/ArduinoIoDriver.h"
#include "hardware/DisplayProgramSelectionView.h"
#include "hardware/DisplaySplashScreenView.h"
#include "hardware/DisplayBitmapSplashScreenView.h"
#include "hardware/DisplayConfigMenuView.h"


const uint8_t MIDI_CHANNEL = 0;

MidiPatchBoxApplication app;
StateMachine stateMachine;

ProgramSelector programSelector;
MidiController midiController(MIDI_CHANNEL);
ArduinoIoDriver ioDriver;

// Create button and encoder instances
Button userButton(24);
Button rightButton(17);
Button encoderButton(29);
Encoder encoder;
UserInput userInput;

DisplayProgramSelectionView displayView;
DisplaySplashScreenView splashView;
DisplayBitmapSplashScreenView bitmapSplashView;
DisplayConfigMenuView configMenuView;
ProgramsBank programsBank;

StateFactory stateFactory;
DiContainer diContainer;

void setup()
{
    // Set manufacturer and product descriptors BEFORE USB initialization
    USBDevice.setManufacturerDescriptor("iv660");
    USBDevice.setProductDescriptor("MIDI Patch Box");
    USBDevice.setSerialDescriptor("0001"); // any serial number

    // Initialize StateFactory using DiContainer
    stateFactory = StateFactory(&diContainer);
    
    // Initialize programs bank with program names
    programsBank.addProgram(0, "Clean")
        ->addProgram(41, "Viola")
        ->addProgram(112, "Reverse");
    
    programSelector.setPrograms({0, 41, 112});
    
    // Configure hardware components
    userButton.setIoDriver(&ioDriver);
    rightButton.setIoDriver(&ioDriver);
    encoderButton.setIoDriver(&ioDriver)
        ->enableLongPressDetection();
    encoder.setPinA(27)
        ->setPinB(28)
        ->setIoDriver(&ioDriver);
    
    // Configure UserInput with dependency injection
    userInput.setUserButton(&userButton)
        ->setRightButton(&rightButton)
        ->setEncoderButton(&encoderButton)
        ->setEncoder(&encoder);

    // Setup DiContainer with all dependencies
    diContainer.setSplashScreenView(&bitmapSplashView)
        ->setIoDriver(&ioDriver)
        ->setStateFactory(&stateFactory)
        ->setUserInput(&userInput)
        ->setProgramSelector(&programSelector)
        ->setMidiController(&midiController)
        ->setProgramSelectionView(&displayView)
        ->setProgramsBank(&programsBank)
        ->setConfigMenuView(&configMenuView)
        ->setStateMachine(&stateMachine);

    // Initialize MidiPatchBoxApplication using DiContainer
    app = MidiPatchBoxApplication(&diContainer);
    app.begin();
    
    // Initialize State Machine with SplashScreenState using DiContainer
    SplashScreenState* splashScreenState = new SplashScreenState(&diContainer);
    stateMachine.changeState(splashScreenState);
}

void loop() {
    app.tick();
}
