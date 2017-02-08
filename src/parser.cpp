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
bool parse_lab(std::stringstream &ss, const std::string &sn, const int &ln, Code &c,
               std::map<int64_t, std::pair<int, std::string>> &m, const std::string &cl)
{
	std::string token;
	ss >> token;

	// If it's a sublabel, expand it
	if (token[0] == '.')
		token = cl + token;

	m[c.size()] = std::pair<int, std::string>(ln, token);

	// Add a filler
	c.push_int(-1);

	if (check_empty(ss, sn, ln))
		return true;
	return false;
}


// gfc
// Gets a formatted character from the stringstream
// @arg ss - The stringstream
// @arg sn - File name for error reporting
// @arg ln - Line number for error reporting
// @ret (Character, Was there any error?)
std::pair<char, bool> gfc(std::stringstream &ss, const std::string &sn, const int &ln)
{
	char ch;
	ch = ss.get();
	if (ss.fail())
		return std::pair<char, bool>('\0', true);
	if (ch == '\\') {
		ch = ss.get();
		if (ss.fail()) {
			std::cerr << Error() << "Expected \\ expansion at " << sn << '.' << ln <<
				"but found EOL instead." << std::endl;
			return std::pair<char, bool>('\0', true);
		}
		switch (ch) {
		case 't':
			return std::pair<char, bool>('\t', false);
		case 'n':
			return std::pair<char, bool>('\n', false);
		default:
			std::cerr << Error() << "Expected valid \\ expansion at " << sn << '.' << ln <<
				"but found invalid expanding character '" << ch << "'" << std::endl;
			return std::pair<char, bool>(ch, true);
		}
	}
	return std::pair<char, bool>(ch, false);
}


// parse
// @exported
// Parses the source file into a Code object
// @arg src      - The ifstream holding the source file
// @arg src_name - The name of the source file for error reporting
// @ret - The Code object. An empty Code object is returned on error.
Code parse(std::ifstream& src, std::string& src_name)
{
	Code code;
	int line_num = 0;
	std::string line;

	std::string context_label = "";

	// Holds the strings of the labels and the index they reference
	std::map<std::string, int64_t> label_dict;
	// Holds the index the label reference appears mapping to the line number it appear and to the
	// name of the label referenced
	std::map<int64_t, std::pair<int, std::string>> label_refs;

	// Holds the name of a string and its index
	std::map<std::string, int> data_dict;

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


		// Check if it's a constant string
		if (token == "data") {
			line_stream >> token;
			// Check if string_name already exists
			auto const find = data_dict.find(token);
			if (find != data_dict.end()) {
				std::cout << Error() << "Invalid string redefinition at " << src_name << '.' <<
					line_num << std::endl;
				return Code();
			}
			data_dict[token] = code.data.size();

			// Make sure next character is a "
			char ch_token;
			line_stream >> ch_token;
			if (ch_token != '"') {
				std::cout << Error() << "Expected '\"' but found " << ch_token << " at " <<
					src_name << '.' << line_num << std::endl;
				return Code();
			}

			auto tmp = gfc(line_stream, src_name, line_num);
			std::ostringstream new_data;
			while (!tmp.second && tmp.first != '"') {
				new_data << tmp.first;
				tmp = gfc(line_stream, src_name, line_num);
			}
			if (tmp.second) {
				std::cerr << Error() << "Failed to parse string at " << src_name << '.' <<
					line_num << std::endl;
			}
			code.data.push_back(new_data.str());
			// Make sure line is empty
			if (check_empty(line_stream, src_name, line_num))
				return Code();
			continue;
		}

		// Check if line is a label
		if (token.back() == ':') {
			auto label_name = token.substr(0, token.length() - 1);
			// Check if it's a sublabel in need of expansion
			if (label_name[0] == '.') {
				// Check if it's a valid sublabel
				if (context_label.empty()) {
					std::cerr << Error() << "Sublabel without context label '" << label_name <<
						"' at " << src_name << '.' << line_num << std::endl;
					return Code();
				}
				// Expand sublabel
				label_name = context_label + label_name;
			} else {
				context_label = label_name;
			}
			// Check for label redefinitions
			auto const tmp = label_dict.find(label_name);
			if (tmp != label_dict.end()) {
				std::cout << Error() << "Invalid label redefinition at " << src_name << '.' <<
					line_num << std::endl;
				return Code();
			}
			label_dict[label_name] = code.size();
			if (label_name == dtvm_args::entry_point)
				code.entry_point = code.size();
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

		} else if (token == "inc") {
			code.push_op(op::inc);
			if (parse_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "dec") {
			code.push_op(op::dec);
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

		} else if (token == "ods") {
			code.push_op(op::ods);
			line_stream >> token;
			// Attempt to find token in data dict
			if (data_dict.find(token) == data_dict.end()) {
				std::cerr << Error() << "Undefined data label '" << token << "' at " <<
					src_name << '.' << line_num << std::endl;
				return Code();
			} else {
				code.push_int(data_dict.find(token)->second);
			}
			if (check_empty(line_stream, src_name, line_num))
				return Code();

		} else if (token == "ofv") {
			code.push_op(op::ofv);
			if (parse_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "onl") {
			code.push_op(op::onl);
			if (check_empty(line_stream, src_name, line_num))
				return Code();

		} else if (token == "iiv") {
			code.push_op(op::iiv);
			if (parse_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "ifv") {
			code.push_op(op::ifv);
			if (parse_reg(line_stream, src_name, line_num, code))
				return Code();

		} else if (token == "ipf") {
			code.push_op(op::ipf);
			if (parse_reg(line_stream, src_name, line_num, code))
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
			if (parse_lab(line_stream, src_name, line_num, code, label_refs, context_label))
				return Code();

		} else if (token == "jgt") {
			code.push_op(op::jgt);
			if (parse_lab(line_stream, src_name, line_num, code, label_refs, context_label))
				return Code();

		} else if (token == "jeq") {
			code.push_op(op::jeq);
			if (parse_lab(line_stream, src_name, line_num, code, label_refs, context_label))
				return Code();

		} else if (token == "jlt") {
			code.push_op(op::jlt);
			if (parse_lab(line_stream, src_name, line_num, code, label_refs, context_label))
				return Code();

		} else if (token  == "call") {
			code.push_op(op::call);
			if (parse_lab(line_stream, src_name, line_num, code, label_refs, context_label))
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

	if (code.entry_point < 0) {
		std::cerr << Error() << "The entry point label '" << dtvm_args::entry_point  <<
			"' was not found." << std::endl;
		return Code();
	}

	// Go thorugh label references and use the label dictionary to substitute the proper
	// 'addresses' where they were referenced.
	for (auto &ref : label_refs) {
		const auto index_to_change = ref.first;
		const auto referenced_label = ref.second.second;
		const auto find_result = label_dict.find(referenced_label);
		if (find_result == label_dict.end()) {
			std::cerr << Error() << "Unknown label '" << referenced_label << '\'' <<
				" in " << src_name << '.' << ref.second.first << std::endl;
			return Code();
		}
		const auto referenced_index = find_result->second;
		code[index_to_change] = referenced_index;
	}

	return code;
}
