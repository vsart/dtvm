// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#include "op.hpp"


std::ostream &operator<<(std::ostream &os, op const &o)
{
	switch (o) {
	case op::halt:
		return os << "halt";
	case op::noop:
		return os << "noop";
	case op::mov:
		return os << "mov ";
	case op::push:
		return os << "push";
	case op::pop:
		return os << "pop ";
	case op::inc:
		return os << "inc ";
	case op::dec:
		return os << "dec ";
	case op::add:
		return os << "add ";
	case op::sub:
		return os << "sub ";
	case op::mul:
		return os << "mul ";
	case op::div:
		return os << "div ";
	case op::mod:
		return os << "mod ";
	case op::cil:
		return os << "cil ";
	case op::cfl:
		return os << "cfl ";
	case op::ods:
		return os << "ods ";
	case op::ofv:
		return os << "ofv ";
	case op::onl:
		return os << "onl ";
	case op::iiv:
		return os << "iiv ";
	case op::ifv:
		return os << "ifv ";
	case op::ipf:
		return os << "ipf ";
	case op::cmp:
		return os << "cmp ";
	case op::cmpz:
		return os << "cmpz";
	case op::jmp:
		return os << "jmp ";
	case op::jgt:
		return os << "jgt ";
	case op::jeq:
		return os << "jeq ";
	case op::jlt:
		return os << "jlt ";
	case op::call:
		return os << "call";
	case op::ret:
		return os << "ret";
	}
}
