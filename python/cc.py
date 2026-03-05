#!/usr/bin/env python3
from __future__ import annotations

import re
import sys
import subprocess
from dataclasses import dataclass
from pathlib import Path
from typing import List, Optional, Dict, Tuple

# ----------------------------
# Lexer
# ----------------------------

KEYWORDS = {"int", "return", "if", "else", "while", "for", "break", "continue", "struct"}

TOKEN_SPEC = [
    ("NUMBER",   r"\d+"),
    ("ID",       r"[A-Za-z_]\w*"),
    ("STRING",   r"\"(?:\\.|[^\"\\])*\""),
    ("OP",       r"->|==|!=|<=|>=|\&\&|\|\||[+\-*/%<>=!&.;,(){}\[\]]"),
    ("SKIP",     r"[ \t\r\n]+"),
    ("MISMATCH", r"."),
]

TOKEN_RE = re.compile("|".join(f"(?P<{name}>{pat})" for name, pat in TOKEN_SPEC), re.DOTALL)

@dataclass
class Tok:
    kind: str
    value: str
    pos: int

def lex(src: str) -> List[Tok]:
    src = re.sub(r"//.*?$", "", src, flags=re.MULTILINE)
    src = re.sub(r"/\*.*?\*/", "", src, flags=re.DOTALL)

    toks: List[Tok] = []
    for m in TOKEN_RE.finditer(src):
        kind = m.lastgroup
        val = m.group()
        pos = m.start()
        if kind == "SKIP":
            continue
        if kind == "ID" and val in KEYWORDS:
            toks.append(Tok("KW", val, pos))
        elif kind == "MISMATCH":
            raise SyntaxError(f"Unexpected character {val!r} at {pos}")
        else:
            toks.append(Tok(kind, val, pos))
    toks.append(Tok("EOF", "", len(src)))
    return toks


# ----------------------------
# AST
# ----------------------------

@dataclass
class StructDef:
    name: str
    fields: List[str]

@dataclass
class Program:
    structs: List[StructDef]
    funcs: List["FuncDef"]

@dataclass
class FuncDef:
    name: str
    params: List[str]
    body: "Block"

@dataclass
class Block:
    stmts: List["Stmt"]

class Stmt: pass

@dataclass
class Return(Stmt):
    expr: "Expr"

@dataclass
class If(Stmt):
    cond: "Expr"
    then_blk: Block
    else_blk: Optional[Block]

@dataclass
class While(Stmt):
    cond: "Expr"
    body: Block

@dataclass
class For(Stmt):
    init: Optional["Stmt"]      # VarDecl / ExprStmt / None
    cond: Optional["Expr"]      # None => true
    post: Optional["Expr"]      # expression executed at loop end
    body: Block

@dataclass
class Break(Stmt):
    pass

@dataclass
class Continue(Stmt):
    pass

@dataclass
class ExprStmt(Stmt):
    expr: "Expr"

@dataclass
class VarDecl(Stmt):
    decls: List[Tuple[str, Optional[str], Optional[int], Optional["Expr"]]]  # (name, struct_type, array_size, init)

class Expr: pass

@dataclass
class Num(Expr):
    value: int

@dataclass
class Var(Expr):
    name: str

@dataclass
class StrLit(Expr):
    value: str  # raw contents (no quotes)

@dataclass
class Call(Expr):
    name: str
    args: List[Expr]

@dataclass
class Unary(Expr):
    op: str
    rhs: Expr

@dataclass
class Binary(Expr):
    op: str
    lhs: Expr
    rhs: Expr

@dataclass
class Index(Expr):
    base: Expr
    index: Expr

@dataclass
class FieldAccess(Expr):
    obj: Expr
    field: str
    struct_type: str

@dataclass
class ArrowAccess(Expr):
    obj: Expr
    field: str
    struct_type: str

@dataclass
class Assign(Expr):
    target: Expr   # lvalue (Var, Unary("*", ...), Index)
    rhs: Expr


# ----------------------------
# Parser (Pratt)
# ----------------------------

