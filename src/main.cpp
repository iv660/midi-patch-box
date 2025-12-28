#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include "app/MidiPatchBoxApplication.h"
#include "app/ProgramSelector.h"
#include "app/UserInput.h"
#include "app/StateMachine.h"
#include "app/SplashScreenState.h"
#include "app/MainApplicationStateFactory.h"
#include "app/ProgramsBank.h"
#include "hardware/MidiController.h"
#include "hardware/ArduinoIoDriver.h"
#include "hardware/DisplayProgramSelectionView.h"
#include "hardware/DisplaySplashScreenView.h"


const uint8_t MIDI_CHANNEL = 0;

MidiPatchBoxApplication app;
StateMachine stateMachine;

ProgramSelector programSelector;
UserInput userInput;
MidiController midiController(MIDI_CHANNEL);
ArduinoIoDriver ioDriver;
DisplayProgramSelectionView displayView;
DisplaySplashScreenView splashView;
ProgramsBank programsBank;

MainApplicationStateFactory stateFactory;

void setup()
{
    // Set manufacturer and product descriptors BEFORE USB initialization
    USBDevice.setManufacturerDescriptor("iv660");
    USBDevice.setProductDescriptor("MIDI Patch Box");
    USBDevice.setSerialDescriptor("0001"); // any serial number
    
    // Initialize state factory with dependencies
    stateFactory.setUserInput(&userInput)
               ->setProgramSelector(&programSelector)
               ->setMidiController(&midiController)
               ->setProgramSelectionView(&displayView)
               ->setProgramsBank(&programsBank);
    
    // Initialize programs bank with program names
    programsBank.addProgram(0, "Clean")
               ->addProgram(41, "Viola")
               ->addProgram(112, "Reverse");
    
    programSelector.setPrograms({0, 41, 112});
    
    userInput.setIoDriver(&ioDriver);

    app.setProgramSelector(&programSelector)
        ->setUserInput(&userInput)
        ->setMidiController(&midiController)
        ->setProgramSelectionView(&displayView)
        ->setStateMachine(&stateMachine)
        ->begin();
    
    // Initialize State Machine with SplashScreenState that will transition to MainApplicationState after 1 second
    stateMachine.changeState((new SplashScreenState())
        ->setSplashScreenView(&splashView)
        ->setIoDriver(&ioDriver)
        ->setStateFactory(&stateFactory));
}

void loop() {
    app.tick();
}
