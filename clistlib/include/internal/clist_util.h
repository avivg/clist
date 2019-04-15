#ifndef __CLIST_UTIL_H__
#define __CLIST_UTIL_H__

#include <stdlib.h>

void clu_free(void*);
void* clu_alloc(size_t size);
void clu_memset(void *buf, char val, size_t size);

#endif