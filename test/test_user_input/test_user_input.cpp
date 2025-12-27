#include <unity.h>
#include "app/UserInput.h"
#include "mocks/MockIoDriver.h"

void setUp(void) {}
void tearDown(void) {}

// Test 1: Basic initialization with default pins
void testShouldCreateUserInputWithDefaultPins() {
    UserInput userInput; // Default pins: user=24, right=25
    TEST_ASSERT_NOT_NULL(&userInput);
}

// Test 2: Custom pins initialization
void testShouldCreateUserInputWithCustomPins() {
    UserInput userInput(10, 11); // Custom pins
    TEST_ASSERT_NOT_NULL(&userInput);
}

// Test 3: Dependency injection with fluent interface
void testShouldAcceptIoDriver() {
    MockIoDriver ioDriver;
    UserInput userInput(24, 25);
    
    UserInput* result = userInput.setIoDriver(&ioDriver);
    
    // Should return this for fluent interface
    TEST_ASSERT_EQUAL_PTR(&userInput, result);
}

// Test 4: User button press detection via Button composition
void testShouldDetectUserButtonPress() {
    MockIoDriver ioDriver;
    UserInput userInput(2, 3); // Use pin 2 (MockIoDriver supports pin 2)
    userInput.setIoDriver(&ioDriver);
    
    // Simulate press on pin 2 (user button)
    ioDriver.setPinState(2, 0);  // Press (LOW)
    userInput.update();
    ioDriver.delay(500);         // Hold > 300ms (debounce via Button)
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
    UserInput userInput(2, 3); // Pin 3 not supported by MockIoDriver
    userInput.setIoDriver(&ioDriver);
    
    userInput.update();
    
    // Right button should always be false (pin 3 not supported)
    TEST_ASSERT_FALSE(userInput.rightButtonIsPressed());
    TEST_ASSERT_FALSE(userInput.userButtonIsPressed()); // User button also not pressed
}

// Test 6: Graceful degradation without IoDriver
void testShouldHandleMissingIoDriver() {
    UserInput userInput(24, 25);
    // Don't set IoDriver
    
    userInput.update(); // Should not crash
    
    TEST_ASSERT_FALSE(userInput.userButtonIsPressed());
    TEST_ASSERT_FALSE(userInput.rightButtonIsPressed());
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(testShouldCreateUserInputWithDefaultPins);
    RUN_TEST(testShouldCreateUserInputWithCustomPins);
    RUN_TEST(testShouldAcceptIoDriver);
    RUN_TEST(testShouldDetectUserButtonPress);
    RUN_TEST(testShouldHandleRightButtonWhenNotSupported);
    RUN_TEST(testShouldHandleMissingIoDriver);
    
    return UNITY_END();
}