#include <clist.h>
#include <internal/clist_util.h>
#include <internal/clist_intern.h>

clist_t clist_create(size_t element_size)
{
    clist_t new_list = clu_alloc(sizeof(struct clist_s));
    NULL_CHECK(new_list);

    new_list->elem_size = element_size;
    new_list->head_sentinel.next = LIST_END(new_list);
    new_list->tail_sentinel.prev = LIST_START(new_list);
    return new_list;
}

void clist_free(clist_t lst)
{
    clist_elem_p elem = clist_get_first(lst);
    while(elem)
    {
        clist_elem_p next = clist_get_next(lst, elem);
        clist_remove(lst, elem);
        elem = next;
    }
    NULL_CHECK_VOID(lst);
    clu_free(lst);
}


clist_elem_p clist_add_first(clist_t lst)
{
    NULL_CHECK(lst);
    return clist_add_after(lst, LIST_START(lst));
}

clist_elem_p clist_add_last(clist_t lst)
{
    NULL_CHECK(lst);
    return clist_add_after(lst, ELEMENT_PREV(LIST_END(lst)));
}

clist_elem_p clist_add_after(clist_t lst, clist_elem_p prev)
{
    if (lst && prev)
    {
        clist_elem_p new_element = clist_element_create(lst);
        clist_elem_p old_next = ELEMENT_NEXT(prev);

        ELEMENT_NEXT(new_element) = old_next;
        ELEMENT_PREV(new_element) = prev;

        ELEMENT_NEXT(prev) = new_element;
        if (old_next)
            ELEMENT_PREV(old_next) = new_element;
        
        return new_element;
    }
    return NULL;
}


clist_elem_p clist_element_create(clist_t lst)
{
    if (lst)
    {
        size_t full_element_size = lst->elem_size + TAG_SIZE;
        clist_element_tag_t *new_elem_tag = clu_alloc(full_element_size);
        return TAG_ELEMENT(new_elem_tag);
    }
    return NULL;
}

clist_elem_p clist_get_first(clist_t lst)
{
    if (lst)
    {
        clist_elem_p first = ELEMENT_NEXT(LIST_START(lst));
        if (first != LIST_END(lst))
            return first;
    }
    return NULL;
}

clist_elem_p clist_get_last(clist_t lst)
{
    if (lst)
    {
        clist_elem_p last = ELEMENT_PREV(LIST_END(lst));
        if (last != LIST_START(lst))
            return last;
    }
    return NULL;
}

clist_elem_p clist_get_next(clist_t lst, clist_elem_p element)
{
    if (element)
    {
        clist_elem_p next = ELEMENT_NEXT(element);
        if (next != LIST_END(lst))
            return next;
    }
    return NULL;
}

clist_elem_p clist_get_prev(clist_t lst, clist_elem_p element)
{
    if (element)
    {
        clist_elem_p prev = ELEMENT_PREV(element);
        if (prev != LIST_START(lst))
            return prev;
    }
    return NULL;
}

void clist_remove(clist_t lst, clist_elem_p element)
{
    NULL_CHECK_VOID(lst);
    NULL_CHECK_VOID(element);
    clist_remove_after(lst, ELEMENT_PREV(element), element);
}

void clist_remove_after(clist_t lst, clist_elem_p prev, clist_elem_p element)
{
    if (prev)
    {
        clist_elem_p new_next = ELEMENT_NEXT(element);
        ELEMENT_NEXT(prev) = new_next;
        ELEMENT_PREV(new_next) = prev;
        clist_element_free(element);
    }
}

void clist_element_free(clist_elem_p element)
{
    NULL_CHECK_VOID(element);
    clu_free(ELEMENT_TAG(element));
}