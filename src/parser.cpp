// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#include "parser.hpp"

#include <iostream>
#include <sstream>

#include <utility>
#include <map>

#include "args.hpp"
#include "error.hpp"


// get_int
// Tries to get an integer from the stringstream and prints out an error on failure.
// @arg ss - stringstream which the token must originate from
// @arg sn - File name for error reporting
// @arg ln - Line number for error reporting
// @ret - Second value reports true if there was an error and the first on is the integer
//        value if the second value is false.
std::pair<int64_t, bool> get_int(std::stringstream &ss, const std::string &sn, const int &ln) {
	int64_t integer_token;
	ss >> integer_token;
	if (ss.fail()) {
		std::cerr << Error() << "Invalid integer literal in " << sn << '.' << ln << std::endl;
		return std::pair<int64_t, bool>(0, true);
	}
	return std::pair<int64_t, bool>(integer_token, false);
}


// get_reg
// Tries to get an integer from the stringstream that represents a register index, and prints
// out an error on failure.
// @arg ss - stringstream which the token must originate from
// @arg sn - File name for error reporting
// @arg ln - Line number for error reporting
// @ret - Second value reports true if there was an error and the first on is the index
//        number if the second value is false.
std::pair<int64_t, bool> get_reg(std::stringstream &ss, const std::string &sn, const int &ln) {
	int64_t integer_token;
	ss >> integer_token;
	if (ss.fail()) {
		std::cerr << Error() << "Invalid register literal in " << sn << '.' << ln << std::endl;
		return std::pair<int64_t, bool>(0, true);
	}
	if (integer_token < 0 || integer_token >= dtvm_args::num_regs) {
		std::cerr << Error() << "Invalid register " << integer_token << " at " << sn << '.' <<
		ln << ". Should be within range [0," << dtvm_args::num_regs <<  ')' << std::endl;
	}
	return std::pair<int64_t, bool>(integer_token, false);
}


// get_float
// Tries to get a floating number from the stringstream that represents a register index, and
// prints out an error on failure.
// @arg ss - stringstream which the token must originate from
// @arg sn - File name for error reporting
// @arg ln - Line number for error reporting
// @ret - Second value reports true if there was an error and the first on is the floating
//        point number if the second value is false.
std::pair<double, bool> get_float(std::stringstream &ss, const std::string &sn, const int &ln) {
	double float_token;
	ss >> float_token;
	if (ss.fail()) {
		std::cerr << Error() << "Invalid register literal in " << sn << '.' << ln << std::endl;
		return std::pair<double, bool>(0., true);
	}
	return std::pair<double, bool>(float_token, false);
}


// check_empty
// Checks if the stringstream is semantically empty and prints an error otherwise.
// @arg ss - stringstream which the token must originate from
// @arg sn - File name for error reporting
// @arg ln - Line number for error reporting
// @ret - Returns true if the stringstream is not semantically empty.
bool check_empty(std::stringstream &ss, const std::string &sn, const int &ln)
{
	std::string token;
	if (ss >> token) {
		// Allow comments
		if (token[0] == ';')
			return false;

		std::cerr << Error() << "Expected newline but found '" << token << "' in " <<
			sn << '.' << ln << std::endl;
		return true;
	}
	return false;
}


// parse_reg_reg
// Modular parsing block to fetch two register tokens from the stringstream
// @arg ss - stringstream which the token must originate from
// @arg sn - File name for error reporting
// @arg ln - Line number for error reporting
// @arg c  - Code object to push the parsed values into
// @ret - Returns true if there was an error.
bool parse_reg_reg(std::stringstream &ss, const std::string &sn, const int &ln, Code &c)
{
	auto tmp1 = get_reg(ss, sn, ln);
	if (tmp1.second)
		return true;
	c.push_int(tmp1.first);

	auto tmp2 = get_reg(ss, sn, ln);
	if (tmp2.second)
		return true;
	c.push_int(tmp2.first);

	if (check_empty(ss, sn, ln))
		return true;

	return false;
}


// parse_int_reg
// Modular parsing block to fetch an integer and a register token from the stringstream
// @arg ss - stringstream which the token must originate from
// @arg sn - File name for error reporting
// @arg ln - Line number for error reporting
// @arg c  - Code object to push the parsed values into
// @ret - Returns true if there was an error.
bool parse_int_reg(std::stringstream &ss, const std::string &sn, const int &ln, Code &c)
{
	auto tmp1 = get_int(ss, sn, ln);
	if (tmp1.second)
		return true;
	c.push_int(tmp1.first);

	auto tmp2 = get_reg(ss, sn, ln);
	if (tmp2.second)
		return true;
	c.push_int(tmp2.first);

	if (check_empty(ss, sn, ln))
		return true;

	return false;
}


// parse_flt_reg
// Modular parsing block to fetch a floating point and a register token from the stringstream
// @arg ss - stringstream which the token must originate from
// @arg sn - File name for error reporting
// @arg ln - Line number for error reporting
// @arg c  - Code object to push the parsed values into
// @ret - Returns true if there was an error.
bool parse_flt_reg(std::stringstream &ss, const std::string &sn, const int &ln, Code &c)
{
	auto tmp1 = get_float(ss, sn, ln);
	if (tmp1.second)
		return true;
	c.push_float(tmp1.first);

	auto tmp2 = get_reg(ss, sn, ln);
	if (tmp2.second)
		return true;
	c.push_int(tmp2.first);

	if (check_empty(ss, sn, ln))
		return true;

	return false;
}


