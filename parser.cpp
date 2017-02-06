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


std::tuple<double, bool> get_float(std::stringstream &ss, const std::string &sn, const int &ln) {
	double float_token;
	ss >> float_token;
	if (ss.fail()) {
		std::cerr << Error() << "Invalid register literal in " << sn << '.' << ln << std::endl;
		return std::make_tuple(0., true);
	}
	return std::make_tuple(float_token, false);
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


bool parse_reg_reg(std::stringstream &ss, const std::string &sn, const int &ln, Code &c)
{
	auto tmp1 = get_reg(ss, sn, ln);
	if (std::get<1>(tmp1))
		return true;
	c.push_int(std::get<0>(tmp1));

	auto tmp2 = get_reg(ss, sn, ln);
	if (std::get<1>(tmp2))
		return true;
	c.push_int(std::get<0>(tmp2));

	if (check_empty(ss, sn, ln))
		return true;

	return false;
}


bool parse_int_reg(std::stringstream &ss, const std::string &sn, const int &ln, Code &c)
{
	auto tmp1 = get_int(ss, sn, ln);
	if (std::get<1>(tmp1))
		return true;
	c.push_int(std::get<0>(tmp1));

	auto tmp2 = get_reg(ss, sn, ln);
	if (std::get<1>(tmp2))
		return true;
	c.push_int(std::get<0>(tmp2));

	if (check_empty(ss, sn, ln))
		return true;

	return false;
}


bool parse_flt_reg(std::stringstream &ss, const std::string &sn, const int &ln, Code &c)
{
	auto tmp1 = get_float(ss, sn, ln);
	if (std::get<1>(tmp1))
		return true;
	c.push_float(std::get<0>(tmp1));

	auto tmp2 = get_reg(ss, sn, ln);
	if (std::get<1>(tmp2))
		return true;
	c.push_int(std::get<0>(tmp2));

	if (check_empty(ss, sn, ln))
		return true;

	return false;
}


bool parse_reg(std::stringstream &ss, const std::string &sn, const int &ln, Code &c)
{
	auto tmp1 = get_reg(ss, sn, ln);
	if (std::get<1>(tmp1))
		return true;
	c.push_int(std::get<0>(tmp1));

	if (check_empty(ss, sn, ln))
		return true;

	return false;
}


bool parse_lab(std::stringstream &ss ,const std::string &sn, const int &ln, Code &c, std::map<int64_t, std::string> &m)
{
	std::string token;
	ss >> token;
	m[c.curr_index] = token;

	// Add a filler
	c.push_int(-1);

	if (check_empty(ss, sn, ln))
		return true;
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
