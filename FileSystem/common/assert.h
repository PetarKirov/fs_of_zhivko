#pragma once

#include <string>
#include <iostream>

// Find a __func__ macro that works:
#ifndef FUNCTION_NAME
#ifdef __PRETTY_FUNCTION__
#define FUNCTION_NAME __PRETTY_FUNCTION__
#endif
#endif

#ifndef FUNCTION_NAME
#ifdef __FUNCTION__
#define FUNCTION_NAME __FUNCTION__
#endif
#endif

#ifndef FUNCTION_NAME
#ifdef __func__
#define FUNCTION_NAME __func__
#endif
#endif

#ifndef FUNCTION_NAME
#define FUNCTION_NAME ""
#endif

#define FS_ASSERT( expr, msg ) fs_assert(expr, msg, FUNCTION_NAME);


inline void fs_assert(bool expr, std::wstring msg, const char* func)
{
	if (!expr)
	{
		std::wcout << std::endl << msg <<" "<< func << std::endl;
		exit(1);
	}
}