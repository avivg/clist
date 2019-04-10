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
        tested_clist = NULL;
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

MU_TEST(test_clist_add_top)
{
    test_struct_t *elem_p = NULL;
    test_struct_t *elem_get_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    /* When */
    elem_p = clist_add_top(tested_clist);
    elem_p->str = "TestString";
    elem_get_p = clist_get_top(tested_clist);
    /* Check */
    mu_check(elem_p != NULL);
    mu_check(elem_get_p == elem_p);
    mu_assert_string_eq("TestString", elem_get_p->str);
}

MU_TEST(test_clist_add_multiple)
{
    test_struct_t *elem_p = NULL;
    test_struct_t *elem_get_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    elem_p = clist_add_top(tested_clist);
    elem_p->str = "Elem1";
    elem_p = clist_add_top(tested_clist);
    elem_p->str = "Elem2";
    /* When */
    elem_get_p = clist_get_top(tested_clist);
    /* Check */
    mu_check(elem_get_p != NULL);
    mu_assert_string_eq("Elem2", elem_get_p->str);

    /* And when */
    elem_get_p = clist_get_next(tested_clist, elem_get_p);
    /* Check */
    mu_check(elem_get_p != NULL);
    mu_assert_string_eq("Elem1", elem_get_p->str);

}

MU_TEST(test_clist_remove_top)
{
    test_struct_t *elem_p = NULL;
    test_struct_t *elem_get_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    elem_p = clist_add_top(tested_clist);
    elem_p->str = "Elem1";
    elem_p = clist_add_top(tested_clist);
    elem_p->str = "Elem2";
    /* When */
    clist_remove(tested_clist, elem_p);
    /* Check */
    elem_get_p = clist_get_top(tested_clist);
    mu_check(elem_get_p != NULL);
    mu_assert_string_eq("Elem1", elem_get_p->str);
}

MU_TEST(test_clist_remove_tail)
{
    test_struct_t *elem_1 = NULL;
    test_struct_t *elem_2 = NULL;
    test_struct_t *elem_get_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    elem_1 = clist_add_top(tested_clist);
    elem_2 = clist_add_top(tested_clist);
    elem_2->str = "Elem2";
    /* When */
    clist_remove(tested_clist, elem_1);
    /* Check */
    elem_get_p = clist_get_top(tested_clist);
    mu_check(elem_get_p != NULL);
    mu_check(clist_get_next(tested_clist, elem_get_p) == NULL);
    mu_assert_string_eq("Elem2", elem_get_p->str);
}

MU_TEST(test_clist_remove_middle)
{
    test_struct_t *elem_1 = NULL;
    test_struct_t *elem_2 = NULL;
    test_struct_t *elem_3 = NULL;
    test_struct_t *elem_get_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    elem_1 = clist_add_top(tested_clist);
    elem_2 = clist_add_top(tested_clist);
    elem_3 = clist_add_top(tested_clist);
    /* When */
    clist_remove(tested_clist, elem_2);
    /* Check */
    elem_get_p = clist_get_top(tested_clist);
    mu_check(elem_get_p == elem_3);
    mu_check(clist_get_next(tested_clist, elem_get_p) == elem_1);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_clist_create);
	MU_RUN_TEST(test_clist_add_top);
    MU_RUN_TEST(test_clist_add_multiple);
    MU_RUN_TEST(test_clist_remove_top);
    MU_RUN_TEST(test_clist_remove_tail);
    MU_RUN_TEST(test_clist_remove_middle);
}

void test_acceptance_suite_runner(void)
{
    printf("\n\n~~ Acceptance Tests:\n");
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
}