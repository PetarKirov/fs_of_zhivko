#pragma once

#include <iostream>
#include <string>

#include "../common/string_helpers.h"
#include "../interface/file_system.h"

bool ask_user(std::wstring msg);

void print_help();

void main_loop(FileSystem& fs);

void execute_command(String input, bool& is_exit, FileSystem& fs);

bool eat_command(String &input, const CharType *command);

String eat_arg(String &input);