class Parser:
    def __init__(self, toks: List[Tok]):
        self.toks = toks
        self.i = 0
        # struct_defs: name -> [(field_name, field_struct_type, field_is_ptr)]
        self.struct_defs: Dict[str, List[Tuple[str, Optional[str], bool]]] = {}
        # local_vars: var_name -> (struct_type, is_ptr) — reset per function
        self.local_vars: Dict[str, Tuple[str, bool]] = {}

    def cur(self) -> Tok:
        return self.toks[self.i]

    def eat(self, kind: str, value: Optional[str] = None) -> Tok:
        t = self.cur()
        if t.kind != kind:
            raise SyntaxError(f"Expected {kind}, got {t.kind} at {t.pos}")
        if value is not None and t.value != value:
            raise SyntaxError(f"Expected {value!r}, got {t.value!r} at {t.pos}")
        self.i += 1
        return t

    def match(self, kind: str, value: Optional[str] = None) -> bool:
        t = self.cur()
        if t.kind != kind:
            return False
        if value is not None and t.value != value:
            return False
        return True

    def _field_struct_type(self, struct_name: str, field_name: str) -> str:
        """Look up the struct type of a field for chained access resolution."""
        if struct_name not in self.struct_defs:
            raise SyntaxError(f"Unknown struct '{struct_name}'")
        for fname, fstype, _fis_ptr in self.struct_defs[struct_name]:
            if fname == field_name:
                if fstype is not None:
                    return fstype
                raise SyntaxError(f"Field '{field_name}' of struct '{struct_name}' is not a struct type")
        raise SyntaxError(f"Struct '{struct_name}' has no field '{field_name}'")

    def parse_base_type(self) -> Optional[str]:
        """Parse 'int' or 'struct Name'. Returns struct name or None for int."""
        if self.match("KW", "int"):
            self.eat("KW", "int")
            return None
        if self.match("KW", "struct"):
            self.eat("KW", "struct")
            name = self.eat("ID").value
            return name
        raise SyntaxError(f"Expected type, got {self.cur().value!r} at {self.cur().pos}")

    def parse_struct_def(self) -> StructDef:
        """Parse 'struct Name { type field; ... };'"""
        self.eat("KW", "struct")
        name = self.eat("ID").value
        self.eat("OP", "{")
        fields: List[str] = []
        field_info: List[Tuple[str, Optional[str], bool]] = []
        while not self.match("OP", "}"):
            ftype = self.parse_base_type()
            is_ptr = False
            while self.match("OP", "*"):
                self.eat("OP", "*")
                is_ptr = True
            fname = self.eat("ID").value
            self.eat("OP", ";")
            fields.append(fname)
            field_info.append((fname, ftype, is_ptr))
        self.eat("OP", "}")
        self.eat("OP", ";")
        self.struct_defs[name] = field_info
        return StructDef(name, fields)

    def parse_program(self) -> Program:
        structs: List[StructDef] = []
        funcs: List[FuncDef] = []
        while not self.match("EOF"):
            # struct definition: struct Name { ... };
            if self.match("KW", "struct"):
                saved = self.i
                self.eat("KW", "struct")
                self.eat("ID")
                if self.match("OP", "{"):
                    self.i = saved
                    structs.append(self.parse_struct_def())
                else:
                    self.i = saved
                    funcs.append(self.parse_func())
            else:
                funcs.append(self.parse_func())
        return Program(structs, funcs)

    def parse_func(self) -> FuncDef:
        self.local_vars = {}
        self.parse_base_type()  # return type (ignored)
        while self.match("OP", "*"):
            self.eat("OP", "*")
        name = self.eat("ID").value
        self.eat("OP", "(")
        params: List[str] = []
        if not self.match("OP", ")"):
            while True:
                stype = self.parse_base_type()
                is_ptr = False
                while self.match("OP", "*"):
                    self.eat("OP", "*")
                    is_ptr = True
                pname = self.eat("ID").value
                params.append(pname)
                if stype is not None:
                    self.local_vars[pname] = (stype, is_ptr)
                if self.match("OP", ","):
                    self.eat("OP", ",")
                    continue
                break
        self.eat("OP", ")")
        body = self.parse_block()
        return FuncDef(name, params, body)

    def parse_block(self) -> Block:
        self.eat("OP", "{")
        stmts: List[Stmt] = []
        while not self.match("OP", "}"):
            stmts.append(self.parse_stmt())
        self.eat("OP", "}")
        return Block(stmts)

    def parse_stmt(self) -> Stmt:
        if self.match("KW", "return"):
            self.eat("KW", "return")
            e = self.parse_expr()
            self.eat("OP", ";")
            return Return(e)

        if self.match("KW", "if"):
            self.eat("KW", "if")
            self.eat("OP", "(")
            cond = self.parse_expr()
            self.eat("OP", ")")
            then_blk = self.parse_block()
            else_blk = None
            if self.match("KW", "else"):
                self.eat("KW", "else")
                else_blk = self.parse_block()
            return If(cond, then_blk, else_blk)

        if self.match("KW", "while"):
            self.eat("KW", "while")
            self.eat("OP", "(")
            cond = self.parse_expr()
            self.eat("OP", ")")
            body = self.parse_block()
            return While(cond, body)

        if self.match("KW", "for"):
            self.eat("KW", "for")
            self.eat("OP", "(")

            init: Optional[Stmt] = None
            if self.match("KW", "int") or self.match("KW", "struct"):
                init = self.parse_vardecl_stmt()
            elif self.match("OP", ";"):
                self.eat("OP", ";")
                init = None
            else:
                e = self.parse_expr()
                self.eat("OP", ";")
                init = ExprStmt(e)

            cond: Optional[Expr] = None
            if not self.match("OP", ";"):
                cond = self.parse_expr()
            self.eat("OP", ";")

            post: Optional[Expr] = None
            if not self.match("OP", ")"):
                post = self.parse_expr()
            self.eat("OP", ")")

            body = self.parse_block()
            return For(init, cond, post, body)

        if self.match("KW", "break"):
            self.eat("KW", "break")
            self.eat("OP", ";")
            return Break()

        if self.match("KW", "continue"):
            self.eat("KW", "continue")
            self.eat("OP", ";")
            return Continue()

        if self.match("KW", "int") or self.match("KW", "struct"):
            return self.parse_vardecl_stmt()

        e = self.parse_expr()
        self.eat("OP", ";")
        return ExprStmt(e)

    def parse_vardecl_stmt(self) -> VarDecl:
        stype = self.parse_base_type()
        decls: List[Tuple[str, Optional[str], Optional[int], Optional[Expr]]] = []
        while True:
            is_ptr = False
            while self.match("OP", "*"):
                self.eat("OP", "*")
                is_ptr = True
            name = self.eat("ID").value
            arr_size = None
            if self.match("OP", "["):
                self.eat("OP", "[")
                arr_size = int(self.eat("NUMBER").value)
                self.eat("OP", "]")
            init = None
            # struct_type in decl tuple: only for direct (non-pointer) struct variables
            decl_stype = stype if (stype is not None and not is_ptr and arr_size is None) else None
            if decl_stype is None and arr_size is None and self.match("OP", "="):
                self.eat("OP", "=")
                init = self.parse_expr()
            decls.append((name, decl_stype, arr_size, init))
            if stype is not None:
                self.local_vars[name] = (stype, is_ptr)
            if self.match("OP", ","):
                self.eat("OP", ",")
                continue
            break
        self.eat("OP", ";")
        return VarDecl(decls)

    PRECEDENCE = {
        "||": 1,
        "&&": 2,
        "==": 3, "!=": 3,
        "<": 4, "<=": 4, ">": 4, ">=": 4,
        "+": 5, "-": 5,
        "*": 6, "/": 6, "%": 6,
    }

    def parse_expr(self, min_prec: int = 0) -> Expr:
        e = self.parse_unary()

        while True:
            t = self.cur()

            if t.kind == "OP" and t.value == "=" and min_prec <= 0:
                self.eat("OP", "=")
                rhs = self.parse_expr(0)
                e = Assign(e, rhs)
                continue

            if t.kind != "OP" or t.value not in self.PRECEDENCE:
                break

            prec = self.PRECEDENCE[t.value]
            if prec < min_prec:
                break

            op = t.value
            self.eat("OP", op)
            rhs = self.parse_expr(prec + 1)
            e = Binary(op, e, rhs)

        return e

    def parse_unary(self) -> Expr:
        if self.match("OP", "-") or self.match("OP", "!") or self.match("OP", "*") or self.match("OP", "&"):
            op = self.eat("OP").value
            rhs = self.parse_unary()
            return Unary(op, rhs)
        return self.parse_primary()

    def parse_primary(self) -> Expr:
        t = self.cur()
        if t.kind == "NUMBER":
            self.eat("NUMBER")
            e = Num(int(t.value))
        elif t.kind == "STRING":
            self.eat("STRING")
            e = StrLit(t.value[1:-1])
        elif t.kind == "ID":
            name = self.eat("ID").value
            if self.match("OP", "("):
                self.eat("OP", "(")
                args: List[Expr] = []
                if not self.match("OP", ")"):
                    while True:
                        args.append(self.parse_expr())
                        if self.match("OP", ","):
                            self.eat("OP", ",")
                            continue
                        break
                self.eat("OP", ")")
                e = Call(name, args)
            else:
                e = Var(name)
        elif self.match("OP", "("):
            self.eat("OP", "(")
            e = self.parse_expr()
            self.eat("OP", ")")
        else:
            raise SyntaxError(f"Unexpected token {t.kind}:{t.value!r} at {t.pos}")
        # postfix [], ., ->
        while self.match("OP", "[") or self.match("OP", ".") or self.match("OP", "->"):
            if self.match("OP", "["):
                self.eat("OP", "[")
                idx = self.parse_expr()
                self.eat("OP", "]")
                e = Index(e, idx)
            elif self.match("OP", "."):
                self.eat("OP", ".")
                field = self.eat("ID").value
                # resolve struct type from variable
                if isinstance(e, Var) and e.name in self.local_vars:
                    st, _is_ptr = self.local_vars[e.name]
                elif isinstance(e, (FieldAccess, ArrowAccess)):
                    st = self._field_struct_type(e.struct_type, e.field)
                else:
                    raise SyntaxError(f"Cannot resolve struct type for '.' at {self.cur().pos}")
                e = FieldAccess(e, field, st)
            else:
                self.eat("OP", "->")
                field = self.eat("ID").value
                if isinstance(e, Var) and e.name in self.local_vars:
                    st, _is_ptr = self.local_vars[e.name]
                elif isinstance(e, (FieldAccess, ArrowAccess)):
                    st = self._field_struct_type(e.struct_type, e.field)
                else:
                    raise SyntaxError(f"Cannot resolve struct type for '->' at {self.cur().pos}")
                e = ArrowAccess(e, field, st)
        return e


