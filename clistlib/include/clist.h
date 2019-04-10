#ifndef __CLIST_H__
#define __CLIST_H__

#include <stdlib.h>

struct clist_s
{
    void *head;
    size_t elem_size;
};

typedef struct clist_s * clist_t;
typedef void * clist_element_handle_t;

void clist_free(clist_t clist);
clist_t clist_create(size_t element_size);

clist_element_handle_t clist_add_top(clist_t);
clist_element_handle_t clist_get_top(clist_t);

clist_element_handle_t clist_get_next(clist_t, clist_element_handle_t);
void clist_remove(clist_t, clist_element_handle_t);

#endif /* __CLIST_H__ */