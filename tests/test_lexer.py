import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

import cc


def toks(src):
    """Return list of (kind, value) pairs, excluding EOF."""
    return [(t.kind, t.value) for t in cc.lex(src) if t.kind != "EOF"]


# ---------- Basic tokens ----------

def test_integer_literal():
    assert toks("42") == [("NUMBER", "42")]


def test_identifier():
    assert toks("foo") == [("ID", "foo")]


def test_string_literal():
    assert toks('"hello"') == [("STRING", '"hello"')]


def test_string_with_escape():
    assert toks(r'"hello\n"') == [("STRING", r'"hello\n"')]


# ---------- Keywords ----------

def test_keywords():
    for kw in ("int", "return", "if", "else", "while", "for", "break", "continue", "struct"):
        assert toks(kw) == [("KW", kw)]


def test_keyword_prefix_is_id():
    # "integer" is not the keyword "int"
    assert toks("integer") == [("ID", "integer")]


# ---------- Operators ----------

def test_single_char_ops():
    assert toks("+ - * / %") == [
        ("OP", "+"), ("OP", "-"), ("OP", "*"), ("OP", "/"), ("OP", "%"),
    ]


def test_comparison_ops():
    assert toks("== != < <= > >=") == [
        ("OP", "=="), ("OP", "!="),
        ("OP", "<"), ("OP", "<="),
        ("OP", ">"), ("OP", ">="),
    ]


def test_logical_ops():
    assert toks("&& ||") == [("OP", "&&"), ("OP", "||")]


def test_arrow_and_dot():
    assert toks("-> .") == [("OP", "->"), ("OP", ".")]


def test_delimiters():
    assert toks("( ) { } [ ] ; ,") == [
        ("OP", "("), ("OP", ")"),
        ("OP", "{"), ("OP", "}"),
        ("OP", "["), ("OP", "]"),
        ("OP", ";"), ("OP", ","),
    ]


# ---------- Combinations ----------

def test_var_decl_tokens():
    assert toks("int x = 5;") == [
        ("KW", "int"), ("ID", "x"), ("OP", "="), ("NUMBER", "5"), ("OP", ";"),
    ]


def test_pointer_decl():
    assert toks("int *p = &x;") == [
        ("KW", "int"), ("OP", "*"), ("ID", "p"),
        ("OP", "="), ("OP", "&"), ("ID", "x"), ("OP", ";"),
    ]


def test_function_call_tokens():
    assert toks("foo(1, 2)") == [
        ("ID", "foo"), ("OP", "("),
        ("NUMBER", "1"), ("OP", ","), ("NUMBER", "2"),
        ("OP", ")"),
    ]


def test_array_access():
    assert toks("arr[0]") == [
        ("ID", "arr"), ("OP", "["), ("NUMBER", "0"), ("OP", "]"),
    ]


def test_struct_arrow():
    assert toks("p->x") == [("ID", "p"), ("OP", "->"), ("ID", "x")]


# ---------- Comments ----------

def test_line_comment_stripped():
    assert toks("x // comment\ny") == [("ID", "x"), ("ID", "y")]


def test_block_comment_stripped():
    assert toks("x /* block */ y") == [("ID", "x"), ("ID", "y")]


# ---------- Whitespace ----------

def test_whitespace_ignored():
    assert toks("  \t\n  42  \n") == [("NUMBER", "42")]


# ---------- Errors ----------

def test_mismatch_raises():
    import pytest
    with pytest.raises(SyntaxError):
        cc.lex("@")
