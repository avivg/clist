#include <stdlib.h>

extern int test_clistlib_suite_runner(void);
extern int test_clist_util_suite_runner(void);

int main() {
    int failures = 0;

    failures += test_clistlib_suite_runner();
    failures += test_clist_util_suite_runner();

    if (failures)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}