#ifndef __CLIST_INTERNAL_H__
#define __CLIST_INTERNAL_H__

#include <stdlib.h>
#include <clist_types.h>

/*
 * TYPES
 */

struct clist_s
{
    void *head;
    size_t elem_size;
};

typedef struct
{
    clist_element_handle_t *next;
} clist_element_tag_t;



/*
 * MACROS
 */



/*
 * Internal APIs
 */

void clist_remove_first(clist_t);
void clist_remove_middle(clist_t, clist_element_handle_t);

#endif /* __CLIST_INTERNAL_H__ */