CC = clang

.PHONY: all gen1 bootstrap test doom clean

all: gen1

gen1: selfhost.c
	$(CC) -Wno-incompatible-pointer-types -Wno-format -Wno-implicit-function-declaration -Wno-int-conversion -Wno-shift-count-overflow -Wno-pointer-integer-compare -Wno-compare-distinct-pointer-types -Wno-pointer-type-mismatch -o gen1 selfhost.c

bootstrap: gen1
	@echo "=== Stage 1: gen1 compiles selfhost.c ==="
	./gen1 selfhost.c -o gen2
	$(CC) -o gen2 selfhost.s
	@echo "=== Stage 2: gen2 compiles selfhost.c ==="
	./gen2 selfhost.c -o gen3
	cp selfhost.s gen2_selfhost.s
	$(CC) -o gen3 selfhost.s
	@echo "=== Stage 3: gen3 compiles selfhost.c ==="
	./gen3 selfhost.c -o gen3_check
	@echo "=== Verifying SHA match ==="
	@if [ "$$(shasum gen2_selfhost.s | cut -d' ' -f1)" = "$$(shasum selfhost.s | cut -d' ' -f1)" ]; then \
		echo "Bootstrap PASSED: gen2.s matches gen3.s"; \
	else \
		echo "Bootstrap FAILED: gen2.s does NOT match gen3.s"; \
		exit 1; \
	fi
	@rm -f gen2_selfhost.s gen3_check selfhost.s

test: gen1
	@pass=0; fail=0; \
	for n in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102; do \
		if [ -f tests/test_batch$$n.c ]; then \
			if ./gen1 tests/test_batch$$n.c -o /tmp/test_batch$${n}_out 2>/dev/null && /tmp/test_batch$${n}_out 2>/dev/null; then \
				pass=$$((pass + 1)); \
			else \
				echo "FAIL: test_batch$$n"; \
				fail=$$((fail + 1)); \
			fi; \
		fi; \
	done; \
	echo "=== test_batch36 (with -D flags) ==="; \
	if ./gen1 -DTEST_VAL=42 -DFLAG tests/test_batch36.c -o /tmp/test_batch36_out 2>/dev/null && /tmp/test_batch36_out 2>/dev/null; then \
		pass=$$((pass + 1)); \
	else \
		echo "FAIL: test_batch36 (with -D)"; \
		fail=$$((fail + 1)); \
	fi; \
	rm -f /tmp/test_batch*_out; \
	echo "$$pass passed, $$fail failed"; \
	[ $$fail -eq 0 ]

doom: gen1
	./gen1 doom/doom_pp4.c -o doom_gen1
	$(CC) -o doom_gen1 doom/doom_pp4.s doom/doom_main4.c \
		-I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2
	@echo "Built doom_gen1. Run with: ./doom_gen1"

clean:
	rm -f gen1 gen2 gen3 gen2_selfhost.s selfhost.s
	rm -f doom_gen1 doom/doom_pp4.s
	rm -f /tmp/test_batch*_out
