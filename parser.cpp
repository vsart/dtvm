#include "parser.hpp"

// @TODO Remove this debug include
#include <iostream>


Code parse(std::ifstream& src, std::string& src_name)
{
	// Rely that src is opened and at the proper point

	Code code;

	std::cout << "Reading " << src_name << "\n";

	std::string token;
	while (src >> token) {
		std::cout << "Read: " << token << "\n";
	}

	return code;
}
