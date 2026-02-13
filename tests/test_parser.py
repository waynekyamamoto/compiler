import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

import cc


def parse_program(src):
    """Parse full C source into a Program AST."""
    return cc.Parser(cc.lex(src)).parse_program()


def parse_func_body(body_src):
    """Wrap body statements in 'int main() { ... }' and return the stmt list."""
    prog = parse_program(f"int main() {{ {body_src} }}")
    assert len(prog.funcs) == 1
    return prog.funcs[0].body.stmts


def parse_expr(expr_src):
    """Parse a single expression by wrapping in 'return <expr>;'."""
    stmts = parse_func_body(f"return {expr_src};")
    assert len(stmts) == 1
    assert isinstance(stmts[0], cc.Return)
    return stmts[0].expr


# ==================== Expression tests ====================

# ---------- Literals ----------

def test_number():
    e = parse_expr("42")
    assert isinstance(e, cc.Num)
    assert e.value == 42


def test_variable():
    e = parse_expr("x")
    assert isinstance(e, cc.Var)
    assert e.name == "x"


def test_string_literal():
    e = parse_expr('"hello"')
    assert isinstance(e, cc.StrLit)
    assert e.value == "hello"


# ---------- Unary ----------

def test_unary_neg():
    e = parse_expr("-5")
    assert isinstance(e, cc.Unary)
    assert e.op == "-"
    assert isinstance(e.rhs, cc.Num) and e.rhs.value == 5


def test_unary_not():
    e = parse_expr("!x")
    assert isinstance(e, cc.Unary)
    assert e.op == "!"
    assert isinstance(e.rhs, cc.Var) and e.rhs.name == "x"


def test_unary_deref():
    e = parse_expr("*p")
    assert isinstance(e, cc.Unary)
    assert e.op == "*"
    assert isinstance(e.rhs, cc.Var) and e.rhs.name == "p"


def test_unary_addr():
    e = parse_expr("&x")
    assert isinstance(e, cc.Unary)
    assert e.op == "&"
    assert isinstance(e.rhs, cc.Var) and e.rhs.name == "x"


# ---------- Binary / precedence ----------

def test_add():
    e = parse_expr("1 + 2")
    assert isinstance(e, cc.Binary)
    assert e.op == "+"
    assert isinstance(e.lhs, cc.Num) and e.lhs.value == 1
    assert isinstance(e.rhs, cc.Num) and e.rhs.value == 2


def test_precedence_mul_over_add():
    # 1 + 2 * 3  =>  Binary(+, 1, Binary(*, 2, 3))
    e = parse_expr("1 + 2 * 3")
    assert isinstance(e, cc.Binary) and e.op == "+"
    assert isinstance(e.lhs, cc.Num) and e.lhs.value == 1
    assert isinstance(e.rhs, cc.Binary)
    assert e.rhs.op == "*"
    assert e.rhs.lhs.value == 2 and e.rhs.rhs.value == 3


def test_precedence_parens():
    # (1 + 2) * 3  =>  Binary(*, Binary(+, 1, 2), 3)
    e = parse_expr("(1 + 2) * 3")
    assert isinstance(e, cc.Binary) and e.op == "*"
    assert isinstance(e.lhs, cc.Binary) and e.lhs.op == "+"


def test_left_associativity():
    # 1 - 2 - 3  =>  Binary(-, Binary(-, 1, 2), 3)
    e = parse_expr("1 - 2 - 3")
    assert isinstance(e, cc.Binary) and e.op == "-"
    assert isinstance(e.lhs, cc.Binary) and e.lhs.op == "-"
    assert isinstance(e.rhs, cc.Num) and e.rhs.value == 3


def test_comparison_lower_than_arith():
    # a + 1 < b  =>  Binary(<, Binary(+, a, 1), b)
    e = parse_expr("a + 1 < b")
    assert isinstance(e, cc.Binary) and e.op == "<"
    assert isinstance(e.lhs, cc.Binary) and e.lhs.op == "+"


def test_logical_and():
    e = parse_expr("a && b")
    assert isinstance(e, cc.Binary) and e.op == "&&"


def test_logical_or_lower_than_and():
    # a || b && c  =>  Binary(||, a, Binary(&&, b, c))
    e = parse_expr("a || b && c")
    assert isinstance(e, cc.Binary) and e.op == "||"
    assert isinstance(e.rhs, cc.Binary) and e.rhs.op == "&&"


# ---------- Assignment ----------

def test_assign():
    e = parse_expr("x = 5")
    assert isinstance(e, cc.Assign)
    assert isinstance(e.target, cc.Var) and e.target.name == "x"
    assert isinstance(e.rhs, cc.Num) and e.rhs.value == 5


# ---------- Call ----------

def test_call_no_args():
    e = parse_expr("foo()")
    assert isinstance(e, cc.Call)
    assert e.name == "foo"
    assert e.args == []


def test_call_with_args():
    e = parse_expr("add(1, 2)")
    assert isinstance(e, cc.Call)
    assert e.name == "add"
    assert len(e.args) == 2
    assert isinstance(e.args[0], cc.Num) and e.args[0].value == 1
    assert isinstance(e.args[1], cc.Num) and e.args[1].value == 2


# ---------- Index ----------

