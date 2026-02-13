# ---------- Basic ----------

def test_hello_world(compile_and_run):
    src = """\
int main() {
    printf("hello world\\n");
    return 0;
}
"""
    assert compile_and_run(src) == "hello world\n"


def test_return_exit_code(compile_and_run_rc):
    src = """\
int main() {
    return 42;
}
"""
    _, rc = compile_and_run_rc(src)
    assert rc == 42


# ---------- Arithmetic & Unary ----------

def test_arithmetic(compile_and_run):
    src = """\
int main() {
    printf("%d\\n", 2 + 3);
    printf("%d\\n", 10 - 4);
    printf("%d\\n", 3 * 7);
    printf("%d\\n", 20 / 4);
    printf("%d\\n", 17 % 5);
    return 0;
}
"""
    assert compile_and_run(src) == "5\n6\n21\n5\n2\n"


def test_unary_negation(compile_and_run):
    src = """\
int main() {
    int x = 10;
    printf("%d\\n", -x);
    return 0;
}
"""
    assert compile_and_run(src) == "-10\n"


def test_logical_not(compile_and_run):
    src = """\
int main() {
    printf("%d %d\\n", !0, !5);
    return 0;
}
"""
    assert compile_and_run(src) == "1 0\n"


# ---------- Comparisons & Logical ----------

def test_comparisons(compile_and_run):
    src = """\
int main() {
    printf("%d %d\\n", 1 == 1, 1 == 2);
    printf("%d %d\\n", 1 != 2, 1 != 1);
    printf("%d %d\\n", 1 < 2, 2 < 1);
    printf("%d %d\\n", 2 <= 2, 3 <= 2);
    printf("%d %d\\n", 3 > 2, 2 > 3);
    printf("%d %d\\n", 2 >= 2, 1 >= 2);
    return 0;
}
"""
    expected = "1 0\n1 0\n1 0\n1 0\n1 0\n1 0\n"
    assert compile_and_run(src) == expected


def test_logical_and_or(compile_and_run):
    src = """\
int main() {
    printf("%d %d %d\\n", 1 && 1, 1 && 0, 0 && 1);
    printf("%d %d %d\\n", 1 || 0, 0 || 1, 0 || 0);
    return 0;
}
"""
    assert compile_and_run(src) == "1 0 0\n1 1 0\n"


# ---------- Variables ----------

def test_variable_init(compile_and_run):
    src = """\
int main() {
    int x = 5;
    int y = 10;
    printf("%d\\n", x + y);
    return 0;
}
"""
    assert compile_and_run(src) == "15\n"


def test_multiple_declarations(compile_and_run):
    src = """\
int main() {
    int a, b;
    a = 3;
    b = 7;
    printf("%d\\n", a + b);
    return 0;
}
"""
    assert compile_and_run(src) == "10\n"


# ---------- Control Flow ----------

def test_if_else(compile_and_run):
    src = """\
int main() {
    int x = 5;
    if (x > 3) {
        printf("yes\\n");
    } else {
        printf("no\\n");
    }
    if (x > 10) {
        printf("big\\n");
    } else {
        printf("small\\n");
    }
    return 0;
}
"""
    assert compile_and_run(src) == "yes\nsmall\n"


def test_while_loop(compile_and_run):
    src = """\
int main() {
    int i = 0;
    int sum = 0;
    while (i < 5) {
        sum = sum + i;
        i = i + 1;
    }
    printf("%d\\n", sum);
    return 0;
}
"""
    assert compile_and_run(src) == "10\n"


def test_for_loop(compile_and_run):
    src = """\
int main() {
    int sum = 0;
    for (int i = 1; i <= 10; i = i + 1) {
        sum = sum + i;
    }
    printf("%d\\n", sum);
    return 0;
}
"""
    assert compile_and_run(src) == "55\n"


def test_break(compile_and_run):
    src = """\
int main() {
    int i = 0;
    while (1) {
        if (i == 3) {
            break;
        }
        i = i + 1;
    }
    printf("%d\\n", i);
    return 0;
}
"""
    assert compile_and_run(src) == "3\n"


def test_continue(compile_and_run):
    src = """\
int main() {
    int sum = 0;
    for (int i = 0; i < 10; i = i + 1) {
        if (i % 2 == 0) {
            continue;
        }
        sum = sum + i;
    }
    printf("%d\\n", sum);
    return 0;
}
"""
    # sum of odd numbers 1+3+5+7+9 = 25
    assert compile_and_run(src) == "25\n"


# ---------- Functions ----------

def test_function_call(compile_and_run):
    src = """\
int add(int a, int b) {
    return a + b;
}
int main() {
    printf("%d\\n", add(3, 4));
    return 0;
}
"""
    assert compile_and_run(src) == "7\n"


def test_recursion_fibonacci(compile_and_run):
    src = """\
int fib(int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}
int main() {
    printf("%d\\n", fib(10));
    return 0;
}
"""
    assert compile_and_run(src) == "55\n"


# ---------- Pointers ----------

def test_pointer_deref(compile_and_run):
    src = """\
int main() {
    int x = 42;
    int *p = &x;
    printf("%d\\n", *p);
    return 0;
}
"""
    assert compile_and_run(src) == "42\n"


def test_pointer_write(compile_and_run):
    src = """\
int main() {
    int x = 1;
    int *p = &x;
    *p = 99;
    printf("%d\\n", x);
    return 0;
}
"""
    assert compile_and_run(src) == "99\n"


# ---------- Arrays ----------

def test_array(compile_and_run):
    src = """\
int main() {
    int arr[3];
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    printf("%d %d %d\\n", arr[0], arr[1], arr[2]);
    return 0;
}
"""
    assert compile_and_run(src) == "10 20 30\n"


# ---------- Structs ----------

def test_struct_dot_access(compile_and_run):
    src = """\
struct Point {
    int x;
    int y;
};
int main() {
    struct Point p;
    p.x = 3;
    p.y = 4;
    printf("%d %d\\n", p.x, p.y);
    return 0;
}
"""
    assert compile_and_run(src) == "3 4\n"


def test_struct_arrow_access(compile_and_run):
    src = """\
struct Point {
    int x;
    int y;
};
int set_point(struct Point *p, int x, int y) {
    p->x = x;
    p->y = y;
    return 0;
}
int main() {
    struct Point pt;
    set_point(&pt, 10, 20);
    printf("%d %d\\n", pt.x, pt.y);
    return 0;
}
"""
    assert compile_and_run(src) == "10 20\n"


def test_struct_chained_arrow(compile_and_run):
    src = """\
struct Node {
    int val;
    struct Node *next;
};
int main() {
    struct Node b;
    b.val = 42;
    b.next = 0;
    struct Node a;
    a.val = 1;
    a.next = &b;
    printf("%d\\n", a.next->val);
    return 0;
}
"""
    assert compile_and_run(src) == "42\n"
