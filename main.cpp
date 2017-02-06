#include <iostream>
#include <string>
#include <fstream>

#include "args.hpp"

#include "error.hpp"
#include "vm_types.hpp"

#include "parser.hpp"


#ifndef VERSION
#define VERSION "undef"
#endif


int main(int argc, char **argv)
{
	// @TODO: Make it possible through a flag to one day be able to generate
	// a binary pre-compiled file.

	if (argc == 1) {
		// @TODO Print out some usage info
		std::cerr << Error() << "Invalid number of arguments" << std::endl;
		return 1;
	} else {
		// Before anything, check if this is a version invocation
		// @TODO Add license
		if (std::string(argv[1]) == "version") {
			std::cout << "DTVM version " << VERSION << "\n" <<
				"by Victhor S. Sartório" << std::endl;
			return 0;
		}

		// Parse possible flags
		for (int i = 3; i < argc; i++) {
			std::string arg(argv[i]);

			if (arg == "-no-ansi-color-codes" || arg == "-no-acc")
				dtvm_args::no_ansi_color_codes = true;
			else if (arg == "-parse-and-print")
				dtvm_args::parse_and_print = true;
			else
				std::cout << Warn() << "Unknown option '" << argv[i] << "'\n";
		}

		// Attempt to open file
		std::string file_path(argv[2]);
		std::ifstream file(file_path);
		if (!file.is_open()) {
			std::cerr << Error() << "Could not open file '" << file_path << "'" << std::endl;
			return 1;
		}

		// Parse code
		auto code = parse(file, file_path);
		if (code.curr_index == 0) {
			std::cerr << Error() << "Got invalid code from parser" << std::endl;
			return 1;
		}

		// If the program was called with -parse-and-print, just output the bytecode
		// and stop execution.
		if (dtvm_args::parse_and_print) {
			code.display();
			return 0;
		}

		// Run the code in the VM
		std::cout << Error() << "The VM is not yet implemented" << std::endl;
	}

	return 0;
}
