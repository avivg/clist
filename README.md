# clist     [![Build Status](https://travis-ci.org/avivg/clist.svg?branch=master)](https://travis-ci.org/avivg/clist)
> Double Linked List, ansi-C implementation, with super simple interface.

With this list, the user can ignore the internal management of head, tail, next, prev, etc. and consentrate on the data itself. The user only have it's own data structure pointers to deal with and no pesky shims or list constructs needs to be added to it.

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
        point *p, *p1, *p2;
        clist_t lst = clist_create(sizeof(point));

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

Will result with:

    x: 100, y: 200
    x: 300, y: 400

Updated code available in [basic example](example/basic_example.c)

See [API](clistlib/include/clist.h)

## Build
To create a static library under `./clistlib/bin`:

    make

Run the tests (Will pull [minunit](https://github.com/siu/minunit)):

    git submodule init
    make test

To run valgrind tests (assuming it's installed and in PATH):

    make test_valg

## More examples
To implement the "classic" linked list, where the user can remove the objects from the list _without releasing them_, simply define the list managed object as a pointer to the user data and dereferece the returned values from the list api.
See [classic example](example/classic_example.c)

## TODO
* Try to create test double for malloc/clu_alloc and test allocation error handling
