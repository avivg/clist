#include <stdio.h>
#include <lightunit.h>

#include <internal/clist_util.h>

LU_TEST_SUITE(test_suite_clist_utils);

LU_TEST(test_suite_clist_utils, test_utils_smoke_alloc_free)
{
    void *buf = clu_alloc(71);
    LU_ASSERT(buf != NULL);
    clu_free(buf);
}

int test_clist_util_suite_runner(void)
{
    printf("\n\n~~ CList Utilities Tests:\n");
    LU_SUITE_RUN(test_suite_clist_utils);
    LU_SUITE_REPORT(test_suite_clist_utils);
    return LU_SUITE_STATUS(test_suite_clist_utils);
}