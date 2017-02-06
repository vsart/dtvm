#include "vm_types.hpp"


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
	case op::ofv:
		return os << "ofv ";
	case op::onl:
		return os << "onl ";
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
	}
}


std::ostream &operator<<(std::ostream &os, var const &v)
{
	switch (v.get_type()) {
	case var_type::integer:
		return os << v.as_int();
	case var_type::floating:
		return os << v.as_float();
	case var_type::operation:
		return os << v.as_op();
	}
}
