#include <clist.h>
#include <internal/clist_util.h>
#include <internal/clist_intern.h>

void clist_free(clist_t clist)
{
    clist_elem_p elem = clist_get_top(clist);
    while(elem)
    {
        clist_elem_p next = clist_get_next(clist, elem);
        clist_remove(clist, elem);
        elem = next;
    }
    clu_free(clist);
}

clist_t clist_create(size_t element_size)
{
    clist_t new_list = clu_alloc(sizeof(struct clist_s));
    new_list->elem_size = element_size;
    return new_list;
}


clist_elem_p clist_add_top(clist_t lst)
{
    clist_elem_p new_element = clist_element_create(lst);
    ELEMENT_NEXT(new_element) = lst->head;
    lst->head = new_element;
    return new_element;
}

clist_elem_p clist_add_after(clist_t lst, clist_elem_p prev)
{
    clist_elem_p new_element = clist_element_create(lst);
    ELEMENT_NEXT(new_element) = ELEMENT_NEXT(prev);
    ELEMENT_NEXT(prev) = new_element;
    return new_element;
}


clist_elem_p clist_element_create(clist_t lst)
{
    size_t full_element_size = lst->elem_size + TAG_SIZE;
    clist_element_tag_t *new_elem_tag = clu_alloc(full_element_size);
    return TAG_ELEMENT(new_elem_tag);
}

clist_elem_p clist_get_top(clist_t lst)
{
    return lst->head;
}

clist_elem_p clist_get_next(clist_t lst, clist_elem_p element)
{
    return ELEMENT_NEXT(element);
}

void clist_remove(clist_t lst, clist_elem_p element)
{
    if (element == lst->head)
    {
        clist_remove_first(lst);
    }
    else
    {
        clist_remove_middle(lst, element);
    }
}

void clist_remove_first(clist_t lst)
{
    clist_elem_p old_head = lst->head;
    lst->head = ELEMENT_NEXT(lst->head);
    clist_element_free(old_head);
}

void clist_remove_middle(clist_t lst, clist_elem_p element)
{
    clist_elem_p prev = lst->head;
    while (prev && ELEMENT_NEXT(prev) != element)
    {
        prev = clist_get_next(lst, prev);
    }
    if (prev)
    {
        ELEMENT_NEXT(prev) = ELEMENT_NEXT(element);
        clist_element_free(element);
    }
}

void clist_element_free(clist_elem_p elem)
{
    if (elem)
    {
        clu_free(ELEMENT_TAG(elem));
    }
}