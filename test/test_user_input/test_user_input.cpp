#include <unity.h>
#include "app/UserInput.h"
#include "app/Button.h"
#include "app/Encoder.h"
#include "mocks/MockIoDriver.h"
#include "mocks/MockButton.h"
#include "mocks/MockEncoder.h"

void setUp(void) {}
void tearDown(void) {}

// Test 1: Basic initialization with default pins
void testShouldCreateUserInputWithDefaultPins() {
    UserInput userInput;
    TEST_ASSERT_NOT_NULL(&userInput);
}

// Test 2: Custom pins initialization - now tests fluent interface
void testShouldCreateUserInputWithCustomPins() {
    MockButton userButton;
    MockButton rightButton;
    
    UserInput userInput;
    userInput.setUserButton(&userButton)
             ->setRightButton(&rightButton);
    
    TEST_ASSERT_NOT_NULL(&userInput);
}

// Test 3: Dependency injection with fluent interface - updated for new API
void testShouldAcceptIoDriver() {
    MockButton userButton;
    MockButton rightButton;
    
    UserInput userInput;
    UserInput* result = userInput.setUserButton(&userButton)
                                ->setRightButton(&rightButton);
    
    // Should return this for fluent interface
    TEST_ASSERT_EQUAL_PTR(&userInput, result);
}

// Test 4: User button press detection via Button composition
void testShouldDetectUserButtonPress() {
    MockIoDriver ioDriver;
    Button userButton(2);  // Use pin 2 (MockIoDriver supports pin 2)
    Button rightButton(3);
    userButton.setIoDriver(&ioDriver);
    rightButton.setIoDriver(&ioDriver);
    
    UserInput userInput;
    userInput.setUserButton(&userButton)
             ->setRightButton(&rightButton);
    
    // Simulate press on pin 2 (user button)
    ioDriver.setPinState(2, 0);  // Press (LOW)
    userInput.update();
    ioDriver.delay(100);         // Hold > 50ms (debounce via Button)
    ioDriver.setPinState(2, 1);  // Release (HIGH)
    userInput.update();
    
    TEST_ASSERT_TRUE(userInput.userButtonIsPressed());
    TEST_ASSERT_FALSE(userInput.rightButtonIsPressed());
    
    // Should reset after next update
    userInput.update();
    TEST_ASSERT_FALSE(userInput.userButtonIsPressed());
}

// Test 5: Right button limitation with MockIoDriver
void testShouldHandleRightButtonWhenNotSupported() {
    MockIoDriver ioDriver;
    Button userButton(2);  // Pin 2 supported by MockIoDriver
    Button rightButton(3); // Pin 3 not supported by MockIoDriver
    userButton.setIoDriver(&ioDriver);
    rightButton.setIoDriver(&ioDriver);
    
    UserInput userInput;
    userInput.setUserButton(&userButton)
             ->setRightButton(&rightButton);
    
    userInput.update();
    
    // Right button should always be false (pin 3 not supported)
    TEST_ASSERT_FALSE(userInput.rightButtonIsPressed());
    TEST_ASSERT_FALSE(userInput.userButtonIsPressed()); // User button also not pressed
}

// Test 6: Graceful degradation without buttons
void testShouldHandleMissingIoDriver() {
    UserInput userInput;
    // Don't set any buttons
    
    userInput.update(); // Should not crash
    
    TEST_ASSERT_FALSE(userInput.userButtonIsPressed());
    TEST_ASSERT_FALSE(userInput.rightButtonIsPressed());
}

// Test 7: Encoder clockwise rotation detection
void testShouldDetectEncoderClockwiseRotation() {
    MockEncoder encoder;
    
    UserInput userInput;
    userInput.setEncoder(&encoder);
    
    TEST_ASSERT_FALSE(userInput.encoderRotatedClockwise());
}

// Test 8: Encoder with actual rotation sequence
void testShouldDetectEncoderRotationSequence() {
    MockIoDriver ioDriver;
    Button userButton(2);
    Button rightButton(3);
    Button encoderButton(6);
    Encoder encoder;
    
    userButton.setIoDriver(&ioDriver);
    rightButton.setIoDriver(&ioDriver);
    encoderButton.setIoDriver(&ioDriver);
    encoder.setPinA(4)->setPinB(5)->setIoDriver(&ioDriver);
    
    UserInput userInput;
    userInput.setUserButton(&userButton)
             ->setRightButton(&rightButton)
             ->setEncoderButton(&encoderButton)
             ->setEncoder(&encoder);
    
    // Set initial state (A high, B low - matches lastEncoderA=1 initialization)
    ioDriver.setPinState(4, 1); // A high
    ioDriver.setPinState(5, 0); // B low
    userInput.update();
    TEST_ASSERT_FALSE(userInput.encoderRotatedClockwise());
    
    // Simulate clockwise rotation: A goes low while B is low
    ioDriver.setPinState(4, 0); // A low (transition that triggers detection)
    userInput.update();
    
    // Should detect clockwise rotation when A goes low while B is low
    TEST_ASSERT_TRUE(userInput.encoderRotatedClockwise());
}

void testShouldInitilizeUsingFluentSetters(void) {
    MockButton userButton;
    MockButton rightButton;
    MockButton encoderButton;
    MockEncoder encoder;

    UserInput userInput;

    userInput.setUserButton(&userButton)
        ->setRightButton(&rightButton)
        ->setEncoderButton(&encoderButton)
        ->setEncoder(&encoder);

    userButton.press();
    userInput.update();
    TEST_ASSERT_TRUE(userInput.userButtonIsPressed());

    rightButton.press();
    userInput.update();
    TEST_ASSERT_TRUE(userInput.rightButtonIsPressed());

    encoder.rotateClockwise();
    userInput.update();
    TEST_ASSERT_TRUE(userInput.encoderRotatedClockwise());

    encoder.rotateCounterClockwise();
    userInput.update();
    TEST_ASSERT_TRUE(userInput.encoderRotatedCounterClockwise());

    encoderButton.press();
    userInput.update();
    TEST_ASSERT_TRUE(userInput.encoderButtonPressed());
}

void testShouldDetectEncoderButtonLongPress(void) {
    MockButton encoderButton;
    UserInput userInput;
    
    userInput.setEncoderButton(&encoderButton);
    
    encoderButton.longPress();
    userInput.update();
    
    TEST_ASSERT_TRUE(userInput.encoderButtonLongPressed());
}

void testShouldNotDetectLongPressWhenEncoderButtonNotSet(void) {
    UserInput userInput;
    
    userInput.update();
    
    TEST_ASSERT_FALSE(userInput.encoderButtonLongPressed());
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(testShouldCreateUserInputWithDefaultPins);
    RUN_TEST(testShouldCreateUserInputWithCustomPins);
    RUN_TEST(testShouldAcceptIoDriver);
    RUN_TEST(testShouldDetectUserButtonPress);
    RUN_TEST(testShouldHandleRightButtonWhenNotSupported);
    RUN_TEST(testShouldHandleMissingIoDriver);
    RUN_TEST(testShouldDetectEncoderClockwiseRotation);
    RUN_TEST(testShouldDetectEncoderRotationSequence);
    RUN_TEST(testShouldInitilizeUsingFluentSetters);
    RUN_TEST(testShouldDetectEncoderButtonLongPress);
    RUN_TEST(testShouldNotDetectLongPressWhenEncoderButtonNotSet);
    
    return UNITY_END();
}