CC = clang++
CF = -O2 -g -march=native -Wall -Wextra -Wold-style-cast -Werror -std=c++1z -fno-rtti -fno-omit-frame-pointer -stdlib=libc++

OBJS=args.o

all: dtvm

dtvm: main.cpp $(OBJS) error.hpp vm_types.hpp
	$(CC) $(CF) -DVERSION='"0.0.1"' main.cpp $(OBJS) -o $@

args.o: args.cpp args.hpp
	$(CC) $(CF) -c $< -o $@

clean:
	rm -f *.o dtvm
