#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>

inline std::string	lTrim(const std::string& str)
{
	std::string::size_type start = 0;
	while (start < str.size()
		&& std::isspace(static_cast<unsigned char>(str[start])))
	{
		++start;
	}
	return (str.substr(start));
}

inline std::string	rTrim(const std::string& str)
{
	if (str.empty())
		return (str);

	std::string::size_type end = str.size() - 1;
	while (end != std::string::npos
		&& std::isspace(static_cast<unsigned char>(str[end])))
	{
		if (end == 0)
			return ("");
		--end;
	}
	return (str.substr(0, end + 1));
}

inline std::string	toLower(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
					(int(*)(int)) std::tolower);
	return (result);
}

inline std::string	trim(const std::string& str)
{
	return (rTrim(lTrim(str)));
}

inline std::vector<std::string>	split(const std::string& str, const std::string& sep)
{
	std::vector<std::string>	tokens;
	size_t						start = 0;
	size_t						end = str.find(sep);

	while (end != std::string::npos)
	{
		tokens.push_back(str.substr(start, end - start));
		start = end + sep.length();
		end = str.find(sep, start);
	}
	tokens.push_back(str.substr(start));
	return (tokens);
}

inline int	stringToHex(const std::string& str)
{
	std::istringstream iss(str);
	int value;

	iss >> std::hex >> value;
	if (iss.fail() || !iss.eof())
		return (-1);
	return (value);
}

template <typename T>
inline std::string	toString(T value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

#endif //STRING_UTILS_HPP