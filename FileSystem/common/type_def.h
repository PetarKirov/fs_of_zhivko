#pragma once

using byte = unsigned char;
using LenSmall = byte;
using Len = unsigned long long;
using SLen = signed long long;

// used to point to a place in the whole file system
using Address = unsigned long long;

// used to point to an index inside the nodes
using NodeIndex = unsigned long long;

// used to point to an index inside the data blocks
using DataBlockIndex = unsigned long long;
