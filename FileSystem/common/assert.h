#pragma once

#include <string>
#include <iostream>
//
//#ifndef FUNCTION_NAME
//#ifdef __PRETTY_FUNCTION__
//#define FUNCTION_NAME __PRETTY_FUNCTION__
//#elif __FUNCTION__
//#define FUNCTION_NAME __FUNCTION__
//#elif __func__
//#define FUNCTION_NAME __func__
//#else
//#define FUNCTION_NAME ""
//#endif
//#endif



inline void fs_assert(bool expr, std::wstring msg, const char* func)
{
	if (!expr)
	{
		std::wcout << std::endl << msg <<" "<< func << std::endl;
		exit(1);
	}
}