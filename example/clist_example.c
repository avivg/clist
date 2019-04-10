#include <stdio.h>
#include <clist.h>

typedef struct
{
    int x;
    int y;
} point;

int main(int ac, char **av)
{
    clist_t lst = clist_create(sizeof(point));

    point *p1 = clist_add_top(lst);
    p1->x = 100;
    p1->y = 200;
    
    point *p2 = clist_add_after(lst, p1);
    p2->x = 300;
    p2->y = 400;

    for (point *p = clist_get_top(lst); p; p = clist_get_next(lst, p))
    {
        printf("x: %d, y: %d\n", p->x, p->y);
    }

    clist_free(lst);
}