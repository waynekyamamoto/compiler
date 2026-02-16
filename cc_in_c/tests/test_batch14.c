/* Test batch 14: typedef support and forward struct declarations */
int printf(char *fmt, ...);

/* --- Typedef: basic types --- */
typedef int MyInt;
typedef char MyChar;
typedef void MyVoid;
typedef unsigned long MyULong;

/* --- Typedef: pointer types --- */
typedef int *IntPtr;
typedef char *String;

/* --- Typedef: struct types --- */
struct Point {
    int x;
    int y;
};

typedef struct Point Point;

/* --- Typedef with inline struct definition --- */
typedef struct Rect {
    int x;
    int y;
    int w;
    int h;
} Rect;

/* --- Typedef: chained (typedef of a typedef) --- */
typedef MyInt Score;

/* --- Forward struct declaration --- */
struct Node;

struct Node {
    int val;
    struct Node *next;
};

/* --- Typedef of enum --- */
typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE
} Color;

/* --- Typedef function pointer --- */
typedef int (*BinOp)(int, int);

int add(int a, int b) { return a + b; }

/* --- Test functions --- */

int test_basic_typedef() {
    MyInt x = 42;
    Score s = 100;
    return x + s;
}

int test_pointer_typedef() {
    int val = 77;
    IntPtr p = &val;
    return *p;
}

Point make_point(int x, int y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

int test_struct_typedef() {
    Point p;
    p.x = 10;
    p.y = 20;
    return p.x + p.y;
}

int test_inline_struct_typedef() {
    Rect r;
    r.x = 1;
    r.y = 2;
    r.w = 100;
    r.h = 200;
    return r.w + r.h;
}

int test_enum_typedef() {
    Color c = COLOR_BLUE;
    return c;
}

int test_forward_struct() {
    struct Node n1;
    struct Node n2;
    n1.val = 10;
    n1.next = &n2;
    n2.val = 20;
    n2.next = 0;
    return n1.val + n1.next->val;
}

int main() {
    int fail = 0;

    if (test_basic_typedef() != 142) { printf("FAIL: basic typedef\n"); fail = 1; }
    if (test_pointer_typedef() != 77) { printf("FAIL: pointer typedef\n"); fail = 1; }
    if (test_struct_typedef() != 30) { printf("FAIL: struct typedef\n"); fail = 1; }
    if (test_inline_struct_typedef() != 300) { printf("FAIL: inline struct typedef\n"); fail = 1; }
    if (test_enum_typedef() != 2) { printf("FAIL: enum typedef\n"); fail = 1; }
    if (test_forward_struct() != 30) { printf("FAIL: forward struct\n"); fail = 1; }

    if (!fail) printf("All batch 14 tests passed.\n");
    return fail;
}
