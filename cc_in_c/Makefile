CC = clang
CFLAGS = -Wall -Wextra -std=c11 -g
SRCS = main.c util.c lexer.c ast.c parser.c codegen.c
OBJS = $(SRCS:.c=.o)
TARGET = cc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

test: $(TARGET)
	./cc ../hello.c -o hello_test && ./hello_test
	./cc ../hanoi.c -o hanoi_test && ./hanoi_test
	./cc ../ptr_test.c -o ptr_test_out && ./ptr_test_out
	rm -f hello_test hanoi_test ptr_test_out ../hello.s ../hanoi.s ../ptr_test.s ../hello.o ../hanoi.o ../ptr_test.o

test-new: $(TARGET)
	@for n in 1 2 3 4 5; do \
		echo "=== test_batch$$n ==="; \
		./cc tests/test_batch$$n.c -o tests/test_batch$${n}_out && ./tests/test_batch$${n}_out || exit 1; \
	done
	@rm -f tests/test_batch*_out tests/test_batch*.s tests/test_batch*.o
	@echo "All batch tests passed."

test-selfhost: $(TARGET)
	./cc selfhost.c -o gen1
	@for n in 1 2 3 4 5; do \
		echo "=== test_batch$$n (selfhost) ==="; \
		./gen1 tests/test_batch$$n.c -o /tmp/test_batch$${n}_out && /tmp/test_batch$${n}_out || exit 1; \
	done
	@rm -f gen1 /tmp/test_batch*_out
	@echo "All selfhost batch tests passed."

test-all: test test-new test-selfhost

.PHONY: all clean test test-new test-selfhost test-all
