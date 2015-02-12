#pragma once

const int node_name_len = 256;
const int chunk_size = 8;

using byte = unsigned char;
using LenSmall = byte;
using Len = unsigned long long;
using Address = unsigned long long;

enum NodeType
{
	None,
	File,
	Dir
};

struct BlobPtr
{
	Address ptr;
	Len blob_size;
};

// For singly-linked chunk lists
struct ChunkPtr
{
	Address ptr;
	LenSmall elem_count;
};

struct Chunk
{
	Address elems[chunk_size];
	ChunkPtr next;
};

struct Node
{
	Address parent;
	ChunkPtr files;
	ChunkPtr dirs;
	BlobPtr file_data;

	NodeType type;

	char name[node_name_len];

	/** 
	*	If node.type == File => parent && !files && !dirs && maybe(file_data)
	*
	*	If node.type == Dir => maybe(parent) && maybe(files) && maybe(dirs) && !file_data
	*	(if this is the root dir it will not have a parent, otherwise it will have)
	*
	*	Else (if node.type == None) => !parent && !files && !dirs && !file_data.
	*	(node is uninitialized)
	*/
};

