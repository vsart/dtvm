// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#include "args.hpp"


bool dtvm_args::no_ansi_color_codes = false;
bool dtvm_args::parse_and_print = false;
int dtvm_args::num_regs = 16;
std::string dtvm_args::entry_point = "_start";
bool dtvm_args::debug = false;
bool dtvm_args::show_data = false;
