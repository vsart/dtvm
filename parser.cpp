#include "parser.hpp"

#include <iostream>
#include <sstream>

#include "error.hpp"


Code parse(std::ifstream& src, std::string& src_name)
{
	// Rely that src is opened and at the proper point

	Code code;
	int line_num = 0;
	std::string line;

	while (std::getline(src, line)) {
		line_num++;

		if (line.empty())
			continue;

		std::stringstream line_stream(line);

		std::string token;
		line_stream >> token;

		// Check if line is a comment
		if (token[0] == ';')
			continue;

		// It must match an operation
		if (token == "halt") {
			code.push_op(op::halt);

			if (line_stream >> token) {
				std::cerr << Error() << "Expected newline but found '" << token << "' in " <<
					src_name << " at line " << line_num << std::endl;
				return Code();
			}
		} else if (token == "noop") {
			code.push_op(op::noop);

			if (line_stream >> token) {
				std::cerr << Error() << "Expected newline but found '" << token << "' in " <<
					src_name << " at line " << line_num << std::endl;
				return Code();
			}
		} else if (token == "cil") {
			code.push_op(op::cil);

			int integer_literal;
			line_stream >> integer_literal;
			if (line_stream.fail()) {
				std::cerr << Error() << "Invalid integer literal after 'cil' in " <<
					src_name << " at line " << line_num << std::endl;
				return Code();
			}
			code.push_int(integer_literal);

			// @TODO @URGENT check valid register number and push it
			// @TODO @URGENT check for newline
		} else {
			std::cerr << Error() << "Unkown instruction '" << token << "' in " << src_name <<
				" at line " << line_num << std::endl;
			return Code();
		}
	}

	return code;
}
