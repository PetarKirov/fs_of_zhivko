#pragma once

#include "structures.h"

const Len block_size = 1024;
const Len free_nodes_cache_size = 256;
const Len free_blocks_cache_size = 256;

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
	{
		block_size_in_bytes = block_size;
	}

	bool is_free_blocks_cache_full()
	{
		return cached_free_blocks_count < free_blocks_cache_size;
	}

	bool is_free_blocks_cache_empty()
	{
		return cached_free_blocks_count  == 0;
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

	void* get(Address offset)
	{
		return (void*)(this->start_address + offset);
	}

	void write(Address addr, void* data, Len data_size_in_bytes);

	void write(void* in_memory_addr, void* data, Len data_size_in_bytes);

	DirNode* get_parent(Node* node)
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
	}
};