// parse_int_reg
// Modular parsing block to fetch a register token from the stringstream
// @arg ss - stringstream which the token must originate from
// @arg sn - File name for error reporting
// @arg ln - Line number for error reporting
// @arg c  - Code object to push the parsed values into
// @ret - Returns true if there was an error.
bool parse_reg(std::stringstream &ss, const std::string &sn, const int &ln, Code &c)
{
	auto tmp1 = get_reg(ss, sn, ln);
	if (tmp1.second)
		return true;
	c.push_int(tmp1.first);

	if (check_empty(ss, sn, ln))
		return true;

	return false;
}


// parse_lab
// Modular parsing block to fetch a label token from the stringstream
// @arg ss - stringstream which the token must originate from
// @arg sn - File name for error reporting
// @arg ln - Line number for error reporting
// @arg c  - Code object to push the parsed values into
// @arg m  - Map to store the information regarding the label reference
// @ret - Returns true if there was an error.
bool parse_lab(std::stringstream &ss ,const std::string &sn, const int &ln, Code &c,
               std::map<int64_t, std::string> &m)
{
	std::string token;
	ss >> token;
	m[c.size()] = token;

	// Add a filler
	c.push_int(-1);

	if (check_empty(ss, sn, ln))
		return true;
	return false;
}


// parse
// @exported
// Parses the source file into a Code object
// @arg src      - The ifstream holding the source file
// @arg src_name - The name of the source file for error reporting
// @ret - The Code object. An empty Code object is returned on error.
Code parse(std::ifstream& src, std::string& src_name)
{
	// Rely that src is opened and at the proper point

	Code code;
	int line_num = 0;
	std::string line;

	// Holds the strings of the labels and the index they reference
	std::map<std::string, int64_t> label_dict;
	// Holds the index label references appear and the name of the label referenced
	std::map<int64_t, std::string> label_refs;

	while (std::getline(src, line)) {
		line_num++;

		if (line.empty())
			continue;

		std::stringstream line_stream(line);

		std::string token;
		line_stream >> token;

		// Check if line is a comment
		// The other possibility of a comment is handled by `check_empty`
		if (token[0] == ';')
			continue;

		// Check if line is a label
		if (token[0] == '@') {
			auto tmp = label_dict.find(token);
			if (tmp != label_dict.end()) {
				std::cout << Error() << "Invalid label redefinition at " << src_name << '.' <<
					line_num << std::endl;
			}
			label_dict[token] = code.size();
			// Make sure line is empty after label
			if (check_empty(line_stream, src_name, line_num))
				return Code();
			continue;
		}


		// Try to match an instruction and error otherwisde

		if (token == "halt") {
			code.push_op(op::halt);
			if (check_empty(line_stream, src_name, line_num))
				return Code();

		} else if (token == "noop") {
			code.push_op(op::noop);
			if (check_empty(line_stream, src_name, line_num))
				return Code();

		} else if (token == "mov") {
			code.push_op(op::mov);
			if (parse_reg_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "push") {
			code.push_op(op::push);
			if (parse_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "pop") {
			code.push_op(op::pop);
			if (parse_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "add") {
			code.push_op(op::add);
			if (parse_reg_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "sub") {
			code.push_op(op::sub);
			if (parse_reg_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "mul") {
			code.push_op(op::mul);
			if (parse_reg_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "div") {
			code.push_op(op::div);
			if (parse_reg_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "mod") {
			code.push_op(op::mod);
			if (parse_reg_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "cil") {
			code.push_op(op::cil);
			if (parse_int_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "cfl") {
			code.push_op(op::cfl);
			if (parse_flt_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "ofv") {
			code.push_op(op::ofv);
			if (parse_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "onl") {
			code.push_op(op::onl);
			if (check_empty(line_stream, src_name, line_num))
				return Code();

		} else if (token == "cmp") {
			code.push_op(op::cmp);
			if (parse_reg_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "cmpz") {
			code.push_op(op::cmpz);
			if (parse_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "jmp") {
			code.push_op(op::jmp);
			if (parse_lab(line_stream, src_name, line_num, code, label_refs))
				return Code();

		} else if (token == "jgt") {
			code.push_op(op::jgt);
			if (parse_lab(line_stream, src_name, line_num, code, label_refs))
				return Code();

		} else if (token == "jeq") {
			code.push_op(op::jeq);
			if (parse_lab(line_stream, src_name, line_num, code, label_refs))
				return Code();

		} else if (token == "jlt") {
			code.push_op(op::jlt);
			if (parse_lab(line_stream, src_name, line_num, code, label_refs))
				return Code();

		} else if (token  == "call") {
			code.push_op(op::call);
			if (parse_lab(line_stream, src_name, line_num, code, label_refs))
				return Code();

		} else if (token == "ret") {
			code.push_op(op::ret);
			if (check_empty(line_stream, src_name, line_num))
				return Code();

		} else {
			std::cerr << Error() << "Unkown instruction '" << token << "' in " <<
			             src_name << '.' << line_num << std::endl;
			return Code();
		}
	}

	// Always make sure to push a halt at the end
	// 1. This avoids empty Code object when an empty source is given
	// 2. This makes it so a label at the end of a file points to something meaningful
	code.push_op(op::halt);

	// Go thorugh label references and use the label dictionary to substitute the proper
	// 'addresses' where they were referenced.
	for (auto &ref : label_refs) {
		const auto index_to_change = ref.first;
		const auto referenced_label = ref.second;
		const auto find_result = label_dict.find(referenced_label);
		if (find_result == label_dict.end()) {
			// @TODO Add information about where this label was used
			std::cerr << Error() << "Unknown label '" << referenced_label << '\'' << std::endl;
			return Code();
		}
		const auto referenced_index = find_result->second;
		code[index_to_change] = referenced_index;
	}

	return code;
}
