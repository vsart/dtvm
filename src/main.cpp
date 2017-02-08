// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#include <fstream>
#include <iostream>
#include <string>

#include "args.hpp"
#include "error.hpp"
#include "parser.hpp"
#include "vm.hpp"


#ifndef VERSION
#define VERSION "dev"
#endif


int main(int argc, char **argv)
{
	// @TODO: Make it possible through a flag to one day be able to generate a binary file.

	if (argc == 1) {
		// @TODO Print out proper usage information
		std::cerr << Error() << "Invalid number of arguments" << std::endl;
		return 1;
	} else {
		// Before anything, check if this is a version invocation
		if (std::string(argv[1]) == "version") {
			std::cout << "DTVM version " << VERSION << " - Copyright (C) Victhor S. Sartório\n" <<
				"Licensed under the MIT License. See distributed LICENSE file for details." <<
				std::endl;
			return 0;
		}

		// Parse possible flags
		for (int i = 2; i < argc; i++) {
			std::string arg(argv[i]);

			if (arg == "-no-ansi-color-codes" || arg == "-no-acc")
				dtvm_args::no_ansi_color_codes = true;
			else if (arg == "-parse-and-print")
				dtvm_args::parse_and_print = true;
			else if (arg == "-r8")
				dtvm_args::num_regs = 8;
			else if (arg == "-r16")
				dtvm_args::num_regs = 16;
			else if (arg == "-r32")
				dtvm_args::num_regs = 32;
			else
				std::cout << Warn() << "Unknown option '" << argv[i] << "'" << std::endl;
		}

		// Attempt to open file
		std::string file_path(argv[1]);
		std::ifstream file(file_path);
		if (!file.is_open()) {
			std::cerr << Error() << "Could not open file '" << file_path << "'" << std::endl;
			return 1;
		}

		// Parse code
		auto code = parse(file, file_path);
		if (code.size() == 0) {
			std::cerr << Error() << "Got invalid code from parser" << std::endl;
			return 1;
		}

		// If the program was called with -parse-and-print, just pretty print the parsed bytecode.
		if (dtvm_args::parse_and_print) {
			std::cout << code;
			return 0;
		}

		// Run the code in the VM
		execute(code);
	}

	return 0;
}
