#include <iostream>
#include <string>
#include <fstream>

#include "error.hpp"
#include "vm_types.hpp"


int main(int argc, char **argv)
{
	if (argc == 1) {
		// @TODO Print out some usage info
		std::cerr << Error() << "Invalid number of arguments" << std::endl;
		return 1;
	} else if (argc == 2) {
		// @TODO Also make it possible for this to be a version or usage invocation
		// @TODO Implement runtime
		std::cout << Error() << "Runtime not yet implemented" << std::endl;
	} else {
		// This should be a compilation invocation, which requires the second argument to be "c".
		if (std::string("c") != argv[1]) {
			std::cerr << Error() << "Expected 'c' to be the second argument but got " << argv[1] << " instead\n";
			return 1;
		}

		// Warn that optional flags are being ignored
		for (int i = 3; i < argc; i++) {
			std::cout << Warn() << "Ignoring option '" << argv[i] << "'\n";
		}

		// Attempt to open file
		std::string file_path(argv[2]);
		std::ifstream file(file_path);
		if (!file.is_open()) {
			std::cerr << Error() << "Could not open file '" << file_path << "'" << std::endl;
			return 1;
		}

		std::cout << Error() << "Compilation not yet implemented" << std::endl;
	}

	return 0;
}