# ----------------------------
# Codegen (macOS arm64 assembly)
# ----------------------------

class CodegenError(Exception):
    pass

def decode_c_string(lit: str) -> str:
    out = []
    i = 0
    while i < len(lit):
        c = lit[i]
        if c != "\\":
            out.append(c)
            i += 1
            continue
        i += 1
        if i >= len(lit):
            raise CodegenError("Bad escape in string literal")
        esc = lit[i]
        i += 1
        if esc == "n": out.append("\n")
        elif esc == "t": out.append("\t")
        elif esc == "r": out.append("\r")
        elif esc == "\\": out.append("\\")
        elif esc == '"': out.append('"')
        elif esc == "0": out.append("\0")
        else:
            raise CodegenError(f"Unsupported escape: \\{esc}")
    return "".join(out)

def asm_escape_string(s: str) -> str:
    s = s.replace("\\", "\\\\")
    s = s.replace('"', '\\"')
    s = s.replace("\n", "\\n")
    s = s.replace("\t", "\\t")
    s = s.replace("\r", "\\r")
    s = s.replace("\0", "\\0")
    return s

@dataclass
class FuncLayout:
    slots: Dict[str, int]    # name -> offset bytes from fp, negative offset
    arrays: Dict[str, int]   # name -> element count (absent = scalar)
    structs: Dict[str, str]  # name -> struct_type (direct struct variables only)
    stack_size: int           # aligned to 16

