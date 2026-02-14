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
	rm -f hello_test hanoi_test ptr_test_out ../hello.s ../hanoi.s ../ptr_test.s

.PHONY: all clean test
