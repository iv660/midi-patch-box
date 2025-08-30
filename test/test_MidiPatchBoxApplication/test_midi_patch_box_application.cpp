#include "unity.h"
#include "app/MidiPatchBoxApplication.h"

void setUp(void) {
    // Called before each test
}

void tearDown(void) {
    // Called after each test
}

// Test that tick() method can be called without error
void testShouldSupportTickMethod(void) {
    MidiPatchBoxApplication app;

    app.tick();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testShouldSupportTickMethod);
    return UNITY_END();
}
