#include <internal/clist_util.h>

void* clist_util_alloc(size_t size)
{
    return malloc(size);
}

void clist_util_free(void *buf)
{
    free(buf);
}