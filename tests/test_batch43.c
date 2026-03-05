/* test_batch43: struct array indexing via function parameter */
int printf(char *fmt, ...);

struct Item {
    int id;
    int value;
    int flags;
};

int sum_items(struct Item *items, int n) {
    int total = 0;
    int i = 0;
    while (i < n) {
        total = total + items[i].value;
        i = i + 1;
    }
    return total;
}

int get_flag(struct Item *items, int idx) {
    return items[idx].flags;
}

int main() {
    int fail = 0;

    struct Item arr[3];
    arr[0].id = 1;  arr[0].value = 10; arr[0].flags = 100;
    arr[1].id = 2;  arr[1].value = 20; arr[1].flags = 200;
    arr[2].id = 3;  arr[2].value = 30; arr[2].flags = 300;

    /* Test 1: sum via pointer param */
    int s = sum_items(arr, 3);
    if (s != 60) { printf("FAIL: sum %d != 60\n", s); fail = 1; }

    /* Test 2: index via pointer param */
    int f = get_flag(arr, 2);
    if (f != 300) { printf("FAIL: flag %d != 300\n", f); fail = 1; }

    /* Test 3: index 0 */
    int f0 = get_flag(arr, 0);
    if (f0 != 100) { printf("FAIL: flag0 %d != 100\n", f0); fail = 1; }

    if (!fail) printf("batch43: all tests passed\n");
    return fail;
}
