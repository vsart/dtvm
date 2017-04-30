// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#include "code.hpp"

#include "error.hpp"
#include "args.hpp"


// Empty constructor
Code::Code()
	: code(std::vector<var>()), data(std::vector<std::string>()), entry_point(-1)
{};


// Append an instruction to the code
void Code::push_op(op o)
{
	code.push_back(var(o));
}


// Append an integer to the code
void Code::push_int(int64_t i)
{
	code.push_back(var(i));
}


// Append a floating point value to the code
void Code::push_float(double f)
{
	code.push_back(var(f));
}


// Add a shortcut to access the data member
var& Code::operator[](int idx)
{
	return code[idx];
}
var Code::operator[](int idx) const
{
	return code[idx];
}


// Add a shortcut to get data size
size_t Code::size() const
{
	return code.size();
}


int display_line(std::ostream& o, const Code& c, int it)
{
	switch (c[it].as_op()) {
	case op::halt:
		o << c[it].as_op();
		it++;
		break;

	case op::noop:
		o << c[it].as_op();
		it++;
		break;

	case op::mov:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::push:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::pop:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::inc:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::dec:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::add:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::sub:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::mul:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::div:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::mod:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::cil:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::cfl:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_float() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::ods:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::ofv:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::onl:
		o << c[it].as_op();
		it++;
		break;

	case op::iiv:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::ifv:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::ipf:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::cmp:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::cmpz:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::jmp:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::jgt:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::jeq:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::jlt:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::call:
		o << c[it].as_op() << '\t';
		it++;
		o << c[it].as_int();
		it++;
		break;

	case op::ret:
		o << c[it].as_op();
		it++;
		break;
	}

	return it;
}


// Pretty prints the code to stdout
std::ostream &operator<<(std::ostream &o, const Code &c)
{
	size_t it = 0;

	if (dtvm_args::show_data) {
		o << "SECTION data\n" << std::endl;
		for (size_t i = 0; i < c.data.size(); i++)
			o << i << ":\n" << c.data[i] << std::endl;

		o << "\nSECTION code" << std::endl;
	}

	while (true) {
		if (it >= c.size()) {
			o << std::endl;
			return o;
		}

		o << '\n' << it << ":\t";

		if (c[it].get_type() != var_type::operation) {
			std::cerr << Error() << "Tried to display a non-op as op at " << it << std::endl;
		}

		it = display_line(o, c, it);
	}
}
