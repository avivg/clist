/*
 * This is an example of a "classic" linked list implementation,
 * in the sense that the user data is managed by the user.
 * For example, user data elements may be taken out of the list
 * without having their memory freed.
 */

#include <stdio.h>
#include <clist.h>

typedef struct
{
    int x;
    int y;
} point;

typedef struct
{
    point *data;
} element_t;

/* It's possible to define element_t as point* directly
   (typedef point *element_t) and then replace all 'elem->data' below
   with (*elem) */

/* Create the list containing only pointer to the data */
clist_t point_list_create()
{
    return clist_create(sizeof(element_t));
}

/* Add (allocate) a pointer to the list and make it point to the user data */
void point_list_add(clist_t list, point * p)
{
    element_t *elem = clist_add_last(list);
    elem->data = p;
}

/* Use the pointers returned from the list to print all the points */
void point_list_print(clist_t list)
{
    element_t *pt;
    clist_iterate(list, pt)
    {
        printf("x: %d, y: %d\n", pt->data->x, pt->data->y);
    }
}

/* Release the list and all the allocated pointers */
void point_list_free(clist_t list)
{
    clist_free(list);
}

int main(int ac, char **av)
{
    point p1, p2;
    clist_t list;

    /* The points are not allocated by the list, only a pointer to them. */
    p1.x = 100;
    p1.y = 200;

    p2.x = 300;
    p2.y = 400;

    /* The list will contain pointers to user data, not the data itself */
    list = point_list_create();
    point_list_add(list, &p1);
    point_list_add(list, &p2);
    point_list_print(list);

    /* Freeing leaves the points intact */
    point_list_free(list);
}