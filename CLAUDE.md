# Self-Hosting C Compiler — Project Instructions

## Overview
Single-file self-hosting C compiler targeting ARM64 (Apple Silicon).
- **Main source**: `selfhost.c` (~11,000 lines)
- **Pipeline**: Lexer → Preprocessor → Parser (Pratt) → AST → ARM64 Codegen → clang assembler/linker
- **No IR, no optimizer** — direct AST-to-assembly generation

## Bootstrap Process
```
clang -o gen1 selfhost.c          # Stage 0: clang compiles the compiler
./gen1 selfhost.c -o selfhost     # Stage 1: compiler compiles itself
clang -o gen2 selfhost.s
./gen2 selfhost.c -o selfhost     # Stage 2: gen2 compiles itself
clang -o gen3 selfhost.s
```
**Verification**: `gen2`'s assembly output must SHA-match `gen3`'s assembly output. If they don't match, something is broken.

## Self-Hosting Constraint
The compiler's own source code can only use C features the compiler already supports. Every new feature must be implemented without using that feature. Do not break self-hosting.

## Testing Pipeline
Every change must pass this verification sequence:
1. **Test batches**: 99 test batch files in `tests/` (run with gen1)
2. **Bootstrap**: gen2.s must SHA-match gen3.s
3. **sqlite3**: `./gen1 sqlite3.c -o sqlite3` must compile and assemble
4. **Doom** (optional): `./gen1 doom/doom_pp4.c -o doom_gen1` must compile

Batch 36 needs `-DTEST_VAL=42 -DFLAG` as separate args (zsh doesn't word-split).

## Building Doom
```bash
./gen1 doom/doom_pp4.c -o doom_gen1
clang -o doom_gen1 doom/doom_pp4.s doom/doom_main4.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2
./doom_gen1
```
Float literals are precomputed (no float codegen yet). WAD file: `doom/doom1.wad`.

## Known Bugs / Limitations
- `&&` in ternary conditions only evaluates first operand — use nested if/if instead
- `&array[N]` not supported as global initializer
- All values are 8 bytes (int, pointer, char stored in 8-byte slots)
- Apple ARM64 variadic: variadic args go on stack, not registers

## Key Conventions
- `__read_byte`/`__write_byte` intrinsics for byte-level ops in self-hosting code
- `char *` pointers tracked via `lay_char_name[]` / `nlay_char` / `cg_is_char()`
- Global pointer tracking via `cg_g_is_intptr[]`
- Function pointer typedefs tracked via `td_is_funcptr[]`

## Rules
- **Never break self-hosting.** Always verify bootstrap after changes.
- **Never weaken tests.** If tests fail, fix the compiler, not the tests.
- **Don't use features you haven't implemented.** The compiler must compile itself.
- zsh heredocs escape `!` even with single-quoted delimiters — use Python to write test files containing `!=`.
