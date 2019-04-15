#include <internal/clist_util.h>

void* clu_alloc(size_t size)
{
    void *blob = malloc(size);
    if (blob)
    {
        clu_memset(blob, 0, size);
    }
    return blob;
}

void clu_free(void *buf)
{
    free(buf);
}

void clu_memset(void *buf, char val, size_t size)
{
    char *cp = (char*)buf;
    while(size--)
    {
        *cp++ = val;
    }
}