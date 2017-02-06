#include "parser.hpp"

#include <iostream>
#include <sstream>

#include <tuple>
#include <map>

#include "error.hpp"


std::tuple<int64_t, bool> get_int(std::stringstream &ss, const std::string &sn, const int &ln) {
	int64_t integer_token;
	ss >> integer_token;
	if (ss.fail()) {
		std::cerr << Error() << "Invalid integer literal in " << sn << '.' << ln << std::endl;
		return std::make_tuple(0, true);
	}
	return std::make_tuple(integer_token, false);
}


std::tuple<int64_t, bool> get_reg(std::stringstream &ss, const std::string &sn, const int &ln) {
	// @TODO Check if integer value is actually valid
	int64_t integer_token;
	ss >> integer_token;
	if (ss.fail()) {
		std::cerr << Error() << "Invalid register literal in " << sn << '.' << ln << std::endl;
		return std::make_tuple(0, true);
	}
	return std::make_tuple(integer_token, false);
}


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


Code parse(std::ifstream& src, std::string& src_name)
{
	// Rely that src is opened and at the proper point

	Code code;
	int line_num = 0;
	std::string line;

	std::map<std::string, int64_t> label_dict;
	std::map<int64_t, std::string> label_refs;

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

		// Check if line is a label
		if (token[0] == '@') {
			// @TODO Check if label is already defined and don't allow
			// substitutions.
			label_dict[token] = code.curr_index;
			continue;
		}

		if (token == "halt") {
			code.push_op(op::halt);

			if (check_empty(line_stream, src_name, line_num))
				return Code();


		} else if (token == "noop") {
			code.push_op(op::noop);

			if (check_empty(line_stream, src_name, line_num))
				return Code();


		} else if (token == "add") {
			code.push_op(op::add);

			auto tmp1 = get_reg(line_stream, src_name, line_num);
			if (std::get<1>(tmp1))
				return Code();
			code.push_int(std::get<0>(tmp1));

			auto tmp2 = get_reg(line_stream, src_name, line_num);
			if (std::get<1>(tmp2))
				return Code();
			code.push_int(std::get<0>(tmp2));

			if (check_empty(line_stream, src_name, line_num))
				return Code();


		} else if (token == "cil") {
			code.push_op(op::cil);

			auto tmp1 = get_int(line_stream, src_name, line_num);
			if (std::get<1>(tmp1))
				return Code();
			code.push_int(std::get<0>(tmp1));

			auto tmp2 = get_reg(line_stream, src_name, line_num);
			if (std::get<1>(tmp2))
				return Code();
			code.push_int(std::get<0>(tmp2));

			if (check_empty(line_stream, src_name, line_num))
				return Code();


		} else if (token == "ofv") {
			code.push_op(op::ofv);

			auto tmp1 = get_reg(line_stream, src_name, line_num);
			if (std::get<1>(tmp1))
				return Code();
			code.push_int(std::get<0>(tmp1));

			if (check_empty(line_stream, src_name, line_num))
				return Code();


		} else if (token == "onl") {
			code.push_op(op::onl);

			if (check_empty(line_stream, src_name, line_num))
				return Code();


		} else if (token == "jmp") {
			code.push_op(op::jmp);

			line_stream >> token;
			label_refs[code.curr_index] = token;

			code.push_int(-1);

			if (check_empty(line_stream, src_name, line_num))
				return Code();


		} else if (token == "jgt") {
			code.push_op(op::jgt);

			line_stream >> token;
			label_refs[code.curr_index] = token;

			code.push_int(-1);

			if (check_empty(line_stream, src_name, line_num))
				return Code();


		} else if (token == "jeq") {
			code.push_op(op::jeq);

			line_stream >> token;
			label_refs[code.curr_index] = token;

			code.push_int(-1);

			if (check_empty(line_stream, src_name, line_num))
				return Code();


		} else if (token == "jlt") {
			code.push_op(op::jlt);

			line_stream >> token;
			label_refs[code.curr_index] = token;

			code.push_int(-1);

			if (check_empty(line_stream, src_name, line_num))
				return Code();


		} else {
			std::cerr << Error() << "Unkown instruction '" << token << "' in " <<
				src_name << '.' << line_num << std::endl;
			return Code();
		}
	}

	// Push a halt at the end
	code.push_op(op::halt);

	for (auto &ref : label_refs) {
		const auto index_to_change = ref.first;
		const auto referenced_label = ref.second;
		const auto find_result = label_dict.find(referenced_label);
		if (find_result == label_dict.end()) {
			// @TODO Add information about where this label was used
			std::cerr << Error() << "Unknown label " << referenced_label << std::endl;
			return Code();
		}
		const auto referenced_index = find_result->second;
		code.change(index_to_change, var(referenced_index));
	}

	return code;
}
