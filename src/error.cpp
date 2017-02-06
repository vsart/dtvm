// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#include "error.hpp"

#include "args.hpp"


std::ostream &operator<<(std::ostream &os, Warn const &) {
	if (dtvm_args::no_ansi_color_codes)
		return os << "WARN: ";
	else
		return os << "\033[1;33mWARN:  \033[m";
}


std::ostream &operator<<(std::ostream &os, Error const &) {
	if (dtvm_args::no_ansi_color_codes)
		return os << "ERROR: ";
	else
		return os << "\033[1;31mERROR: \033[m";
}
