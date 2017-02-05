#pragma once

#include <ostream>


class Warn {};

std::ostream &operator<<(std::ostream &os, Warn const &) {
#ifdef _DTVM_NO_ANSI_COLORS
	return os << "WARN: ";
#else
	return os << "\033[1;33mWARN:  \033[m";
#endif
};

class Error {};

std::ostream &operator<<(std::ostream &os, Error const &) {
#ifdef _DTVM_NO_ANSI_COLORS
	return os << "ERROR: ";
#else
	return os << "\033[1;31mERROR: \033[m";
#endif
}
