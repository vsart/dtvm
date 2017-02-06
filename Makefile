CC = clang++
CF = -O2 -g -march=native -Wall -Wextra -Wold-style-cast -Wpedantic -Werror -std=c++1z -fno-rtti -fno-omit-frame-pointer

OBJS=args.o parser.o error.o op.o var.o code.o

all: dtvm

dtvm: main.cpp $(OBJS)
	$(CC) $(CF) -DVERSION='"0.0.1"' $^ -o $@

args.o: args.cpp args.hpp
	$(CC) $(CF) -c $< -o $@

parser.o: parser.cpp parser.hpp code.o
	$(CC) $(CF) -c $< -o $@

op.o: op.cpp op.hpp
	$(CC) $(CF) -c $< -o $@

var.o: var.cpp var.hpp op.o
	$(CC) $(CF) -c $< -o $@

code.o: code.cpp code.hpp op.o var.o
	$(CC) $(CF) -c $< -o $@

error.o: error.cpp error.hpp args.o
	$(CC) $(CF) -c $< -o $@

clean:
	rm -f *.o dtvm
