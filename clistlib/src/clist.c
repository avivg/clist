#include <clist.h>
#include <internal/clist_util.h>

void clist_free(clist_t clist)
{
    clu_free(clist->head);
    clu_free(clist);
}

clist_t clist_create(size_t element_size)
{
    clist_t new_list = clu_alloc(sizeof(struct clist_s));
    clu_memset(new_list, 0, sizeof(struct clist_s));
    new_list->elem_size = element_size;

    return new_list;
}

void * clist_add_top(clist_t lst)
{
    lst->head = clu_alloc(lst->elem_size);
    return lst->head;
}

void * clist_get_top(clist_t lst)
{
    return lst->head;
}
