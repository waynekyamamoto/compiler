int printf(int *fmt, ...);
int strcmp(int *s1, int *s2);

// Static global variable
static int sg_counter = 10;

// Static global array
static int sg_arr[4] = {1, 2, 3, 4};

// Static function
static int static_add(int a, int b) {
    return a + b;
}

// Static function modifying static global
static int inc_counter() {
    sg_counter = sg_counter + 1;
    return sg_counter;
}

// Non-static function (should still have .globl)
int public_func(int x) {
    return x * 2;
}

// Static uninitialized global
static int sg_uninit;

// Static global with string init
static int *sg_str = "hello_static";

int main() {
    int fail = 0;

    // Static global variable
    if (sg_counter != 10) { printf("FAIL: sg_counter=%d\n", sg_counter); fail = 1; }

    // Static global array
    if (sg_arr[0] != 1) { printf("FAIL: sg_arr[0]=%d\n", sg_arr[0]); fail = 1; }
    if (sg_arr[3] != 4) { printf("FAIL: sg_arr[3]=%d\n", sg_arr[3]); fail = 1; }

    // Static function
    if (static_add(3, 4) != 7) { printf("FAIL: static_add(3,4)=%d\n", static_add(3, 4)); fail = 1; }

    // Static function modifying static global
    if (inc_counter() != 11) { printf("FAIL: inc_counter()=%d\n", inc_counter()); fail = 1; }
    if (inc_counter() != 12) { printf("FAIL: inc_counter() 2nd=%d\n", inc_counter()); fail = 1; }

    // Public function
    if (public_func(5) != 10) { printf("FAIL: public_func(5)=%d\n", public_func(5)); fail = 1; }

    // Static uninitialized global (should be zero)
    if (sg_uninit != 0) { printf("FAIL: sg_uninit=%d\n", sg_uninit); fail = 1; }

    // Static string global
    if (strcmp(sg_str, "hello_static") != 0) { printf("FAIL: sg_str=%s\n", sg_str); fail = 1; }

    if (fail == 0) {
        printf("All static tests passed!\n");
    }
    return fail;
}
