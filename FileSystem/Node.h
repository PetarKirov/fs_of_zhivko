#pragma once

enum NodeType
{
	None,
	File,
	Folder
};

struct Node;
struct FileList;
struct DirList;

using byte = unsigned char;
using Len = unsigned long long;
using Address = unsigned long long;
using FileNode = Node;
using DirNode = Node;

struct Node
{
	char name[256];
	NodeType type;

	Address parent;
	Address files;
	Address directories;

	Len file_size_in_bytes;
	Address file_data;
};

struct FileList
{
	byte count;
	FileNode* files[8];
	FileList* next;
};

struct DirList
{
	byte count;
	DirNode* directories[8];
	DirList* next;
};