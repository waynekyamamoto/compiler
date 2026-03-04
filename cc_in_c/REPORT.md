# Project Report: Building a Self-Hosting C Compiler with Claude

## The Contrast

Anthropic published ["Building a C compiler with a team of parallel Claudes"](https://www.anthropic.com/engineering/building-c-compiler) in February 2026. Their project: 16 parallel Claude agents, ~$20,000 in API costs, 2 billion input tokens, ~2,000 sessions, producing 100,000 lines of Rust, over ~2 weeks, with no human writing code.

Our project is the polar opposite in philosophy: **one human + one Claude instance, pair-programming interactively, writing a single-file self-hosting C compiler in C itself, targeting ARM64 (Apple Silicon).**

## What We Built

**`selfhost.c`** — an 8,036-line single-file C compiler that:
- Compiles a large subset of C to ARM64 assembly
- **Self-hosts**: compiles itself (`cc` -> `gen1` -> `gen2` -> `gen3`, where `gen2.s == gen3.s`)
- Parses and compiles sqlite3.c (240,000 lines, 2,430 functions, 11MB of assembly)
- Has 62 test batches (4,338 lines of tests) all passing
- Implements: preprocessor, structs/unions, typedefs, enums, function pointers, bitfields, variadic functions, floating-point, computed goto, flexible array members, and much more

## Timeline & Commits

**54 commits over 9 days** (Feb 16-24, 2026):

| Phase | Dates | What Happened |
|-------|-------|---------------|
| Foundation | Feb 16 | Macros, function pointers, structs, typedefs, arrays, preprocessor (`#include`, `#ifdef`, `#if`), static locals, bitfields, designated initializers, compound literals |
| Hardening | Feb 16-17 | Function-like macros, 2D arrays, `#undef`, backslash continuation, `-D` flags, `#error` |
| sqlite3.c push | Feb 20 | Parse all 240K lines of sqlite3.c (Duff's device, local typedefs, const-qualified pointers). Compile and link it. |
| Self-hosting bootstrap | Feb 21 | Fixed double-pointer stride bug. **Achieved `gen2.s == gen3.s` for the first time.** |
| Maturation | Feb 22-23 | Struct pass-by-value/return, floating-point (IEEE 754 bit patterns), `typeof`, `__builtin_expect`, statement expressions, `__FILE__`/`__LINE__` |
| Feature sprint | Feb 24 | Binary literals, multi-dir includes, computed goto (`&&label`/`goto *expr`), flexible array members, Elvis operator (`?:`), zero-filled initializers, `sizeof(array_var)` |

## Strategy

**"Bootstrap-driven development"**: every change must pass the self-hosting bootstrap test. The compiler compiles itself three generations deep, and `gen2.s` must byte-match `gen3.s`. This is the ultimate integration test — if the compiler has a codegen bug, the next generation will produce different output.

The strategy was:
1. **Start with a multi-file "stage 0" compiler** (`cc`) written in standard C, compiled by clang
2. **Write `selfhost.c`** using only the C subset that stage 0 can compile
3. **Iteratively expand the subset**: add a feature to selfhost.c, verify it compiles through stage 0, verify the bootstrap still matches
4. **Use sqlite3.c as a stress test**: a real-world 240K-line codebase that exercises nearly every C feature
5. **Test aggressively**: 62 batch test files covering corner cases

## Tactics

The session-by-session workflow:
1. **Pick a feature** (usually motivated by what sqlite3.c or selfhost.c needs next)
2. **Read the relevant code** in selfhost.c — understand the parser, AST, and codegen
3. **Implement** — typically touching 3-5 areas: token types/enums, parser, AST construction, codegen, and layout/variable tracking
4. **Write a test** — a standalone `.c` file exercising the feature
5. **Build gen1** from the modified selfhost.c using stage 0
6. **Run the test** with gen1
7. **Bootstrap verify**: gen1 -> gen2 -> gen3, diff gen2.s gen3.s
8. **Run all 62 test batches** through gen1
9. **Commit and push**

Each feature typically takes 10-30 minutes of wall time in a Claude Code session.

## What Went Well

**The bootstrap constraint is incredibly powerful.** It catches bugs that unit tests miss. When gen2.s matches gen3.s, you know the compiler is self-consistent — every codegen path it uses to compile itself produces code that, when executed, produces identical output.

**Single-file architecture is underrated.** 8,036 lines in one file sounds scary, but it means: no build system complexity, no header file management, trivial to grep, and the compiler compiles itself in one shot. No Cargo.toml, no crate dependencies, no module system.

**Incremental human-AI pair programming works.** Unlike Anthropic's approach of fully autonomous agents, every commit in this project involved a human deciding what to work on next and an AI implementing it with immediate feedback. The human provides: strategic direction, architectural taste, "try sqlite3.c and see what breaks." The AI provides: detailed implementation, debugging tenacity, knowledge of ARM64 calling conventions.

**sqlite3.c as a benchmark** was the single best decision. It stress-tests everything: massive switch statements, Duff's device, function pointers, bitfields, 2000+ element initializer lists, every preprocessor feature. It found ~20 bugs that test cases didn't.

## What Went Wrong

**Hardcoded bounds are landmines.** The most painful bug this session: adding `ST_COMPUTED_GOTO = 13` but `gen_block` had `stmts[i]->kind > 12` hardcoded, silently filtering out the new statement kind. No error, just silent wrong behavior. This is a class of bug where the compiler "works" but produces subtly wrong code.

**The `&&` token ambiguity** was tricky. The lexer produces `&&` as a single `TK_OP` token, so parsing `&&label` (label address) required matching `"&&"` as one token, not two `"&"` tokens. Took debugging with printf traces to figure out.

**Type tracking is the fundamental limitation.** The compiler treats almost everything as 8-byte values. This works surprisingly well, but means: `sizeof(expr)` required adding a separate `lv_arrsize` tracking table, pointer arithmetic doesn't auto-scale by type size in expressions like `arr + 3`, and char operations need special-case tracking (`lay_char_name`, `cg_is_char`).

**Struct field access for arrays** was the FAM bug: `h->data[i]` where `data` is an array field generated an extra `ldr` that treated the field as a pointer to dereference, when it should have computed the address directly. Required adding `is_array` tracking through three layers: `SFieldInfo`, `SDef`, and codegen arrays.

## By The Numbers: Us vs. Anthropic

| | Anthropic's Project | Our Project |
|---|---|---|
| **Language** | Rust | C (self-hosting) |
| **Target** | x86, ARM, RISC-V | ARM64 (Apple Silicon) |
| **Lines of code** | 100,000 | 8,036 |
| **Agents** | 16 parallel | 1 human + 1 Claude |
| **Cost** | ~$20,000 | A few Claude Code sessions |
| **Duration** | ~2 weeks | 9 days |
| **Commits** | Not disclosed | 54 |
| **Tests** | GCC torture suite (99%) | 62 custom batches (4,338 lines) |
| **Can compile** | Linux kernel, PostgreSQL, FFmpeg, Redis, Doom | sqlite3.c, itself |
| **Self-hosting** | No | Yes (gen2.s == gen3.s) |
| **Human code written** | None | Collaborative |
| **Dependencies** | Rust stdlib only | libc only (via clang linker) |
| **Assembler/Linker** | Delegates to GCC | Delegates to clang |

## What's Left To Do

**Near-term** (would make the compiler more practically useful):
- Proper type tracking through expressions (enables correct pointer arithmetic like `arr + n`)
- `unsigned` comparison/arithmetic (partially done, needs more)
- Multi-file compilation (currently single-file only)
- Optimization passes (currently zero optimization — straight AST-to-assembly)

**Medium-term** (would expand what it can compile):
- Full `struct` designated initializer support (`.field = val` in nested contexts)
- K&R function definitions
- Full `const` correctness
- `volatile` semantics
- Complete `long long` / `size_t` support

**Aspirational**:
- Compile more real-world projects (maybe Lua, jq, or TCC)
- Compile a small OS kernel
- x86-64 backend (currently ARM64 only)

## The Philosophical Difference

Anthropic's project answers: **"What can AI do autonomously at scale?"** — 16 agents, $20K, zero human code, brute-force coverage of the C spec.

Our project answers: **"What can one human and one AI do together, iteratively?"** — collaborative pair programming, where the human provides taste and the AI provides velocity. The result is 12x less code, self-hosting (which theirs isn't), and cost pennies in comparison.

Both are valid. But I'd argue the self-hosting constraint is more elegant. When your compiler can compile itself and produce identical output, you've achieved something that's hard to fake. Their compiler passes GCC's torture tests by brute-forcing compatibility. Ours passes the ultimate test: *it believes in itself enough to reproduce.*

---

Sources:
- [Building a C compiler with a team of parallel Claudes](https://www.anthropic.com/engineering/building-c-compiler)
- [GitHub: anthropics/claudes-c-compiler](https://github.com/anthropics/claudes-c-compiler)
- [The Register: Claude Opus 4.6 spends $20K trying to write a C compiler](https://www.theregister.com/2026/02/09/claude_opus_46_compiler/)
