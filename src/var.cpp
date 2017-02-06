#include "var.hpp"


// Integer constructor
var::var(int64_t i)
	: type(var_type::integer)
{
	value.i = i;
}


// Floating point constructor
var::var(double f)
	: type(var_type::floating)
{
	value.f = f;
}


// Op constructor
var::var(const op o)
	: type(var_type::operation)
{
	value.o = o;
}


// Return the type it currently holds
var_type var::get_type() const
{
	return type;
}


// Implement direct integer assignment
var var::operator=(const int64_t &rhs) {
	type = var_type::integer;
	value.i = rhs;
	return *this;
}


// Implement direct floating point assignment
var var::operator=(const double &rhs) {
	type = var_type::floating;
	value.f = rhs;
	return *this;
}


// Implement direct op assignment
var var::operator=(const op &rhs) {
	type = var_type::operation;
	value.o = rhs;
	return *this;
}


// Get integer value
int var::as_int() const
{
	return value.i;
}


// Get floating point value
double var::as_float() const
{
	return value.f;
}


// Get op value
op var::as_op() const
{
	return value.o;
}


// Prints the proper value based on the type
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
