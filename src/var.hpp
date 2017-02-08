// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#pragma once

#include <ostream>
#include <cinttypes>

#include "op.hpp"


enum class var_type {
	integer,
	floating,
	operation,
};


class var {
private:
	var_type type;

	union {
		int64_t i;
		double f;
		op o;
	} value;

public:
	var();
	var(int i);
	var(int64_t i);
	var(double f);
	var(const op o);

	var_type get_type() const;

	var operator=(const int64_t &rhs);
	var operator=(const double &rhs);
	var operator=(const op &rhs);

	// @TODO @DECISION Maybe add type checking for these methods
	int64_t as_int() const;
	double as_float() const;
	op as_op() const;
};


// Prints the proper value based on the type
std::ostream &operator<<(std::ostream &os, var const &v);
