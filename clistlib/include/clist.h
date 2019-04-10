#ifndef __CLIST_H__
#define __CLIST_H__

#include <stdlib.h>

struct clist_s
{
    void *head;
    size_t elem_size;
};

typedef struct clist_s * clist_t;

void clist_free(clist_t clist);
clist_t clist_create(size_t element_size);

void * clist_add_top(clist_t);
void * clist_get_top(clist_t);

#endif /* __CLIST_H__ */