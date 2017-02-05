#pragma once

#include <fstream>
#include <string>

#include "vm_types.hpp"


Code parse(std::ifstream&, std::string&);
