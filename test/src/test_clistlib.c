#include <stdio.h>
#include <lightunit.h>

#include <clist.h>

LU_TEST_SUITE(test_suite_clistlib);

clist_t tested_clist;

LU_SUITE_SETUP(test_suite_clistlib)
{
    tested_clist = NULL;
}
LU_SUITE_TEARDOWN(test_suite_clistlib)
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

LU_TEST(test_suite_clistlib, test_clist_create)
{
	/* Given */
    size_t test_size = sizeof(test_struct_t);
    /* When */
    tested_clist = clist_create(test_size);
    /* Check */
    LU_ASSERT(tested_clist != NULL);
}

LU_TEST(test_suite_clistlib, test_clist_add_first)
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
    LU_ASSERT(elem_p != NULL);
    LU_ASSERT(elem_get_p == elem_p);
    LU_ASSERT_STR_EQ("TestString", elem_get_p->str);
}

LU_TEST(test_suite_clistlib, test_clist_add_multiple)
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
    LU_ASSERT(elem_get_p != NULL);
    LU_ASSERT_STR_EQ("Elem2", elem_get_p->str);

    /* And when */
    elem_get_p = clist_get_next(tested_clist, elem_get_p);
    /* Check */
    LU_ASSERT(elem_get_p != NULL);
    LU_ASSERT_STR_EQ("Elem1", elem_get_p->str);

}

LU_TEST(test_suite_clistlib, test_clist_add_after)
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
    LU_ASSERT(elem_p == elem_added);
    LU_ASSERT_STR_EQ("Between 2 and 1", elem_p->str);
    LU_ASSERT(clist_get_next(tested_clist, elem_p) == elem_1);

    /* And when */
    elem_added = clist_add_after(tested_clist, elem_1);
    elem_added->str = "After 1";

    /* Check */
    elem_p = clist_get_next(tested_clist, elem_1);
    LU_ASSERT(elem_p == elem_added);
    LU_ASSERT_STR_EQ("After 1", elem_p->str);
    LU_ASSERT(clist_get_next(tested_clist, elem_p) == NULL);
}

LU_TEST(test_suite_clistlib, test_clist_add_last)
{
    test_struct_t *elem_p = NULL;
    test_struct_t *elem_get_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    clist_add_first(tested_clist);
    /* When */
    elem_p = clist_add_last(tested_clist);
    elem_p->str = "TestString";
    elem_get_p = clist_get_next(tested_clist,
                        clist_get_first(tested_clist));
    /* Check */
    LU_ASSERT(elem_p != NULL);
    LU_ASSERT(elem_get_p == elem_p);
    LU_ASSERT_STR_EQ("TestString", elem_get_p->str);
}

LU_TEST(test_suite_clistlib, test_clist_get_next)
{
    test_struct_t *elem_p = NULL;
    test_struct_t *elem_get_p = NULL;
    int idx;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    elem_p = clist_add_last(tested_clist);
    elem_p->b = 1;
    elem_p = clist_add_last(tested_clist);
    elem_p->b = 2;
    elem_p = clist_add_last(tested_clist);
    elem_p->b = 3;
    elem_p = clist_add_last(tested_clist);
    elem_p->b = 4;
    elem_p = clist_add_last(tested_clist);
    elem_p->b = 5;
    /* When */
    elem_get_p = clist_get_first(tested_clist);
    /* Check */
    for (idx = 1; idx <= 5; idx++)
    {
        LU_ASSERT(elem_get_p != NULL);
        LU_ASSERT(elem_get_p->b == idx);
        elem_get_p = clist_get_next(tested_clist, elem_get_p);
    }
}

LU_TEST(test_suite_clistlib, test_clist_get_prev)
{
    test_struct_t *elem_p = NULL;
    test_struct_t *elem_get_p = NULL;
    int idx;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    elem_p = clist_add_last(tested_clist);
    elem_p->b = 1;
    elem_p = clist_add_last(tested_clist);
    elem_p->b = 2;
    elem_p = clist_add_last(tested_clist);
    elem_p->b = 3;
    elem_p = clist_add_last(tested_clist);
    elem_p->b = 4;
    elem_p = clist_add_last(tested_clist);
    elem_p->b = 5;
    /* When */
    elem_get_p = clist_get_last(tested_clist);
    /* Check */
    for (idx = 5; idx >= 1; idx--)
    {
        LU_ASSERT(elem_get_p != NULL);
        LU_ASSERT(elem_get_p->b == idx);
        elem_get_p = clist_get_prev(tested_clist, elem_get_p);
    }
}

