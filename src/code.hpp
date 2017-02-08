// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#pragma once

#include <cinttypes>
#include <ostream>
#include <vector>
#include <iostream>

#include "op.hpp"
#include "var.hpp"


class Code {
private:
	std::vector<var> code;

public:
	std::vector<std::string> data;

	Code();

	void push_op(op o);
	void push_int(int64_t i);
	void push_float(double f);

	var& operator[](int idx);
	var operator[](int idx) const;

	size_t size() const;

	int entry_point;
};

std::ostream &operator<<(std::ostream &o, const Code &c);
