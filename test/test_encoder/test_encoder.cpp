#include <unity.h>
#include "app/Encoder.h"
#include "mocks/MockIoDriver.h"

void setUp(void) {}
void tearDown(void) {}

// Test 1: Basic encoder creation with fluent interface
void testShouldCreateEncoder() {
    MockIoDriver ioDriver;
    Encoder encoder;
    
    Encoder* result = encoder.setPinA(4)
        ->setPinB(5)
        ->setIoDriver(&ioDriver);
    
    // Should return this for fluent interface
    TEST_ASSERT_EQUAL_PTR(&encoder, result);
}

// Test 2: Should detect clockwise rotation
void testShouldDetectClockwiseRotation() {
    MockIoDriver ioDriver;
    Encoder encoder;
    encoder.setPinA(4)->setPinB(5)->setIoDriver(&ioDriver);
    
    // Set initial state: A=1, B=0
    ioDriver.setPinState(4, 1);
    ioDriver.setPinState(5, 0);
    encoder.update();
    
    // Simulate clockwise: A goes low while B also goes low
    ioDriver.setPinState(4, 0);
    encoder.update();
    
    TEST_ASSERT_TRUE(encoder.rotatedClockwise());
    TEST_ASSERT_FALSE(encoder.rotatedCounterClockwise());
}

// Test 3: Should detect counter-clockwise rotation
void testShouldDetectCounterClockwiseRotation() {
    MockIoDriver ioDriver;
    Encoder encoder;
    encoder.setPinA(4)->setPinB(5)->setIoDriver(&ioDriver);
    
    // Set initial state: A=1, B=0
    ioDriver.setPinState(4, 1);
    ioDriver.setPinState(5, 0);
    encoder.update();
    
    // Simulate counter-clockwise: A goes low while B stays low
    ioDriver.setPinState(4, 0);
    ioDriver.setPinState(5, 1);
    encoder.update();
    
    TEST_ASSERT_FALSE(encoder.rotatedClockwise());
    TEST_ASSERT_TRUE(encoder.rotatedCounterClockwise());
}

int main() {
    UNITY_BEGIN();
    
    RUN_TEST(testShouldCreateEncoder);
    RUN_TEST(testShouldDetectClockwiseRotation);
    RUN_TEST(testShouldDetectCounterClockwiseRotation);
    
    return UNITY_END();
}