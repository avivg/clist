#include <clist.h>
#include <internal/clist_util.h>

void clist_free(clist_t clist)
{
    clist_util_free(clist);
}

clist_t clist_create(size_t element_size)
{
    return (clist_t)clist_util_alloc(sizeof(struct clist_s));
}