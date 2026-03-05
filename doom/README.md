# Doom Compilation

Doom (doomgeneric port) compiled by the self-hosting C compiler.

## Source

Based on [doomgeneric](https://github.com/ozkl/doomgeneric), a portable Doom port.

To get the original source:
```bash
git clone https://github.com/ozkl/doomgeneric.git
```

## Files

- `doom_pp4.c` — Preprocessed and modified doomgeneric source, ready for our compiler
- `doom_main4.c` — Custom SDL2 backend (254 lines)

## WAD File

You need `doom1.wad` (the shareware Doom WAD) to run. It is not included in this repo.
Download it from https://doomwiki.org/wiki/DOOM1.WAD and place it in this directory.

## Changes from original doomgeneric

`doom_pp4.c` is a preprocessed single-file version of doomgeneric with the following modifications to work with our compiler:

1. **All `int`/`short` struct fields → `long`**: Our compiler uses 8-byte slots for all values. Struct fields like `int health`, `short floorpic`, `fixed_t` etc. are changed to `long` so field offsets are correct.

2. **`typedef int fixed_t` → `typedef long fixed_t`**: Same reason — all values are 8 bytes.

3. **`typedef unsigned angle_t` → `typedef unsigned long angle_t`**: 8-byte values.

4. **2D arrays flattened**: e.g. `gammatable[5][256]` → `gammatable[1280]`. Our compiler has limited 2D array support.

5. **Packed binary helper functions added** (`pk_u8`, `pk_i16`, `pk_u16`, `pk_i32`): WAD file data uses real C sizes (short=2, int=4) but our compiler's structs use 8 bytes per field. These helpers read packed binary data at correct byte offsets.

6. **Patch accessor macros** (`PATCH_W`, `PATCH_H`, `PATCH_LO`, `PATCH_TO`, `PATCH_COLOFS`): Read patch_t header fields from packed binary data.

7. **Sound channel ABI bridge**: Sound mixing uses accessor functions (`snd_ch_set`, `snd_ch_clear`, etc.) implemented in `doom_main4.c` (compiled with clang) to bridge the ABI gap between our compiler's 8-byte fields and real C struct layout.

8. **Float literals precomputed**: Our compiler doesn't have float codegen yet. Float constants are replaced with precomputed integer/long equivalents.

9. **Runtime initializers for `&array[N]`**: Our compiler doesn't support `&array[N]` as a global initializer. `finecosine`, `mousebuttons`, `joybuttons` are initialized at runtime instead.

## Building

From the repo root:

```bash
make doom
./doom_gen1
```

Or manually:

```bash
./gen1 doom/doom_pp4.c -o doom_gen1
clang -o doom_gen1 doom/doom_pp4.s doom/doom_main4.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2
./doom_gen1
```
