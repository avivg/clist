#include <internal/clist_util.h>

void* clu_alloc(size_t size)
{
    return malloc(size);
}

void clu_free(void *buf)
{
    free(buf);
}

void clu_memset(void *buf, char val, size_t size)
{
    char *cp = buf;
    while(size--)
    {
        *cp++ = val;
    }
}