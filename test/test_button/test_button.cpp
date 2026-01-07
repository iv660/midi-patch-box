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
    ioDriver.delay(21);  // Hold > 20ms (debounce threshold)
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
    
    // Simulate button press shorter than 50ms debounce threshold
    ioDriver.resetTime();
    
    // Press button
    ioDriver.setPinState(2, LOW);
    button.update();
    
    // Hold for only 19ms (under 20ms threshold)
    ioDriver.delay(19);
    
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

void testShouldNotDetectLongPressWhenNotEnabled() {
    MockIoDriver ioDriver;
    Button button(2);  // pin 2
    button.setIoDriver(&ioDriver);
    // NOTE: не вызываем enableLongPressDetection()

    ioDriver.resetTime();
    
    // Press button
    ioDriver.setPinState(2, LOW);
    button.update();
    
    // Hold for 2100ms (> 2000ms)
    ioDriver.delay(2100);
    
    // Release button
    ioDriver.setPinState(2, HIGH);
    button.update();
    
    // Should detect only short press, NOT long press
    TEST_ASSERT_TRUE(button.isPressed());
    TEST_ASSERT_FALSE(button.isLongPressed());
}

void testShouldDetectLongPressWhenEnabled() {
    MockIoDriver ioDriver;
    Button button(2);  // pin 2
    button.setIoDriver(&ioDriver);
    button.enableLongPressDetection(); // Enable long press detection

    ioDriver.resetTime();
    
    // Press button
    ioDriver.setPinState(2, LOW);
    button.update();
    
    // Hold for 2000ms (exactly at threshold)
    ioDriver.delay(2000);
    
    // Release button
    ioDriver.setPinState(2, HIGH);
    button.update();
    
    // Should detect long press, NOT short press
    TEST_ASSERT_TRUE(button.isLongPressed());
    TEST_ASSERT_FALSE(button.isPressed());
    
    // Next update should clear long press flag
    button.update();
    TEST_ASSERT_FALSE(button.isLongPressed());
}

void testShouldDetectShortPressJustUnderThreshold() {
    MockIoDriver ioDriver;
    Button button(2);  // pin 2
    button.setIoDriver(&ioDriver);
    button.enableLongPressDetection();

    ioDriver.resetTime();
    
    // Press button
    ioDriver.setPinState(2, LOW);
    button.update();
    
    // Hold for 1999ms (just under 2000ms threshold)
    ioDriver.delay(1999);
    
    // Release button
    ioDriver.setPinState(2, HIGH);
    button.update();
    
    // Should detect short press, NOT long press
    TEST_ASSERT_TRUE(button.isPressed());
    TEST_ASSERT_FALSE(button.isLongPressed());
}

void testMethodCallOrderShouldNotMatter() {
    MockIoDriver ioDriver;
    Button button(2);  // pin 2
    button.setIoDriver(&ioDriver);
    button.enableLongPressDetection();

    ioDriver.resetTime();
    
    // Press and hold for long press
    ioDriver.setPinState(2, LOW);
    button.update();
    ioDriver.delay(2000);
    ioDriver.setPinState(2, HIGH);
    button.update();
    
    // Test different call orders - should give same results
    bool longPressed1 = button.isLongPressed();
    bool shortPressed1 = button.isPressed();
    
    // Reset for second test
    button.update(); // Clear flags
    
    // Same scenario again
    ioDriver.setPinState(2, LOW);
    button.update();
    ioDriver.delay(2000);
    ioDriver.setPinState(2, HIGH);
    button.update();
    
    // Call in reverse order
    bool shortPressed2 = button.isPressed();
    bool longPressed2 = button.isLongPressed();
    
    // Results should be identical regardless of call order
    TEST_ASSERT_EQUAL(longPressed1, longPressed2);
    TEST_ASSERT_EQUAL(shortPressed1, shortPressed2);
    TEST_ASSERT_TRUE(longPressed1);
    TEST_ASSERT_FALSE(shortPressed1);
}

int main( void ) {
    UNITY_BEGIN();

    RUN_TEST(testShouldInstantiateButton);
    RUN_TEST(testShouldAcceptIoDriver);
    RUN_TEST(testShouldHandleKeyPress);
    RUN_TEST(testShouldNotDetectKeyPressUnderDebounceTrashold);
    RUN_TEST(testShouldCallPinModeOnSetIoDriver);
    RUN_TEST(testShouldNotDetectLongPressWhenNotEnabled);
    RUN_TEST(testShouldDetectLongPressWhenEnabled);
    RUN_TEST(testShouldDetectShortPressJustUnderThreshold);
    RUN_TEST(testMethodCallOrderShouldNotMatter);

    return UNITY_END();
}
