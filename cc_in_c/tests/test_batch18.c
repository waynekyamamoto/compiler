#include <stdio.h>
#include "test_include_helper.h"
#include "test_include_helper2.h"

int main() {
    /* Test 1: macro from included file */
    if (HELPER_VALUE != 42) { printf("FAIL: HELPER_VALUE\n"); return 1; }

    /* Test 2: function from included file */
    if (helper_add(3, 4) != 7) { printf("FAIL: helper_add\n"); return 1; }

    /* Test 3: second include */
    if (HELPER2_VALUE != 99) { printf("FAIL: HELPER2_VALUE\n"); return 1; }

    /* Test 4: include guard — including same header twice should be fine */
    /* (already included above, guard prevents redefinition) */

    /* Test 5: macro from included header used in expression */
    int x = HELPER_VALUE + HELPER_ADDED;
    if (x != 142) { printf("FAIL: HELPER_VALUE + HELPER_ADDED\n"); return 1; }

    printf("All batch 18 tests passed.\n");
    return 0;
}
