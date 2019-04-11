#include <stdlib.h>

extern void test_clistlib_suite_runner(void);
extern void test_clist_util_suite_runner(void);

int main() {

    test_clistlib_suite_runner();
    test_clist_util_suite_runner();

    return EXIT_SUCCESS;
}