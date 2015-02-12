#pragma once

#include "slice.h"

bool space_in_front(String str);
bool space_in_back(String str);

void trim_space_ref(String &str);

String skip_space(String str);
void skip_space_ref(String &str);

String skip_string(String str, const CharType *to_skip);
void skip_string_ref(String &str, const CharType *to_skip);

bool starts_with(String haystack, const CharType* needle);
bool starts_with(Slice<const char> haystack, const char* needle);