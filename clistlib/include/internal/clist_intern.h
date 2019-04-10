#ifndef __CLIST_INTERNAL_H__
#define __CLIST_INTERNAL_H__

#include <stdlib.h>
#include <stdint.h>
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
    clist_element_handle_t next;
} clist_element_tag_t;



/*
 * MACROS
 */

#define TAG_SIZE                (sizeof(clist_element_tag_t))

#define ELEMENT_TAG(__elem)     ( (clist_element_tag_t*)   ( ((uint8_t*)(__elem)) - TAG_SIZE) )
#define TAG_ELEMENT(__tag)      ( (clist_element_handle_t) ( ((uint8_t*)(__tag))  + TAG_SIZE) )

#define ELEMENT_NEXT(__elem)    (ELEMENT_TAG(__elem)->next)

/*
 * Internal APIs
 */

void clist_remove_first(clist_t);
void clist_remove_middle(clist_t, clist_element_handle_t);

clist_element_handle_t clist_element_create(clist_t);
void clist_element_free(clist_element_handle_t);

#endif /* __CLIST_INTERNAL_H__ */