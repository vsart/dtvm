#pragma once

#include <fstream>
#include <string>

#include "code.hpp"


// parse
// @exported
// Parses the source file into a Code object
// @arg src      - The ifstream holding the source file
// @arg src_name - The name of the source file for error reporting
// @ret - The Code object. An empty Code object is returned on error.
Code parse(std::ifstream&, std::string&);
