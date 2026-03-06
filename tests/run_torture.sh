#!/bin/bash
# Run GCC torture tests against gen1
# Usage: ./tests/run_torture.sh [gen1_path]

GEN1="${1:-./gen1}"
TORTURE_DIR="tests/gcc-torture"
OUTDIR="/tmp/torture-out"
rm -rf "$OUTDIR"
mkdir -p "$OUTDIR"

pass=0
fail_compile=0
fail_assemble=0
fail_run=0
timeout_compile=0
timeout_run=0
total=0

for src in "$TORTURE_DIR"/*.c; do
    name=$(basename "$src" .c)
    total=$((total + 1))

    # Compile with gen1 (30s timeout)
    perl -e 'alarm(30); exec @ARGV' "$GEN1" "$src" -o "$OUTDIR/$name" >"$OUTDIR/$name.log" 2>&1
    rc=$?
    if [ $rc -eq 142 ] || [ $rc -eq 137 ]; then
        timeout_compile=$((timeout_compile + 1))
        continue
    fi
    if [ $rc -ne 0 ]; then
        fail_compile=$((fail_compile + 1))
        continue
    fi

    # Find the .s file (gen1 writes it next to source or in current dir)
    sfile="${src%.c}.s"
    if [ ! -f "$sfile" ]; then
        sfile="$(basename "$src" .c).s"
    fi
    if [ ! -f "$sfile" ]; then
        fail_assemble=$((fail_assemble + 1))
        continue
    fi

    # Assemble/link with clang
    clang -o "$OUTDIR/$name" "$sfile" -lm 2>"$OUTDIR/$name.clang.log"
    if [ $? -ne 0 ]; then
        fail_assemble=$((fail_assemble + 1))
        rm -f "$sfile"
        continue
    fi
    rm -f "$sfile"

    # Run (10s timeout)
    perl -e 'alarm(10); exec @ARGV' "$OUTDIR/$name" >/dev/null 2>&1
    rc=$?
    if [ $rc -eq 142 ] || [ $rc -eq 137 ]; then
        timeout_run=$((timeout_run + 1))
        continue
    fi
    if [ $rc -ne 0 ]; then
        fail_run=$((fail_run + 1))
        echo "FAIL-RUN: $name (exit=$rc)"
        continue
    fi

    pass=$((pass + 1))
done

echo ""
echo "=== GCC Torture Test Results ==="
echo "Total:            $total"
echo "Passed:           $pass"
echo "Fail (compile):   $fail_compile"
echo "Fail (assemble):  $fail_assemble"
echo "Fail (run):       $fail_run"
echo "Timeout (compile):$timeout_compile"
echo "Timeout (run):    $timeout_run"
echo ""
echo "Pass rate: $(echo "scale=1; $pass * 100 / $total" | bc)%"