class Codegen:
    def __init__(self, prog: Program):
        self.prog = prog
        self.lines: List[str] = []
        self.label_id = 0
        self.string_pool: Dict[str, str] = {}
        self.loop_stack: List[Tuple[str, str]] = []  # (break_label, continue_label)
        # struct_defs: name -> [field_name, ...] for offset computation
        self.struct_defs: Dict[str, List[str]] = {}
        for sd in prog.structs:
            self.struct_defs[sd.name] = sd.fields

    def new_label(self, base: str) -> str:
        self.label_id += 1
        return f"L_{base}_{self.label_id}"

    def emit(self, s: str) -> None:
        self.lines.append(s)

    def intern_string(self, decoded: str) -> str:
        if decoded in self.string_pool:
            return self.string_pool[decoded]
        lab = f"l_.str_{len(self.string_pool)+1}"
        self.string_pool[decoded] = lab
        return lab

    def layout_func(self, f: FuncDef) -> FuncLayout:
        slots: Dict[str, int] = {}
        arrays: Dict[str, int] = {}
        structs: Dict[str, str] = {}
        offset = 0

        for p in f.params:
            offset += 8
            slots[p] = offset

        def walk_block(b: Block):
            nonlocal offset
            for st in b.stmts:
                if isinstance(st, VarDecl):
                    for (nm, stype, arr_size, _init) in st.decls:
                        if nm in slots:
                            raise CodegenError(f"Duplicate variable {nm} in {f.name}")
                        if stype is not None:
                            # direct struct variable: allocate len(fields) * 8
                            nfields = len(self.struct_defs[stype])
                            offset += nfields * 8
                            structs[nm] = stype
                        elif arr_size is not None:
                            offset += arr_size * 8
                            arrays[nm] = arr_size
                        else:
                            offset += 8
                        slots[nm] = offset
                elif isinstance(st, If):
                    walk_block(st.then_blk)
                    if st.else_blk:
                        walk_block(st.else_blk)
                elif isinstance(st, While):
                    walk_block(st.body)
                elif isinstance(st, For):
                    if st.init and isinstance(st.init, VarDecl):
                        walk_block(Block([st.init]))
                    walk_block(st.body)

        walk_block(f.body)
        stack_size = ((offset + 15) // 16) * 16
        return FuncLayout(slots, arrays, structs, stack_size)

    # ---------- NEW: lvalue/rvalue split ----------
    def gen_addr(self, e: Expr, layout: FuncLayout) -> None:
        """Generate address of an lvalue into x0."""
        if isinstance(e, Var):
            if e.name not in layout.slots:
                raise CodegenError(f"Unknown variable {e.name}")
            off = layout.slots[e.name]
            self.emit(f"\tsub\tx0, x29, #{off}")
            return
        if isinstance(e, Unary) and e.op == "*":
            # address of *e is just the value of e (the pointer itself)
            self.gen_value(e.rhs, layout)
            return
        if isinstance(e, Index):
            # address of base[idx] = base_value + idx * 8
            self.gen_value(e.base, layout)       # pointer or array-decayed address
            self.emit("\tstr\tx0, [sp, #-16]!")
            self.gen_value(e.index, layout)
            self.emit("\tlsl\tx0, x0, #3")       # idx * 8
            self.emit("\tldr\tx1, [sp], #16")
            self.emit("\tadd\tx0, x1, x0")
            return
        if isinstance(e, FieldAccess):
            # p.x => address of obj + field_offset
            self.gen_addr(e.obj, layout)
            field_idx = self.struct_defs[e.struct_type].index(e.field)
            if field_idx > 0:
                self.emit(f"\tadd\tx0, x0, #{field_idx * 8}")
            return
        if isinstance(e, ArrowAccess):
            # p->x => load pointer value + field_offset
            self.gen_value(e.obj, layout)
            field_idx = self.struct_defs[e.struct_type].index(e.field)
            if field_idx > 0:
                self.emit(f"\tadd\tx0, x0, #{field_idx * 8}")
            return
        raise CodegenError(f"Expression is not an lvalue (no address): {type(e).__name__}")

    def gen_value(self, e: Expr, layout: FuncLayout) -> None:
        """Generate value of expression into x0."""
        if isinstance(e, Num):
            self.emit(f"\tmov\tx0, #{e.value}")
            return

        if isinstance(e, Var):
            self.gen_addr(e, layout)
            if e.name not in layout.arrays and e.name not in layout.structs:
                self.emit("\tldr\tx0, [x0]")
            # else: array/struct decays to pointer — address already in x0
            return

        if isinstance(e, FieldAccess):
            self.gen_addr(e, layout)
            self.emit("\tldr\tx0, [x0]")
            return

        if isinstance(e, ArrowAccess):
            self.gen_addr(e, layout)
            self.emit("\tldr\tx0, [x0]")
            return

        if isinstance(e, Index):
            self.gen_addr(e, layout)
            self.emit("\tldr\tx0, [x0]")
            return

        if isinstance(e, Assign):
            self.gen_addr(e.target, layout)        # x0 = &target
            self.emit("\tstr\tx0, [sp, #-16]!")    # push addr
            self.gen_value(e.rhs, layout)          # x0 = rhs value
            self.emit("\tldr\tx1, [sp], #16")      # x1 = addr
            self.emit("\tstr\tx0, [x1]")           # *addr = value
            return

        if isinstance(e, StrLit):
            decoded = decode_c_string(e.value)
            lab = self.intern_string(decoded)
            self.emit(f"\tadrp\tx0, {lab}@PAGE")
            self.emit(f"\tadd\tx0, x0, {lab}@PAGEOFF")
            return

        if isinstance(e, Unary):
            if e.op == "&":
                self.gen_addr(e.rhs, layout)
                return
            if e.op == "*":
                self.gen_value(e.rhs, layout)
                self.emit("\tldr\tx0, [x0]")
                return
            self.gen_value(e.rhs, layout)
            if e.op == "-":
                self.emit("\tneg\tx0, x0")
            elif e.op == "!":
                self.emit("\tcmp\tx0, #0")
                self.emit("\tcset\tx0, eq")
            else:
                raise CodegenError(f"Unsupported unary {e.op}")
            return

        if isinstance(e, Binary):
            op = e.op

            if op in ("&&", "||"):
                end = self.new_label("sc_end")
                rhs_lab = self.new_label("sc_rhs")

                self.gen_value(e.lhs, layout)
                self.emit("\tcmp\tx0, #0")
                if op == "&&":
                    self.emit(f"\tb.ne\t{rhs_lab}")
                    self.emit("\tmov\tx0, #0")
                    self.emit(f"\tb\t{end}")
                else:
                    self.emit(f"\tb.eq\t{rhs_lab}")
                    self.emit("\tmov\tx0, #1")
                    self.emit(f"\tb\t{end}")

                self.emit(f"{rhs_lab}:")
                self.gen_value(e.rhs, layout)
                self.emit("\tcmp\tx0, #0")
                self.emit("\tcset\tx0, ne")
                self.emit(f"{end}:")
                return

            self.gen_value(e.lhs, layout)
            self.emit("\tstr\tx0, [sp, #-16]!")
            self.gen_value(e.rhs, layout)
            self.emit("\tldr\tx1, [sp], #16")

            if op == "+":
                self.emit("\tadd\tx0, x1, x0")
            elif op == "-":
                self.emit("\tsub\tx0, x1, x0")
            elif op == "*":
                self.emit("\tmul\tx0, x1, x0")
            elif op == "/":
                self.emit("\tsdiv\tx0, x1, x0")
            elif op == "%":
                self.emit("\tsdiv\tx9, x1, x0")
                self.emit("\tmsub\tx0, x9, x0, x1")
            elif op in ("==", "!=", "<", "<=", ">", ">="):
                self.emit("\tcmp\tx1, x0")
                cc = {"==":"eq","!=":"ne","<":"lt","<=":"le",">":"gt",">=":"ge"}[op]
                self.emit(f"\tcset\tx0, {cc}")
            else:
                raise CodegenError(f"Unsupported binary op {op}")
            return

        if isinstance(e, Call):
            if e.name == "printf":
                if not e.args:
                    raise CodegenError("printf requires at least 1 argument")
                if not isinstance(e.args[0], StrLit):
                    raise CodegenError("printf first argument must be a string literal in this subset")

                # Apple ARM64 ABI: variadic args go on the stack, not in regs
                n_var = len(e.args) - 1
                if n_var > 0:
                    var_space = ((n_var * 8 + 15) // 16) * 16
                    self.emit(f"\tsub\tsp, sp, #{var_space}")
                    for i, arg in enumerate(e.args[1:]):
                        self.gen_value(arg, layout)
                        self.emit(f"\tstr\tx0, [sp, #{i*8}]")

                self.gen_value(e.args[0], layout)  # format string -> x0
                self.emit("\tbl\t_printf")

                if n_var > 0:
                    self.emit(f"\tadd\tsp, sp, #{var_space}")
                return

            if len(e.args) > 8:
                raise CodegenError("Supports up to 8 call arguments")

            n = len(e.args)
            for arg in e.args:
                self.gen_value(arg, layout)
                self.emit("\tstr\tx0, [sp, #-16]!")

            for i in range(n):
                disp = (n - 1 - i) * 16
                self.emit(f"\tldr\tx{i}, [sp, #{disp}]")

            self.emit(f"\tadd\tsp, sp, #{n*16}")
            self.emit(f"\tbl\t_{e.name}")
            return

        raise CodegenError(f"Unsupported expression node: {type(e).__name__}")

    # ---------- statements ----------
    def gen_stmt(self, st: Stmt, layout: FuncLayout, ret_label: str) -> None:
        if isinstance(st, Return):
            self.gen_value(st.expr, layout)
            self.emit(f"\tb\t{ret_label}")
            return

        if isinstance(st, ExprStmt):
            self.gen_value(st.expr, layout)
            return

        if isinstance(st, VarDecl):
            for (name, stype, arr_size, init) in st.decls:
                if name not in layout.slots:
                    raise CodegenError("Internal: var missing from layout")
                if stype is not None:
                    continue  # direct struct — no scalar init
                if arr_size is not None:
                    continue  # array — no scalar init
                off = layout.slots[name]
                if init is None:
                    self.emit("\tmov\tx0, #0")
                else:
                    self.gen_value(init, layout)
                self.emit(f"\tstr\tx0, [x29, #-{off}]")
            return

        if isinstance(st, If):
            else_lab = self.new_label("else")
            end_lab = self.new_label("endif")
            self.gen_value(st.cond, layout)
            self.emit("\tcmp\tx0, #0")
            if st.else_blk is None:
                self.emit(f"\tb.eq\t{end_lab}")
                self.gen_block(st.then_blk, layout, ret_label)
                self.emit(f"{end_lab}:")
            else:
                self.emit(f"\tb.eq\t{else_lab}")
                self.gen_block(st.then_blk, layout, ret_label)
                self.emit(f"\tb\t{end_lab}")
                self.emit(f"{else_lab}:")
                self.gen_block(st.else_blk, layout, ret_label)
                self.emit(f"{end_lab}:")
            return

        if isinstance(st, While):
            start = self.new_label("while_start")
            end = self.new_label("while_end")
            self.loop_stack.append((end, start))

            self.emit(f"{start}:")
            self.gen_value(st.cond, layout)
            self.emit("\tcmp\tx0, #0")
            self.emit(f"\tb.eq\t{end}")
            self.gen_block(st.body, layout, ret_label)
            self.emit(f"\tb\t{start}")
            self.emit(f"{end}:")

            self.loop_stack.pop()
            return

        if isinstance(st, For):
            start = self.new_label("for_start")
            post_lab = self.new_label("for_post")
            end = self.new_label("for_end")

            if st.init is not None:
                self.gen_stmt(st.init, layout, ret_label)

            self.loop_stack.append((end, post_lab))

            self.emit(f"{start}:")
            if st.cond is not None:
                self.gen_value(st.cond, layout)
                self.emit("\tcmp\tx0, #0")
                self.emit(f"\tb.eq\t{end}")

            self.gen_block(st.body, layout, ret_label)

            self.emit(f"{post_lab}:")
            if st.post is not None:
                self.gen_value(st.post, layout)

            self.emit(f"\tb\t{start}")
            self.emit(f"{end}:")

            self.loop_stack.pop()
            return

        if isinstance(st, Break):
            if not self.loop_stack:
                raise CodegenError("break used outside of a loop")
            brk, _cont = self.loop_stack[-1]
            self.emit(f"\tb\t{brk}")
            return

        if isinstance(st, Continue):
            if not self.loop_stack:
                raise CodegenError("continue used outside of a loop")
            _brk, cont = self.loop_stack[-1]
            self.emit(f"\tb\t{cont}")
            return

        raise CodegenError(f"Unsupported statement node: {type(st).__name__}")

    def gen_block(self, b: Block, layout: FuncLayout, ret_label: str) -> None:
        for st in b.stmts:
            self.gen_stmt(st, layout, ret_label)

    def gen_func(self, f: FuncDef) -> None:
        layout = self.layout_func(f)
        ret_label = self.new_label("ret")

        self.emit("")
        self.emit("\t.p2align\t2")
        self.emit(f"\t.globl\t_{f.name}")
        self.emit(f"_{f.name}:")
        self.emit("\tstp\tx29, x30, [sp, #-16]!")
        self.emit("\tmov\tx29, sp")
        if layout.stack_size:
            self.emit(f"\tsub\tsp, sp, #{layout.stack_size}")

        # store params
        for idx, p in enumerate(f.params):
            off = layout.slots[p]
            self.emit(f"\tstr\tx{idx}, [x29, #-{off}]")

        self.gen_block(f.body, layout, ret_label)

        self.emit("\tmov\tw0, #0")
        self.emit(f"{ret_label}:")
        if layout.stack_size:
            self.emit(f"\tadd\tsp, sp, #{layout.stack_size}")
        self.emit("\tldp\tx29, x30, [sp], #16")
        self.emit("\tret")

    def gen(self) -> str:
        self.emit("\t.text")
        for f in self.prog.funcs:
            self.gen_func(f)

        if self.string_pool:
            self.emit("")
            self.emit("\t.section\t__TEXT,__cstring,cstring_literals")
            for s, lab in self.string_pool.items():
                self.emit(f"{lab}:")
                self.emit(f'\t.asciz\t"{asm_escape_string(s)}"')

        return "\n".join(self.lines) + "\n"


# ----------------------------
# Driver
# ----------------------------

HELP = """\
Usage:
  python3 cc.py [-o output] program.c
"""

def run(cmd: List[str]) -> None:
    try:
        subprocess.run(cmd, check=True)
    except FileNotFoundError:
        print("Missing tool:", cmd[0], file=sys.stderr)
        print("Install Xcode Command Line Tools:  xcode-select --install", file=sys.stderr)
        raise
    except subprocess.CalledProcessError as e:
        raise SystemExit(f"Command failed ({e.returncode}): {' '.join(cmd)}")

def main(argv: List[str]) -> int:
    import getopt
    try:
        opts, args = getopt.getopt(argv[1:], "o:")
    except getopt.GetoptError as e:
        print(f"cc.py: {e}", file=sys.stderr)
        print(HELP, file=sys.stderr)
        return 2

    out_path = "a.out"
    for flag, val in opts:
        if flag == "-o":
            out_path = val

    if len(args) != 1:
        print(HELP, file=sys.stderr)
        return 2

    c_path = Path(args[0])
    if not c_path.exists():
        print(f"cc.py: file not found: {c_path}", file=sys.stderr)
        return 1

    src = c_path.read_text(encoding="utf-8")

    # ignore preprocessor lines
    src = "\n".join(line for line in src.splitlines() if not line.strip().startswith("#"))

    toks = lex(src)
    prog = Parser(toks).parse_program()

    cg = Codegen(prog)
    asm = cg.gen()

    s_path = c_path.with_suffix(".s")
    s_path.write_text(asm, encoding="utf-8")

    run(["clang", str(s_path), "-o", out_path])

    print(f"Wrote {s_path} and built {out_path}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
