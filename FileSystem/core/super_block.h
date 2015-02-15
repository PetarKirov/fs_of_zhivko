#pragma once

#include "../common/assert.h"
#include "structures.h"

#include <cstring>

const Len block_size = 1024;
const Len free_nodes_cache_size = 256;
const Len free_blocks_cache_size = 256;

// The file system layout is:
// zhivko{SuperBlock}{Nodes}{Data Blocks}

// sizeof(SuperBlock) = 
//	5 * sizeof(Len)	+ free_nodes_cache_size * sizeof(Address)
//					+ free_blocks_cache_size * sizeof(Address)
//		== 5 * 8 + (256 * 8) + (256 * 8)
//		== 40 + 4096 = 4136

struct SuperBlock
{
	Len block_size_in_bytes;
	Len file_system_size_in_blocks;

	Len cached_free_nodes_count;
	Address cached_free_nodes[free_nodes_cache_size];

	Len cached_free_blocks_count;
	Address cached_free_blocks[free_blocks_cache_size];

	Len start_address;

	SuperBlock()
		: SuperBlock(0, 0) { }

	SuperBlock(Len file_system_size, Len block_size_ = block_size)
	{
		this->file_system_size_in_blocks = file_system_size;
		this->block_size_in_bytes = block_size_;

		this->cached_free_nodes_count = 0;
		std::memset(cached_free_nodes, 0, sizeof(Address) * free_nodes_cache_size);

		this->cached_free_blocks_count = 0;
		std::memset(cached_free_nodes, 0, sizeof(Address) * free_nodes_cache_size);
	}

	bool is_free_blocks_cache_full()
	{
		return cached_free_blocks_count < free_blocks_cache_size;
	}

	bool is_free_blocks_cache_empty()
	{
		return cached_free_blocks_count  == 0;
	}

	Address create_node(NodeType type)
	{
		auto node_address = allocate_node();

		Node* node = new(get(node_address)) Node(type);

		FS_ASSERT( node->type == type, L"Error in Constructor of Node!" );

		return node_address;
	}

	Address allocate()
	{
		if (!is_free_blocks_cache_empty())
		{
			return cached_free_blocks[cached_free_blocks_count--];
		}
		else
		{
			write(cached_free_nodes, get(cached_free_blocks[0]), cached_free_nodes_count);
		}
	}

	Address allocate_node()
	{
		return 123123;
	}

	void free(Address addr)
	{
		if (!is_free_blocks_cache_full())
		{
			cached_free_blocks[++cached_free_blocks_count] = addr;
		}
		else
		{
			write(addr, cached_free_blocks, cached_free_blocks_count);

			cached_free_blocks[0] = addr;
			cached_free_blocks_count = 0;
		}
	}

	// Converts an address in the file to a pointer (address that we can go to).
	void* get(Address offset)
	{
		return (void*)(this->start_address + offset);
	}

	void write(Address addr, void* data, Len data_size_in_bytes);

	void write(void* in_memory_addr, void* data, Len data_size_in_bytes);

	/*DirNode* get_parent(Node* node)
	{
		return (DirNode*)get(node->parent);
	}

	FileList* get_files(DirNode* node)
	{
		return (FileList*)get(node->files);
	}

	DirList* get_directories(DirNode* node)
	{
		return (DirList*)get(node->directories);
	}

	void* get_data(FileNode* node)
	{
		return get(node->file_data);
	}*/
};