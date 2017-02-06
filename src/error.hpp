#pragma once

#include <ostream>


// This classes are shortcuts to pretty print "WARN" and "ERROR" labels when ANSI color codes
// aren't disabled. They could be implemented as macros instead, but using proper language
// features seemed better.
class Warn {};
std::ostream &operator<<(std::ostream &os, Warn const &);
class Error {};
std::ostream &operator<<(std::ostream &os, Error const &);
