#include <stdio.h>

#include <minunit.h>
#include <internal/clist_util.h>

MU_TEST(test_utils)
{

}

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_utils);
}

void test_clist_util_suite_runner(void)
{
    printf("\n\n~~ CList Utilities Tests:\n");
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
}