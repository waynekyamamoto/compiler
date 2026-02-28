#!/bin/bash
# Run GCC C torture tests against our compiler
# Usage: ./run_torture.sh [compiler] [test_dir]

CC="${1:-./gen1}"
TESTDIR="${2:-gcc-torture}"
OUTDIR="/tmp/cc_torture_results"
rm -rf "$OUTDIR"
mkdir -p "$OUTDIR"

PASS=0
FAIL_COMPILE=0
FAIL_RUN=0
SKIP=0
TOTAL=0

# Features we know we can't handle — skip these tests
should_skip() {
    local f="$1"
    grep -qE '#include.*\.c"|__asm__|__asm\b|\basm\b|_Complex|__complex|dg-additional-options.*-std=(gnu|c)89|dg-require-effective-target|dg-skip-if|__attribute__.*packed|__attribute__.*aligned|#include.*<signal\.h>|#include.*<setjmp\.h>|#include.*<fcntl\.h>|#include.*<sys/stat\.h>|#include.*<sys/mman\.h>|wchar_t|L"[^"]*"' "$f" && return 0
    return 1
}

FAIL_LIST="$OUTDIR/failures.txt"
SKIP_LIST="$OUTDIR/skipped.txt"
PASS_LIST="$OUTDIR/passed.txt"
COMPILE_FAIL_LIST="$OUTDIR/compile_failures.txt"
> "$FAIL_LIST"
> "$SKIP_LIST"
> "$PASS_LIST"
> "$COMPILE_FAIL_LIST"

echo "=== GCC C Torture Test Run ==="
echo "Compiler: $CC"
echo "Test dir: $TESTDIR"
echo ""

for f in "$TESTDIR"/*.c; do
    name=$(basename "$f" .c)
    TOTAL=$((TOTAL + 1))

    if should_skip "$f"; then
        SKIP=$((SKIP + 1))
        echo "$name" >> "$SKIP_LIST"
        continue
    fi

    # Compile
    if ! $CC "$f" -o "$OUTDIR/$name" > "$OUTDIR/${name}.compile.log" 2>&1; then
        FAIL_COMPILE=$((FAIL_COMPILE + 1))
        echo "$name" >> "$COMPILE_FAIL_LIST"
        continue
    fi

    # Run with perl timeout (portable to macOS)
    rc=$(perl -e '
        my $pid = fork();
        if ($pid == 0) {
            exec @ARGV;
            exit(127);
        }
        my $deadline = time() + 5;
        while (1) {
            my $r = waitpid($pid, 1);  # WNOHANG
            if ($r > 0) { exit($? >> 8); }
            if (time() >= $deadline) { kill 9, $pid; waitpid($pid, 0); exit(124); }
            select(undef,undef,undef,0.05);
        }
    ' "$OUTDIR/$name" 2>/dev/null; echo $?)

    if [ "$rc" -eq 0 ]; then
        PASS=$((PASS + 1))
        echo "$name" >> "$PASS_LIST"
    else
        FAIL_RUN=$((FAIL_RUN + 1))
        echo "$name (exit=$rc)" >> "$FAIL_LIST"
    fi

    if [ $((TOTAL % 200)) -eq 0 ]; then
        echo "... $TOTAL/$( ls "$TESTDIR"/*.c | wc -l | tr -d ' ') (pass=$PASS compile_fail=$FAIL_COMPILE run_fail=$FAIL_RUN skip=$SKIP)"
    fi
done

echo ""
echo "=== Results ==="
echo "Total:        $TOTAL"
echo "Passed:       $PASS"
echo "Compile fail: $FAIL_COMPILE"
echo "Run fail:     $FAIL_RUN"
echo "Skipped:      $SKIP"
echo ""
ATTEMPTED=$((TOTAL - SKIP))
if [ $ATTEMPTED -gt 0 ]; then
    PCT=$((PASS * 100 / ATTEMPTED))
    echo "Pass rate:    $PASS / $ATTEMPTED attempted ($PCT%)"
fi
echo ""
echo "Details in $OUTDIR/"
echo "  passed.txt, failures.txt, compile_failures.txt, skipped.txt"
