#pragma once

#include <cinttypes>
#include <ostream>
#include <vector>
#include <iostream>

#include "op.hpp"
#include "var.hpp"


class Code {
private:
	std::vector<var> data;

public:
	int curr_index;

	Code();

	void change(int at, const var &v);

	void push_op(op o);
	void push_int(int64_t i);
	void push_float(double f);

	void display() const;
};
