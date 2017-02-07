// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#include "code.hpp"


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
	auto it = data.begin();

	while (true) {
		if (it == data.end()) {
			std::cout << std::endl;
			return;
		}

		std::cout << std::endl;
		switch (it->as_op()) {
		case op::halt:
			std::cout << it->as_op();
			it++;
			break;

		case op::noop:
			std::cout << it->as_op();
			it++;
			break;

		case op::mov:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::push:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::pop:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::add:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::sub:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::mul:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::div:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::mod:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::cil:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::cfl:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_float() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::ofv:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::onl:
			std::cout << it->as_op();
			it++;
			break;

		case op::cmp:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::cmpz:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::jmp:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::jgt:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::jeq:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		case op::jlt:
			std::cout << it->as_op() << '\t';
			it++;
			std::cout << it->as_int();
			it++;
			break;

		default:
			// @TODO Make this an error as it shouldn't happen
			std::cout << "????";
		}
	}
}
