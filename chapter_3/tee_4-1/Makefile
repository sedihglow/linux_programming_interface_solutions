BIN = ./a.out
CC=gcc
CCFLAGS = -I ./ -I ../../shared/include -c -Wall -Wextra -pthread 
CCFLAGS+= -m64 -O0 -g -pedantic -std=c99
LDFLAGS = -pthread -m64

SRCS=$(wildcard ./*.c) $(wildcard ../../shared/src/*.c) 

OBJS=$(SRCS:.c=.o)

.PHONY: all
all: $(BIN)

$(BIN):$(OBJS)
						$(CC) $(OBJS) -o $@ $(LDFLAGS)
						
%.o:%.c
						$(CC) $(CCFLAGS) -o $@ -c $<

.PHONY: valgrind 
valgrind:				# check for memory leak
						$(info -- Checking For Memory Leaks --)
						make
						valgrind --leak-check=full --show-leak-kinds=all ./a.out

.PHONY: debug
debug:					# GNU debugger
						$(info -- Debugging --)
						gdb ./a.out

.PHONY: clean
clean:					# clean the directory
						$(info -- Cleaning The Directory --)
						rm -rf ./*.o ../../shared/src/*.o ./a.out
.PHONY: run
run:					# run the program as follows
						$(info -- Running Program --)
						make
						./a.out
