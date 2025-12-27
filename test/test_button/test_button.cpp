#include <unity.h>
#include "app/IoDriverInterface.h"
#include "app/Button.h"
#include "mocks/MockIoDriver.h"

const int HIGH = 1;
const int LOW = 0;

void setUp(void) {
}

void tearDown(void) {
}

void testShouldInstantiateButton() {
    Button button(2);  // pin 2
}

void testShouldAcceptIoDriver() {
    MockIoDriver ioDriver;
    Button button(2);  // pin 2
    button.setIoDriver(&ioDriver);
}

void testShouldHandleKeyPress() {
    MockIoDriver ioDriver;
    Button button(2);  // pin 2
    button.setIoDriver(&ioDriver);

    ioDriver.setPinState(2, LOW);
    button.update();
    ioDriver.delay(500);
    ioDriver.setPinState(2, HIGH);
    button.update();
    
    TEST_ASSERT_TRUE(button.isPressed());
    
    button.update();
    TEST_ASSERT_FALSE(button.isPressed());
}

void testShouldNotDetectKeyPressUnderDebounceTrashold() {
    MockIoDriver ioDriver;
    Button button(2);  // pin 2
    button.setIoDriver(&ioDriver);
    
    // Simulate button press shorter than 300ms debounce threshold
    ioDriver.resetTime();
    
    // Press button
    ioDriver.setPinState(2, LOW);
    button.update();
    
    // Hold for only 200ms (under 300ms threshold)
    ioDriver.delay(200);
    
    // Release button
    ioDriver.setPinState(2, HIGH);
    button.update();
    
    // Should not detect press due to debounce
    TEST_ASSERT_FALSE(button.isPressed());
    
    // Verify it stays false on subsequent updates
    button.update();
    TEST_ASSERT_FALSE(button.isPressed());
}

void testShouldCallPinModeOnSetIoDriver() {
    MockIoDriver ioDriver;
    Button button(2);  // pin 2
    
    // Act: устанавливаем IoDriver
    button.setIoDriver(&ioDriver);
    
    // Assert: проверяем что pinMode был вызван с правильными параметрами
    TEST_ASSERT_TRUE(ioDriver.wasPinModeCalledWith(2, IoDriverInterface::INPUT_PULLUP));
}

int main( void ) {
    UNITY_BEGIN();

    RUN_TEST(testShouldInstantiateButton);
    RUN_TEST(testShouldAcceptIoDriver);
    RUN_TEST(testShouldHandleKeyPress);
    RUN_TEST(testShouldNotDetectKeyPressUnderDebounceTrashold);
    RUN_TEST(testShouldCallPinModeOnSetIoDriver);

    return UNITY_END();
}
