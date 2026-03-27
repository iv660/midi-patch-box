#include <unity.h>
#include "app/MenuController.h"
#include "../../test/mocks/MockMenuLayoutView.h"

void setUp(void) {
}

void tearDown(void) {
}

void testShouldSetTitle() {
    MockMenuLayoutView mockView;
    MenuController menuController;
    
    char expectedTitle[] = "Test Menu";
    
    menuController.setView(&mockView);
    menuController.setTitle(expectedTitle);
    
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expectedTitle, mockView.getTitle(), 
                                     "Expected to set menu title for view");
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(testShouldSetTitle);
    return UNITY_END();
}
