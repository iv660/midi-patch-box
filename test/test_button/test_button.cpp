#include <unity.h>

const int HIGH = 1;
const int LOW = 0;

class IoDriverInterface {
public:
    virtual int digitalRead(int pin) = 0;
    virtual void delay(unsigned long ms) = 0;
};

class MockIoDriver : public IoDriverInterface {
public:
    int digitalRead(int pin) override {
        return pin == BUTTON_PIN ? pinState : LOW;
    }

    void delay(unsigned long ms) override {
        // Mock delay - do nothing in tests
    }

    void setPinState(int pin, int state) {
        if (pin == BUTTON_PIN) {
            pinState = state;
        }
    }

private:
    int pinState = HIGH; // Emulate pull-up resistor
    const int BUTTON_PIN = 2;
};

class Button {
public:
    Button() : ioDriver(nullptr), lastButtonState(HIGH), buttonPressed(false) {}

    Button* setIoDriver(IoDriverInterface* ioDriver) {
        this->ioDriver = ioDriver;
        return this;
    }

    void update() {
        if (!ioDriver) return;
        
        bool currentState = ioDriver->digitalRead(BUTTON_PIN);
        
        // Detect button press and release cycle
        if (lastButtonState == HIGH && currentState == LOW) {
            // Button was just pressed
            buttonPressed = false; // Not yet a complete press
        } else if (lastButtonState == LOW && currentState == HIGH) {
            // Button was just released - complete press detected
            buttonPressed = true;
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

int main( void ) {
    UNITY_BEGIN();

    RUN_TEST(testShouldInstantiateButton);
    RUN_TEST(testShouldAcceptIoDriver);
    RUN_TEST(testShouldHandleKeyPress);

    return UNITY_END();
}
