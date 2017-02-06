CC = clang++
CF = -O2 -g -march=native -Wall -Wextra -Wold-style-cast -Wpedantic -Werror -std=c++1z -fno-rtti -fno-omit-frame-pointer

OBJS=args.o parser.o vm_types.o error.o

all: dtvm

dtvm: main.cpp $(OBJS)
	$(CC) $(CF) -DVERSION='"0.0.1"' $^ -o $@

args.o: args.cpp args.hpp
	$(CC) $(CF) -c $< -o $@

parser.o: parser.cpp parser.hpp vm_types.o
	$(CC) $(CF) -c $< -o $@

vm_types.o: vm_types.cpp vm_types.hpp
	$(CC) $(CF) -c $< -o $@

error.o: error.cpp error.hpp args.o
	$(CC) $(CF) -c $< -o $@

clean:
	rm -f *.o dtvm
