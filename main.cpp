#include <iostream>
#include <string>
#include <fstream>

#include "args.hpp"

#include "error.hpp"
#include "vm_types.hpp"


#ifndef VERSION
#define VERSION "undef"
#endif


int main(int argc, char **argv)
{
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


		if (std::string("c") == argv[1]) {
			// This is a compilation invocation

			// Parse possible compiler flags
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

			// auto code = parse(file, file_path);

			if (dtvm_args::parse_and_print) {
				// @TODO Add a printer
				std::cout << Error() << "Cannot print parsed code" << std::endl;
				return 0;
			}

			// @TODO Add a compiler
			std::cout << Error() << "Compilation not yet implemented" << std::endl;
		} else {
			// This is a VM invocation

			// Parse possible VM flags
			for (int i = 2; i < argc; i++) {
				std::string arg(argv[i]);

				if (arg == "-no-ansi-color-codes" || arg == "-no-acc")
					dtvm_args::no_ansi_color_codes = true;
				else
					std::cout << Warn() << "Unknown option '" << argv[i] << "'\n";

			}

			// Attempt to open file
			std::string file_path(argv[1]);
			std::ifstream file(file_path, std::ios::in | std::ios::binary);
			if (!file.is_open()) {
				std::cerr << Error() << "Could not open file '" << file_path << "'" << std::endl;
				return 1;
			}

			// @TODO: Add the VM
			std::cout << Error() << "The VM is not yet implemented" << std::endl;
		}
	}

	return 0;
}
