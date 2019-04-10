#include <stdio.h>

#include <minunit.h>
#include <clist.h>

clist_t tested_clist;

void test_setup()
{
    tested_clist = NULL;
}
void test_teardown()
{
    if (tested_clist)
    {
        clist_free(tested_clist);
    }
}

typedef struct
{
    int a;
    int b;
    char *str;
} test_struct_t;

MU_TEST(test_clist_create)
{
	/* Given */
    size_t test_size = sizeof(test_struct_t);
    /* When */
    tested_clist = clist_create(test_size);
    /* Check */
    mu_check(tested_clist != NULL);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_clist_create);
}

void test_acceptance_suite_runner(void)
{
    printf("\n\n~~ Acceptance Tests:\n");
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
}