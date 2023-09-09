#pragma once

#include <string>
#include <sstream>

template <typename T>
inline std::string to_string(T value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}