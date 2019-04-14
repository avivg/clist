/*
 * This is an example of the basic use of clist:
 * The data buffers are allocated and freed by the list
 * api, and the user is left only to fill them and use
 * them directly out of the list.
 * Note that the user data structure does not contain any
 * list management overhead like 'next' pointer, etc.
 */
#include <stdio.h>
#include <clist.h>

typedef struct
{
    int x;
    int y;
} point_t;

int main(int ac, char **av)
{
    point_t *p, *p1, *p2;
    clist_t lst = clist_create(sizeof(point_t));

    p1 = clist_add_first(lst);
    p1->x = 100;
    p1->y = 200;
    
    p2 = clist_add_after(lst, p1);
    p2->x = 300;
    p2->y = 400;

    for (p = clist_get_first(lst); p; p = clist_get_next(lst, p))
    {
        printf("x: %d, y: %d\n", p->x, p->y);
    }

    clist_free(lst);
}
