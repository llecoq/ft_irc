#include "utilsExecution.hpp"

std::string erase_space_begin(std::string const &buf) {
	std::string copy = buf;

	int i = 0;
	std::string::const_iterator it = copy.begin();
	if (*it == ' ') {
		while (*it == ' ') {
			++it;
			++i;
		}
		copy.erase(0, i);
	}
	return copy;
}

std::string get_first_word(std::string const &buf) {
	std::string copy = erase_space_begin(buf);
	std::string first_word;
	first_word.append(copy, copy.find_first_of(" "));
	return first_word;
}

std::vector<std::string> split(std::string const &buf) {

	std::vector<std::string> vec;
	size_t start;
	size_t end = 0;

	while ((start = buf.find_first_not_of(" ", end)) != std::string::npos) { // size_t npos -> end of string
		end = buf.find(" ", start);
		vec.push_back(buf.substr(start, end - start));
	}
	return vec;
}
