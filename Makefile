CC = clang++
CF = -O2 -g -march=native -Wall -Wextra -Wold-style-cast -Wpedantic -Werror -std=c++1z -fno-rtti -fno-omit-frame-pointer

OBJS=obj/args.o obj/parser.o obj/error.o obj/op.o obj/var.o obj/code.o

all:
	@mkdir -p obj
	@make dtvm

dtvm: src/main.cpp $(OBJS)
	$(CC) $(CF) -DVERSION='"0.0.2"' $^ -o $@

obj/args.o: src/args.cpp src/args.hpp
	$(CC) $(CF) -c $< -o $@

obj/parser.o: src/parser.cpp src/parser.hpp obj/code.o
	$(CC) $(CF) -c $< -o $@

obj/op.o: src/op.cpp src/op.hpp
	$(CC) $(CF) -c $< -o $@

obj/var.o: src/var.cpp src/var.hpp obj/op.o
	$(CC) $(CF) -c $< -o $@

obj/code.o: src/code.cpp src/code.hpp obj/op.o obj/var.o
	$(CC) $(CF) -c $< -o $@

obj/error.o: src/error.cpp src/error.hpp obj/args.o
	$(CC) $(CF) -c $< -o $@

clean:
	rm -rf obj dtvm
