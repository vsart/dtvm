CC = clang++
CF = -O2 -g -march=native -Wall -Wextra -Wold-style-cast -Werror -std=c++1z -fno-rtti -fno-omit-frame-pointer -stdlib=libc++

all: dtvm

dtvm: main.cpp error.hpp vm_types.hpp
	$(CC) $(CF) main.cpp $(OBJS) -o $@

clean:
	rm -f *.o dtvm
