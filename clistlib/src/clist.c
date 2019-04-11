#include <clist.h>
#include <internal/clist_util.h>
#include <internal/clist_intern.h>

clist_t clist_create(size_t element_size)
{
    clist_t new_list = clu_alloc(sizeof(struct clist_s));
    if (new_list)
    {
        new_list->elem_size = element_size;
    }
    return new_list;
}

void clist_free(clist_t clist)
{
    clist_elem_p elem = clist_get_first(clist);
    while(elem)
    {
        clist_elem_p next = clist_get_next(clist, elem);
        clist_remove(clist, elem);
        elem = next;
    }
    clu_free(clist);
}


clist_elem_p clist_add_first(clist_t lst)
{
    if (lst)
    {
        return clist_add_after(lst, TAG_ELEMENT(&lst->head_sentinel));
    }
    return NULL;
}

clist_elem_p clist_add_last(clist_t lst)
{
    if (lst)
    {
        clist_elem_p prev = clist_get_first(lst);
        if (prev)
        {
            for (/* empty */;
                 clist_get_next(lst, prev);
                 prev = clist_get_next(lst, prev));
            return clist_add_after(lst, prev);
        }
        else
        {
            return clist_add_first(lst);
        }
    }
    return NULL;
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

clist_elem_p clist_get_first(clist_t lst)
{
    return ELEMENT_NEXT(TAG_ELEMENT(&lst->head_sentinel));
}

clist_elem_p clist_get_last(clist_t lst)
{
    if (lst)
    {
        clist_elem_p prev = clist_get_first(lst);
        for (/* empty */;
                clist_get_next(lst, prev);
                prev = clist_get_next(lst, prev));
        return prev;
    }
    return NULL;
}

clist_elem_p clist_get_next(clist_t lst, clist_elem_p element)
{
    return ELEMENT_NEXT(element);
}

void clist_remove(clist_t lst, clist_elem_p element)
{
    if (lst)
    {
        clist_elem_p prev = TAG_ELEMENT(&lst->head_sentinel);
        while (prev && ELEMENT_NEXT(prev) != element)
        {
            prev = clist_get_next(lst, prev);
        }
        clist_remove_after(lst, prev, element);
    }
}

void clist_remove_after(clist_t lst, clist_elem_p prev, clist_elem_p element)
{
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