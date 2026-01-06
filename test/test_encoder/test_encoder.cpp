#include <unity.h>
#include "app/Encoder.h"
#include "mocks/MockIoDriver.h"

void setUp(void) {}
void tearDown(void) {}

// Test 1: Auto-initialization when setPinA() -> setPinB() -> setIoDriver()
void testShouldAutoInitializePinsWhenSetPinAFirst() {
    MockIoDriver ioDriver;
    Encoder encoder;
    
    encoder.setPinA(27)
           ->setPinB(28)
           ->setIoDriver(&ioDriver);
    
    // Should automatically call pinMode for both pins
    TEST_ASSERT_TRUE(ioDriver.wasPinModeCalledWith(27, 2)); // INPUT_PULLUP = 2
    TEST_ASSERT_TRUE(ioDriver.wasPinModeCalledWith(28, 2)); // INPUT_PULLUP = 2
}

// Test 2: Auto-initialization when setIoDriver() -> setPinA() -> setPinB()
void testShouldAutoInitializePinsWhenSetIoDriverFirst() {
    MockIoDriver ioDriver;
    Encoder encoder;
    
    encoder.setIoDriver(&ioDriver)
           ->setPinA(29)
           ->setPinB(30);
    
    // Should automatically call pinMode for both pins
    TEST_ASSERT_TRUE(ioDriver.wasPinModeCalledWith(29, 2)); // INPUT_PULLUP = 2
    TEST_ASSERT_TRUE(ioDriver.wasPinModeCalledWith(30, 2)); // INPUT_PULLUP = 2
}

// Test 3: Auto-initialization when setPinB() -> setIoDriver() -> setPinA()
void testShouldAutoInitializePinsWhenSetPinBFirst() {
    MockIoDriver ioDriver;
    Encoder encoder;
    
    encoder.setPinB(31)
           ->setIoDriver(&ioDriver)
           ->setPinA(32);
    
    // Should automatically call pinMode for both pins
    TEST_ASSERT_TRUE(ioDriver.wasPinModeCalledWith(31, 2)); // INPUT_PULLUP = 2
    TEST_ASSERT_TRUE(ioDriver.wasPinModeCalledWith(32, 2)); // INPUT_PULLUP = 2
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(testShouldAutoInitializePinsWhenSetPinAFirst);
    RUN_TEST(testShouldAutoInitializePinsWhenSetIoDriverFirst);
    RUN_TEST(testShouldAutoInitializePinsWhenSetPinBFirst);
    
    return UNITY_END();
}