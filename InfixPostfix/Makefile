CC = gcc
CFLAGS = -std=c99 -Wall -g

test: test.o postfix.o stack.o
	$(CC) $^ -o $@ -lm

test.o: postfix.h

postfix.o: postfix.h stack.h
