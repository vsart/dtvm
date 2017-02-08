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


// Add a shortcut to get data size
size_t Code::size() const
{
	return data.size();
}


// Pretty prints the code to stdout
// @TODO: Change this to ostream &operator<< method
void Code::display() const
{
	size_t it = 0;

	while (true) {
		if (it >= data.size()) {
			std::cout << std::endl;
			return;
		}

		std::cout << '\n' << it << ":\t";

		if (data[it].get_type() != var_type::operation) {
			std::cerr << Error() << "Tried to display a non-op as op at " << it << std::endl;
		}

		switch (data[it].as_op()) {
		case op::halt:
			std::cout << data[it].as_op();
			it++;
			break;

		case op::noop:
			std::cout << data[it].as_op();
			it++;
			break;

		case op::mov:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::push:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::pop:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::add:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::sub:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::mul:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::div:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::mod:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::cil:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::cfl:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_float() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::ofv:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::onl:
			std::cout << data[it].as_op();
			it++;
			break;

		case op::cmp:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::cmpz:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::jmp:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::jgt:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::jeq:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::jlt:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::call:
			std::cout << data[it].as_op() << '\t';
			it++;
			std::cout << data[it].as_int();
			it++;
			break;

		case op::ret:
			std::cout << data[it].as_op() << '\t';
			it++;
			break;
		}
	}
}
