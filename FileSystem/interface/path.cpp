#include "path.h"

String rtrimDirSeparators(String s)
{
	return s;
}

bool isSeparator(CharType c)
{
	return c == L'/';
}

size_t lastSeparator(String path)
{
	auto i = path.size() - 1;

	while (i >= 0 && !isSeparator(path[i])) --i;

	return i;
}

String dir_name(String full_path)
{
	if (full_path.empty())
		full_path;

	return full_path.slice(0, lastSeparator(full_path));
}

String file_name(String full_path)
{
	if (full_path.empty())
		full_path;

	return full_path.slice(lastSeparator(full_path) + 1, full_path.size());
}