LU_TEST(test_suite_clistlib, test_clist_get_last)
{
    test_struct_t *elem_p = NULL;
    test_struct_t *elem_get_p = NULL;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    elem_p = clist_add_first(tested_clist);
    elem_p->str = "TestString";
    clist_add_first(tested_clist);
    clist_add_first(tested_clist);
    clist_add_first(tested_clist);
    /* When */
    elem_get_p = clist_get_last(tested_clist);
    /* Check */
    LU_ASSERT(elem_p != NULL);
    LU_ASSERT(elem_get_p == elem_p);
    LU_ASSERT_STR_EQ("TestString", elem_get_p->str);
}


LU_TEST(test_suite_clistlib, test_clist_remove_first)
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
    LU_ASSERT(elem_get_p != NULL);
    LU_ASSERT_STR_EQ("Elem1", elem_get_p->str);
}

LU_TEST(test_suite_clistlib, test_clist_remove_tail)
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
    LU_ASSERT(elem_get_p != NULL);
    LU_ASSERT(clist_get_next(tested_clist, elem_get_p) == NULL);
    LU_ASSERT_STR_EQ("Elem2", elem_get_p->str);
}

LU_TEST(test_suite_clistlib, test_clist_remove_middle)
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
    LU_ASSERT(elem_get_p == elem_3);
    LU_ASSERT(clist_get_next(tested_clist, elem_get_p) == elem_1);
}

LU_TEST(test_suite_clistlib, test_clist_iterators)
{
    test_struct_t *elem = NULL;
    char check_c;
    int nof_checks;

    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    
    /* When */
    elem = clist_add_last(tested_clist);
    elem->a = 'A';
    elem = clist_add_last(tested_clist);
    elem->a = 'B';
    elem = clist_add_last(tested_clist);
    elem->a = 'C';
    elem = clist_add_last(tested_clist);
    elem->a = 'D';
    
    /* Check */
    check_c = 'A';
    nof_checks = 0;
    clist_iterate(tested_clist, elem)
    {
        LU_ASSERT(elem->a == check_c);
        check_c++;
        nof_checks++;
    }
    LU_ASSERT(nof_checks == 4);
    
    check_c = 'D';
    nof_checks = 0;
    clist_reverse_iterate(tested_clist, elem)
    {
        LU_ASSERT(elem->a == check_c);
        check_c--;
        nof_checks++;
    }
    LU_ASSERT(nof_checks == 4);
}

void test_struct_t_destroy(clist_elem_p element)
{
    test_struct_t *concrete_elem = element;
    if (concrete_elem->str)
        free(concrete_elem->str);
    concrete_elem->str = NULL;
}

LU_TEST(test_suite_clistlib, test_clist_custom_destructor)
{
    test_struct_t *elem;
    test_struct_t *elem_get;
    /* Given */
    tested_clist = clist_create(sizeof(test_struct_t));
    elem = clist_add_last(tested_clist);
    elem->str = malloc(100);
    sprintf(elem->str, "Element1");
    elem = clist_add_last(tested_clist);
    elem->str = malloc(10);
    sprintf(elem->str, "Element2");
    elem = clist_add_last(tested_clist);
    elem->str = malloc(200);
    sprintf(elem->str, "Element3");

    /* When */
    clist_set_element_destructor(tested_clist, test_struct_t_destroy);

    /* Check */
    elem_get = clist_get_first(tested_clist);
    LU_ASSERT_STR_EQ("Element1", elem_get->str);
    clist_remove(tested_clist, elem_get);
    elem_get = clist_get_first(tested_clist);
    LU_ASSERT_STR_EQ("Element2", elem_get->str);
    elem_get = clist_get_next(tested_clist, elem_get);
    LU_ASSERT_STR_EQ("Element3", elem_get->str);
    clist_free(tested_clist); /* Running this test with mem-leak
                                 framework (like valgrind) will
                                 detect issues with destructor */
    tested_clist = NULL;
}

int test_clistlib_suite_runner(void)
{
    printf("\n\n~~ CListLib Tests:\n");
    LU_SUITE_RUN(test_suite_clistlib);
    LU_SUITE_REPORT(test_suite_clistlib);
    return LU_SUITE_STATUS(test_suite_clistlib);
}