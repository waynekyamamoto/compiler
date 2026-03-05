# Self-Hosting C Compiler

A self-hosting C compiler targeting ARM64 (Apple Silicon), written entirely by [Claude Code](https://claude.ai/code) without any human-written code. Every line was generated through natural language direction.

## What it does

- Compiles a large subset of C to ARM64 assembly
- **Self-hosting**: compiles its own source code with byte-identical output across generations
- **Compiles sqlite3.c**: 240,000 lines, 2,430 functions → valid ARM64 assembly
- **Runs Doom**: compiles [doomgeneric](https://github.com/ozkl/doomgeneric), 30,000+ lines of C, fully playable
- 80% pass rate on GCC torture test suite (1,300+ tests)

## Quick Start

Requires: macOS on Apple Silicon, clang (Xcode Command Line Tools)

```bash
# Build the compiler
make gen1

# Run tests
make test

# Full bootstrap verification (gen2 output == gen3 output)
make bootstrap
```

## Files

- `selfhost.c` — The compiler (~11,000 lines, single file)
- `tests/` — Test suite (99 test batches)
- `include/` — Minimal system header stubs for self-hosting
- `doom/` — Preprocessed Doom source and SDL2 backend
- `blog/` — Blog post about building this compiler
- `python/` — Historical Python prototype

## External Test Data

These large test inputs are not included in the repo. To use them:

**GCC torture tests** (~1,600 tests):
```bash
# Download from GCC source
svn export svn://gcc.gnu.org/svn/gcc/trunk/gcc/testsuite/gcc.c-torture/execute gcc-torture
```

**sqlite3.c** (amalgamation):
```bash
# Download from https://sqlite.org/download.html
curl -O https://sqlite.org/2024/sqlite-amalgamation-3450000.zip
unzip sqlite-amalgamation-3450000.zip
cp sqlite-amalgamation-3450000/sqlite3.c .
./gen1 sqlite3.c -o sqlite3
```

## Building Doom

Requires SDL2: `brew install sdl2`

You need `doom1.wad` (shareware WAD file, not included). Place it in the `doom/` directory.

```bash
make doom
./doom_gen1
```

## Blog Post

See [blog/BLOG_DRAFT.md](blog/BLOG_DRAFT.md) for the full story of building this compiler using only English.

## License

MIT
