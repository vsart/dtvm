#pragma once

#include <ostream>


class Warn {};
std::ostream &operator<<(std::ostream &os, Warn const &);

class Error {};
std::ostream &operator<<(std::ostream &os, Error const &);