def test_index():
    e = parse_expr("arr[0]")
    assert isinstance(e, cc.Index)
    assert isinstance(e.base, cc.Var) and e.base.name == "arr"
    assert isinstance(e.index, cc.Num) and e.index.value == 0


# ==================== Statement tests ====================

def test_return_stmt():
    stmts = parse_func_body("return 0;")
    assert len(stmts) == 1
    assert isinstance(stmts[0], cc.Return)
    assert isinstance(stmts[0].expr, cc.Num)


def test_var_decl_with_init():
    stmts = parse_func_body("int x = 5;")
    assert len(stmts) == 1
    d = stmts[0]
    assert isinstance(d, cc.VarDecl)
    assert len(d.decls) == 1
    name, stype, arr_size, init = d.decls[0]
    assert name == "x"
    assert stype is None  # int, not struct
    assert arr_size is None
    assert isinstance(init, cc.Num) and init.value == 5


def test_var_decl_no_init():
    stmts = parse_func_body("int x;")
    d = stmts[0]
    name, _, _, init = d.decls[0]
    assert name == "x"
    assert init is None


def test_multiple_var_decl():
    stmts = parse_func_body("int a, b;")
    d = stmts[0]
    assert isinstance(d, cc.VarDecl)
    assert len(d.decls) == 2
    assert d.decls[0][0] == "a"
    assert d.decls[1][0] == "b"


def test_array_decl():
    stmts = parse_func_body("int arr[5];")
    d = stmts[0]
    name, stype, arr_size, init = d.decls[0]
    assert name == "arr"
    assert arr_size == 5


def test_if_no_else():
    stmts = parse_func_body("if (1) { return 0; }")
    s = stmts[0]
    assert isinstance(s, cc.If)
    assert isinstance(s.cond, cc.Num)
    assert len(s.then_blk.stmts) == 1
    assert s.else_blk is None


def test_if_else():
    stmts = parse_func_body("if (x) { return 1; } else { return 0; }")
    s = stmts[0]
    assert isinstance(s, cc.If)
    assert s.else_blk is not None
    assert len(s.else_blk.stmts) == 1


def test_while():
    stmts = parse_func_body("while (x) { x = 0; }")
    s = stmts[0]
    assert isinstance(s, cc.While)
    assert isinstance(s.cond, cc.Var)
    assert len(s.body.stmts) == 1


def test_for_full():
    stmts = parse_func_body("for (int i = 0; i < 10; i = i + 1) { x = i; }")
    s = stmts[0]
    assert isinstance(s, cc.For)
    assert isinstance(s.init, cc.VarDecl)
    assert isinstance(s.cond, cc.Binary) and s.cond.op == "<"
    assert isinstance(s.post, cc.Assign)
    assert len(s.body.stmts) == 1


def test_for_empty_init():
    stmts = parse_func_body("for (; i < 10; i = i + 1) { x = i; }")
    s = stmts[0]
    assert isinstance(s, cc.For)
    assert s.init is None


def test_break_continue():
    stmts = parse_func_body("break; continue;")
    assert isinstance(stmts[0], cc.Break)
    assert isinstance(stmts[1], cc.Continue)


def test_expr_stmt():
    stmts = parse_func_body("foo();")
    s = stmts[0]
    assert isinstance(s, cc.ExprStmt)
    assert isinstance(s.expr, cc.Call)


# ==================== Function / program tests ====================

def test_func_no_params():
    prog = parse_program("int main() { return 0; }")
    assert len(prog.funcs) == 1
    f = prog.funcs[0]
    assert f.name == "main"
    assert f.params == []


def test_func_with_params():
    prog = parse_program("int add(int a, int b) { return a; }")
    f = prog.funcs[0]
    assert f.name == "add"
    assert f.params == ["a", "b"]


def test_multiple_funcs():
    prog = parse_program("int foo() { return 1; } int bar() { return 2; }")
    assert len(prog.funcs) == 2
    assert prog.funcs[0].name == "foo"
    assert prog.funcs[1].name == "bar"


def test_struct_def():
    prog = parse_program("""
        struct Point { int x; int y; };
        int main() { return 0; }
    """)
    assert len(prog.structs) == 1
    assert prog.structs[0].name == "Point"
    assert prog.structs[0].fields == ["x", "y"]


def test_struct_dot_access():
    prog = parse_program("""
        struct Point { int x; int y; };
        int main() {
            struct Point p;
            return p.x;
        }
    """)
    ret = prog.funcs[0].body.stmts[1]
    assert isinstance(ret, cc.Return)
    e = ret.expr
    assert isinstance(e, cc.FieldAccess)
    assert e.field == "x"
    assert e.struct_type == "Point"


def test_struct_arrow_access():
    prog = parse_program("""
        struct Point { int x; int y; };
        int foo(struct Point *p) {
            return p->x;
        }
    """)
    ret = prog.funcs[0].body.stmts[0]
    assert isinstance(ret, cc.Return)
    e = ret.expr
    assert isinstance(e, cc.ArrowAccess)
    assert e.field == "x"
    assert e.struct_type == "Point"


# ==================== Error tests ====================

def test_unexpected_token():
    with pytest.raises(SyntaxError):
        parse_program("int main( { return 0; }")  # missing ')'
