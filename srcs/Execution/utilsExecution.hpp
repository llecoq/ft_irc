#ifndef UTILSEXECUTION_HPP
#define UTILSEXECUTION_HPP

#include <string>
#include <vector>

std::string erase_space_begin(std::string const &buf);
std::string get_first_word(std::string const &buf);
std::vector<std::string> split(std::string const &buf);

#endif