[![Build Status](https://travis-ci.org/avivg/clist.svg?branch=master)](https://travis-ci.org/avivg/clist)
# clist
> Linked list implementation in C with super simple interface.

[API](clistlib/include/clist.h)

## Usage

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

        point *p1 = clist_add_first(lst);
        p1->x = 100;
        p1->y = 200;
        
        point *p2 = clist_add_after(lst, p1);
        p2->x = 300;
        p2->y = 400;

        for (point *p = clist_get_first(lst); p; p = clist_get_next(lst, p))
        {
            printf("x: %d, y: %d\n", p->x, p->y);
        }

        clist_free(lst);
    }

Will result with:

    x: 100, y: 200
    x: 300, y: 400

## Running the tests
To run the test suite, 'git submodule init' and 'git submodule update',

## TODO
* Add get_prev
* Allow custom element destruction callback
* Iteration macro
* Try to create test double for malloc/clu_alloc and test allocation error handling
