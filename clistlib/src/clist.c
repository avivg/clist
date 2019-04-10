#include <clist.h>
#include <internal/clist_util.h>

void clist_free(clist_t clist)
{
    clist_element_handle_t elem = clist_get_top(clist);
    while(elem)
    {
        clist_element_handle_t next = clist_get_next(clist, elem);
        clist_remove(clist, elem);
        elem = next;
    }
    clu_free(clist);
}

clist_t clist_create(size_t element_size)
{
    clist_t new_list = clu_alloc(sizeof(struct clist_s));
    clu_memset(new_list, 0, sizeof(struct clist_s));
    new_list->elem_size = element_size;

    return new_list;
}


typedef struct
{
    clist_element_handle_t *next;
} clist_element_tag_t;

clist_element_handle_t clist_add_top(clist_t lst)
{
    size_t full_element_size = lst->elem_size + sizeof(clist_element_tag_t);
    void * new_element = clu_alloc(full_element_size);
    clu_memset(new_element, 0, full_element_size);
    ((clist_element_tag_t*)new_element)->next = lst->head;
    lst->head = new_element + sizeof(clist_element_tag_t);
    return lst->head;
}

clist_element_handle_t clist_get_top(clist_t lst)
{
    return lst->head;
}

clist_element_handle_t clist_get_next(clist_t lst, clist_element_handle_t element)
{
    clist_element_tag_t *elem_tag = element - sizeof(clist_element_tag_t);
    return elem_tag->next;
}

void clist_remove_first(clist_t lst)
{
    clist_element_tag_t *elem_tag = lst->head - sizeof(clist_element_tag_t);
    lst->head = elem_tag->next;
    clu_free(elem_tag);
}

void clist_remove_middle(clist_t lst, clist_element_handle_t element)
{
    
}

void clist_remove(clist_t lst, clist_element_handle_t element)
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

