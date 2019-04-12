[![Build Status](https://travis-ci.org/avivg/clist.svg?branch=master)](https://travis-ci.org/avivg/clist)
# clist
> Double Linked List, ansi-C implementation, with super simple interface.

[API](clistlib/include/clist.h)

## Build
Create a static library under `./clistlib/bin`:

    make

Run the tests (Will pull [minunit](https://github.com/siu/minunit)):

    git submodule init
    make test

To run valgrind tests (assuming it's installed and in PATH):

    make test_valg

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
        point *p1;
        clist_t lst = clist_create(sizeof(point));

        p1 = clist_add_first(lst);
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

See [example](example/)

## TODO
* Allow custom element destruction callback
* Iteration macro
* Try to create test double for malloc/clu_alloc and test allocation error handling
