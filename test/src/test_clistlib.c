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
    char a;
    char *str;
    int b;
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

MU_TEST(test_clist_add_first)
{
    test_struct_t *elem_p = NULL;
    test_struct_t *elem_get_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    /* When */
    elem_p = clist_add_first(tested_clist);
    elem_p->str = "TestString";
    elem_get_p = clist_get_first(tested_clist);
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
    elem_p = clist_add_first(tested_clist);
    elem_p->str = "Elem1";
    elem_p = clist_add_first(tested_clist);
    elem_p->str = "Elem2";
    /* When */
    elem_get_p = clist_get_first(tested_clist);
    /* Check */
    mu_check(elem_get_p != NULL);
    mu_assert_string_eq("Elem2", elem_get_p->str);

    /* And when */
    elem_get_p = clist_get_next(tested_clist, elem_get_p);
    /* Check */
    mu_check(elem_get_p != NULL);
    mu_assert_string_eq("Elem1", elem_get_p->str);

}

MU_TEST(test_clist_add_after)
{
    test_struct_t  *elem_1 = NULL,
                    *elem_2 = NULL,
                    *elem_added = NULL;
    test_struct_t *elem_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    elem_1 = clist_add_first(tested_clist);
    elem_1->str = "E1";
    elem_2 = clist_add_first(tested_clist);
    elem_2->str = "E2";

    /* When */
    elem_added = clist_add_after(tested_clist, elem_2);
    elem_added->str = "Between 2 and 1";

    /* Check */
    elem_p = clist_get_next(tested_clist, elem_2);
    mu_check(elem_p == elem_added);
    mu_assert_string_eq("Between 2 and 1", elem_p->str);
    mu_check(clist_get_next(tested_clist, elem_p) == elem_1);

    /* And when */
    elem_added = clist_add_after(tested_clist, elem_1);
    elem_added->str = "After 1";

    /* Check */
    elem_p = clist_get_next(tested_clist, elem_1);
    mu_check(elem_p == elem_added);
    mu_assert_string_eq("After 1", elem_p->str);
    mu_check(clist_get_next(tested_clist, elem_p) == NULL);
}

MU_TEST(test_clist_add_last)
{
    test_struct_t *elem_p = NULL;
    test_struct_t *elem_get_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    clist_add_first(tested_clist);
    /* When */
    elem_p = clist_add_last(tested_clist);
    elem_p->str = "TestString";
    elem_get_p = clist_get_last(tested_clist);
    /* Check */
    mu_check(elem_p != NULL);
    mu_check(elem_get_p == elem_p);
    mu_assert_string_eq("TestString", elem_get_p->str);
}

MU_TEST(test_clist_remove_first)
{
    test_struct_t *elem_p = NULL;
    test_struct_t *elem_get_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    elem_p = clist_add_first(tested_clist);
    elem_p->str = "Elem1";
    elem_p = clist_add_first(tested_clist);
    elem_p->str = "Elem2";
    /* When */
    clist_remove(tested_clist, elem_p);
    /* Check */
    elem_get_p = clist_get_first(tested_clist);
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
    elem_1 = clist_add_first(tested_clist);
    elem_2 = clist_add_first(tested_clist);
    elem_2->str = "Elem2";
    /* When */
    clist_remove(tested_clist, elem_1);
    /* Check */
    elem_get_p = clist_get_first(tested_clist);
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
    elem_1 = clist_add_first(tested_clist);
    elem_2 = clist_add_first(tested_clist);
    elem_3 = clist_add_first(tested_clist);
    /* When */
    clist_remove(tested_clist, elem_2);
    /* Check */
    elem_get_p = clist_get_first(tested_clist);
    mu_check(elem_get_p == elem_3);
    mu_check(clist_get_next(tested_clist, elem_get_p) == elem_1);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	MU_RUN_TEST(test_clist_create);
	MU_RUN_TEST(test_clist_add_first);
    MU_RUN_TEST(test_clist_add_multiple);
    MU_RUN_TEST(test_clist_add_after);
    MU_RUN_TEST(test_clist_add_last);
    MU_RUN_TEST(test_clist_remove_first);
    MU_RUN_TEST(test_clist_remove_tail);
    MU_RUN_TEST(test_clist_remove_middle);
}

void test_clistlib_suite_runner(void)
{
    printf("\n\n~~ Acceptance Tests:\n");
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
}