#ifndef UTILS_STRING_HEADER_INCLUDED
#define UTILS_STRING_HEADER_INCLUDED

#include <string>
#include <cctype>

namespace utils
{
	int istrcmp(const char* a, const char* b) noexcept
	{
		for (;; a++, b++)
		{
			int d = tolower(*a) - tolower(*b);
			if (d != 0 || !*a)
				return d;
		}
		return 0;
	}

	std::string& ltrim(std::string& string, const char* characters)
	{
		string.erase(0, string.find_first_not_of(characters));
		return string;
	}

	std::string& rtrim(std::string& string, const char* characters)
	{
		string.erase(string.find_last_not_of(characters) + 1);
		return string;
	}

	std::string& trim(std::string& string, const char* characters)
	{
		return ltrim(rtrim(string, characters), characters);
	}

	std::string ltrim_copy(std::string string, const char* characters)
	{
		return ltrim(string, characters);
	}

	std::string rtrim_copy(std::string string, const char* characters)
	{
		return rtrim(string, characters);
	}

	std::string trim_copy(std::string string, const char* characters)
	{
		return trim(string, characters);
	}
} // namespace utils

#endif // UTILS_STRING_HEADER_INCLUDED
