#include <stdio.h>

#include <minunit.h>
#include <internal/clist_util.h>

MU_TEST(test_utils_smoke_alloc_free)
{
    void *buf = clu_alloc(71);
    mu_check(buf != NULL);
    clu_free(buf);
}

MU_TEST_SUITE(test_suite)
{
    MU_RUN_TEST(test_utils_smoke_alloc_free);
}

int test_clist_util_suite_runner(void)
{
    printf("\n\n~~ CList Utilities Tests:\n");
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return minunit_fail;
}