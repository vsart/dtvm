// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#include "code.hpp"

#include "error.hpp"


// Empty constructor
Code::Code()
	: data(std::vector<var>())
{};


// Append an instruction to the code
void Code::push_op(op o)
{
	data.push_back(var(o));
}


// Append an integer to the code
void Code::push_int(int64_t i)
{
	data.push_back(var(i));
}


// Append a floating point value to the code
void Code::push_float(double f)
{
	data.push_back(var(f));
}


// Add a shortcut to access the data member
var& Code::operator[](int idx)
{
	return data[idx];
}
var Code::operator[](int idx) const
{
	return data[idx];
}


// Add a shortcut to get data size
size_t Code::size() const
{
	return data.size();
}


// Pretty prints the code to stdout
std::ostream &operator<<(std::ostream &o, const Code &c)
{
	size_t it = 0;

	while (true) {
		if (it >= c.size()) {
			std::cout << std::endl;
			return o;
		}

		std::cout << '\n' << it << ":\t";

		if (c[it].get_type() != var_type::operation) {
			std::cerr << Error() << "Tried to display a non-op as op at " << it << std::endl;
		}

		switch (c[it].as_op()) {
		case op::halt:
			std::cout << c[it].as_op();
			it++;
			break;

		case op::noop:
			std::cout << c[it].as_op();
			it++;
			break;

		case op::mov:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::push:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::pop:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::add:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::sub:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::mul:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::div:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::mod:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::cil:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::cfl:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_float() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::ofv:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::onl:
			std::cout << c[it].as_op();
			it++;
			break;

		case op::cmp:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::cmpz:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::jmp:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::jgt:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::jeq:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::jlt:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::call:
			std::cout << c[it].as_op() << '\t';
			it++;
			std::cout << c[it].as_int();
			it++;
			break;

		case op::ret:
			std::cout << c[it].as_op() << '\t';
			it++;
			break;
		}
	}
}
