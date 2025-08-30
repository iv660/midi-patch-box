#include <unity.h>
#include "TestInclude.h"

// Unity требует эти функции даже если они пустые
void setUp(void) {}
void tearDown(void) {}

static void test_math_addition(void) {
    TEST_ASSERT_EQUAL(5, 2 + 3);
}

static void test_math_wrong_addition(void) {
    TEST_ASSERT_NOT_EQUAL(6, 2 + 3);
}

static void test_import_from_project(void) {
    TestInclude test;
    TEST_ASSERT_TRUE(test.alwaysTrue());
}

int main(int, char**) {
    UNITY_BEGIN();

    RUN_TEST(test_math_addition);
    RUN_TEST(test_math_wrong_addition);
    RUN_TEST(test_import_from_project);
    
    return UNITY_END();
}
