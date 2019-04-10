#ifndef __CLIST_H__
#define __CLIST_H__

#include <stdlib.h>

struct clist_s
{
    
};

typedef struct clist_s * clist_t;

void clist_free(clist_t clist);
clist_t clist_create(size_t element_size);


#endif /* __CLIST_H__ */