#ifndef __CLIST_INTERNAL_H__
#define __CLIST_INTERNAL_H__

#include <stdint.h>  /* For uint8_t */
#include <clist.h> /* Needed for some types */

/*
 * TYPES
 */

struct clist_s
{
    clist_elem_p head;
    size_t elem_size;
};

typedef struct
{
    clist_elem_p next;
} clist_element_tag_t;



/*
 * MACROS
 */

#define TAG_SIZE                (sizeof(clist_element_tag_t))

#define ELEMENT_TAG(__elem)     ( (clist_element_tag_t*)( ((uint8_t*)(__elem)) - TAG_SIZE) )
#define TAG_ELEMENT(__tag)      ( (        clist_elem_p)( ((uint8_t*)(__tag )) + TAG_SIZE) )

#define ELEMENT_NEXT(__elem)    (ELEMENT_TAG(__elem)->next)

/*
 * Internal APIs
 */

void clist_remove_first(clist_t);
void clist_remove_middle(clist_t, clist_elem_p);

clist_elem_p clist_element_create(clist_t);
void clist_element_free(clist_elem_p);

#endif /* __CLIST_INTERNAL_H__ */