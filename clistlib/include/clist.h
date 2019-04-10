#ifndef __CLIST_H__
#define __CLIST_H__

#include <stdlib.h>
#include <clist_types.h>

/* Allocates a new list for elements with size 's'.
   The size is the user's data size. */
clist_t clist_create(size_t s);

/* Frees a list */
void clist_free(clist_t);

/* Allocates and adds an element as the first in the list.
   Returns the newly allocated element. */
clist_element_handle_t clist_add_top(clist_t);

/* Allocates and adds and element after 'prev' */
clist_element_handle_t clist_add_after(clist_t, clist_element_handle_t prev);

/* Return the first element in the list */
clist_element_handle_t clist_get_top(clist_t);

/* Return the next element after 'e' in the list */
clist_element_handle_t clist_get_next(clist_t, clist_element_handle_t e);

/* Remove element 'e' from the list */
void clist_remove(clist_t, clist_element_handle_t e);

#endif /* __CLIST_H__ */