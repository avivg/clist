#ifndef __CLIST_INTERNAL_H__
#define __CLIST_INTERNAL_H__

#include <stdint.h>  /* For uint8_t */
#include <clist.h> /* Needed for some types */

/*
 * TYPES
 */

typedef struct
{
    clist_elem_p next;
    clist_elem_p prev;
} clist_element_tag_t;

struct clist_s
{
    clist_element_tag_t head_sentinel;
    clist_element_tag_t tail_sentinel;
    size_t elem_size;
};



/*
 * MACROS
 */

#define TAG_SIZE                (sizeof(clist_element_tag_t))

#define ELEMENT_TAG(__elem)     ( (clist_element_tag_t*)( ((uint8_t*)(__elem)) - TAG_SIZE) )
#define TAG_ELEMENT(__tag)      ( (        clist_elem_p)( ((uint8_t*)(__tag )) + TAG_SIZE) )

#define ELEMENT_NEXT(__elem)    (ELEMENT_TAG(__elem)->next)
#define ELEMENT_PREV(__elem)    (ELEMENT_TAG(__elem)->prev)

#define LIST_START(__lst)        (TAG_ELEMENT(&((__lst)->head_sentinel)))
#define LIST_END(__lst)          (TAG_ELEMENT(&((__lst)->tail_sentinel)))

#define NULL_CHECK(__ptr) \
        do { if (NULL == (__ptr)) return NULL; } while(0)
#define NULL_CHECK_VOID(__ptr) \
        do { if (NULL == (__ptr)) return; } while(0)

/*
 * Internal APIs
 */

void clist_remove_after(clist_t, clist_elem_p prev, clist_elem_p element);

clist_elem_p clist_element_create(clist_t);
void clist_element_free(clist_elem_p);

#endif /* __CLIST_INTERNAL_H__ */