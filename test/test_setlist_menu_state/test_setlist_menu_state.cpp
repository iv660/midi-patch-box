#include <unity.h>
#include <cstring>
#include "app/SetlistMenuState.h"
#include "app/MenuControllerInterface.h"
#include "app/DiContainer.h"
#include "app/MenuLayoutViewInterface.h"

// Mock MenuControllerInterface
class MockMenuController : public MenuControllerInterface {
private:
    char lastTitle[16];
    bool setTitleCalled = false;

public:
    void setTitle(char* title) override {
        strncpy(lastTitle, title, 16);
        lastTitle[15] = '\0';
        setTitleCalled = true;
    }

    MenuControllerInterface* addMenuItem(char* caption, std::function<void()> action) override { return this; }
    MenuControllerInterface* selectNext() override { return this; }
    MenuControllerInterface* selectPrevious() override { return this; }
    void executeSelectedAction() override {}

    // Test helpers
    bool setTitleWasCalled() const { return setTitleCalled; }
    const char* getLastTitle() const { return lastTitle; }
};

void setUp(void) {
}

void tearDown(void) {
}

void testSetlistMenuStateSetsMenuTitleOnEnter() {
    // Arrange
    DiContainer container;
    MockMenuController mockMenuController;
    SetlistMenuState state(&container);
    
    container.setSetlistMenuController(&mockMenuController);
    
    char expectedTitle[] = "Setlist";
    
    // Act
    state.enter();
    
    // Assert
    TEST_ASSERT_TRUE_MESSAGE(mockMenuController.setTitleWasCalled(), 
                             "Expected setTitle to be called on enter");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expectedTitle, mockMenuController.getLastTitle(),
                                     "Expected to set correct menu title");
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(testSetlistMenuStateSetsMenuTitleOnEnter);
    return UNITY_END();
}
