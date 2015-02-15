#pragma once

#include "../common/type_def.h"
#include "../common/slice.h"

const Len data_block_size_in_bytes = 1024;
const int node_name_len = 256;

// File system layout
// zhivko{SuperBlock}{Nodes}{Data Blocks}

// ============== Data Block definition ====================

const Len DataBlockFileCapacity = data_block_size_in_bytes - sizeof(DataBlockIndex);
const Len DataBlockIndexesCapacity = DataBlockFileCapacity / sizeof(NodeIndex);

struct FileChunk
{
	// Bytes used for file data in current data block
	Len bytes_used;
	byte raw_data[DataBlockFileCapacity];
};

struct NodeIndexesChunk
{
	// Count of node indexes in current data block
	Len count;
	NodeIndex elements[DataBlockIndexesCapacity];
};

// Singly-linked list
struct DataBlock
{
	union
	{
		bool is_empty;
		Len _unused; // for alignment only
	};

	union
	{
		FileChunk file_data;
		NodeIndexesChunk node_indexes;
	};

	DataBlockIndex next; // the index of the next data block, if any

	bool empty()
	{
		return is_empty;
	}

	RawData append_data(RawData data)
	{
		for (Len i = file_data.bytes_used;
			i < DataBlockFileCapacity && !data.empty();
				i++, data.pop_front())
		{
			this->file_data.raw_data[i] = data.front();
		}

		return data;
	}
};


// ===================== Node definition =================

enum NodeType
{
	Empty,
	File,
	Dir
};

struct FileNodeInfo
{
	DataBlockIndex file_data;
};

struct DirNodeInfo
{
	DataBlockIndex files;
	DataBlockIndex dirs;
};

struct Node
{
	NodeIndex parent;

	CharType name[node_name_len];

	NodeType type;

	// this->type indicates if file_info is used or dir_info
	union
	{
		FileNodeInfo file_info;
		DirNodeInfo dir_info;
	};

	Node(NodeType type_)
	{
		this->type = type_;
	}

	Node() = default;

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

using DirNode = Node;
using FileNode = Node;
