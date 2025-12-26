#include <unity.h>

const int HIGH = 1;
const int LOW = 0;

class IoDriverInterface {
public:
    virtual int digitalRead(int pin) = 0;
    virtual void delay(unsigned long ms) = 0;
    virtual unsigned long millis() = 0;
};

class MockIoDriver : public IoDriverInterface {
public:
    int digitalRead(int pin) override {
        return pin == BUTTON_PIN ? pinState : LOW;
    }

    void delay(unsigned long ms) override {
        currentTime += ms;
    }

    unsigned long millis() override {
        return currentTime;
    }

    void setPinState(int pin, int state) {
        if (pin == BUTTON_PIN) {
            pinState = state;
        }
    }

    void resetTime() {
        currentTime = 0;
    }

private:
    int pinState = HIGH; // Emulate pull-up resistor
    const int BUTTON_PIN = 2;
    unsigned long currentTime = 0;
};

class Button {
public:
    Button() : ioDriver(nullptr), lastButtonState(HIGH), buttonPressed(false), pressStartTime(0), debounceThreshold(300) {}

    Button* setIoDriver(IoDriverInterface* ioDriver) {
        this->ioDriver = ioDriver;
        return this;
    }

    void update() {
        if (!ioDriver) return;
        
        bool currentState = ioDriver->digitalRead(BUTTON_PIN);
        unsigned long currentTime = ioDriver->millis();
        
        // Detect button press and release cycle with debounce
        if (lastButtonState == HIGH && currentState == LOW) {
            // Button was just pressed - record start time
            pressStartTime = currentTime;
            buttonPressed = false; // Not yet a complete press
        } else if (lastButtonState == LOW && currentState == HIGH) {
            // Button was just released - check if press duration meets threshold
            unsigned long pressDuration = currentTime - pressStartTime;
            if (pressDuration >= debounceThreshold) {
                buttonPressed = true; // Valid press detected
            } else {
                buttonPressed = false; // Too short, ignore
            }
        } else {
            // Reset after one read
            buttonPressed = false;
        }
        
        lastButtonState = currentState;
    }

    bool isPressed() {
        return buttonPressed;
    }

private:
    IoDriverInterface* ioDriver;
    bool lastButtonState;
    bool buttonPressed;
    unsigned long pressStartTime;
    const unsigned long debounceThreshold; // 300ms debounce threshold
    const int BUTTON_PIN = 2;
};

// ==============================================

void setUp(void) {
}

void tearDown(void) {
}

void testShouldInstantiateButton() {
    Button button;
}

void testShouldAcceptIoDriver() {
    MockIoDriver ioDriver;
    Button button;
    button.setIoDriver(&ioDriver);
}

void testShouldHandleKeyPress() {
    MockIoDriver ioDriver;
    Button button;
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
    Button button;
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

int main( void ) {
    UNITY_BEGIN();

    RUN_TEST(testShouldInstantiateButton);
    RUN_TEST(testShouldAcceptIoDriver);
    RUN_TEST(testShouldHandleKeyPress);
    RUN_TEST(testShouldNotDetectKeyPressUnderDebounceTrashold);

    return UNITY_END();
}
