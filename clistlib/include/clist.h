#ifndef __CLIST_H__
#define __CLIST_H__

#include <stdlib.h>  /* For size_t */

typedef struct clist_s * clist_t;
typedef void * clist_elem_p;

/* Allocates a new list for elements with size 's'.
   The size is the user's data size. */
clist_t clist_create(size_t s);

/* Frees a list (release all the elements) */
void clist_free(clist_t);

/* Allocates and adds an element as the first in the list.
   Returns the newly allocated element. */
clist_elem_p clist_add_first(clist_t);

/* Allocates and adds an element as the last in the list.
   Returns the newly allocated element. */
clist_elem_p clist_add_last(clist_t);

/* Allocates and adds and element after 'prev' */
clist_elem_p clist_add_after(clist_t, clist_elem_p prev);

/* Return the first element in the list */
clist_elem_p clist_get_first(clist_t);

/* Return the last element in the list */
clist_elem_p clist_get_last(clist_t);

/* Return the next element after 'e' in the list */
clist_elem_p clist_get_next(clist_t, clist_elem_p e);

/* Remove element 'e' from the list */
void clist_remove(clist_t, clist_elem_p e);

#endif /* __CLIST_H__ */