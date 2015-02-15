#include "string_helpers.h"

#include <cwctype>

bool space_in_front(String str)
{
	return std::iswspace(str.front()) != 0;
}

bool space_in_back(String str)
{
	return std::iswspace(str.back()) != 0;
}

void trim_space_ref(String &str)
{
	while (!str.empty() && space_in_front(str))
		str.pop_front();

	while (!str.empty() && space_in_back(str))
		str.pop_back();
}

String skip_space(String str)
{
	while (!str.empty() && space_in_front(str))
		str.pop_front();

	return str;
}

void skip_space_ref(String &str)
{
	str = skip_space(str);
}

String skip_string(String haystack, const CharType *to_skip)
{
	auto original = haystack;

	while (!haystack.empty() && *to_skip)
	{
		if (haystack.front() != *to_skip)
			return original;

		haystack.pop_front();
		to_skip++;
	}

	if (*to_skip)
		return original;

	return haystack;
}

void skip_string_ref(String haystack, const CharType *to_skip)
{
	haystack = skip_string(haystack, to_skip);
}

bool starts_with(String haystack, const CharType* needle)
{
	auto rem = skip_string(haystack, needle);

	return rem != haystack;
}

bool starts_with(Slice<const char> haystack, const char* needle)
{
	while (!haystack.empty() && *needle)
	{
		if (haystack.front() != *needle)
			return false;

		haystack.pop_front();
		needle++;
	}

	if (*needle)
		return false;

	return true;
}

void string_copy(CharType* dest, String source)
{
	for (size_t i = 0; i < source.size(); i++)
		*dest = source[i];
}
