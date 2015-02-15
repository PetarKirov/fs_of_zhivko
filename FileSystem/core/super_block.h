#pragma once

#include "structures.h"

// Used for offsetof() macro
#include <cstddef>

// The file system layout is:
// zhivko\0{SuperBlock}{Nodes}{Data Blocks}

// sizeof(SuperBlock) = 
//	5 * sizeof(Len)	+ free_nodes_cache_size * sizeof(Address)
//					+ free_blocks_cache_size * sizeof(Address)
//		== 5 * 8 + (256 * 8) + (256 * 8)
//		== 40 + 4096 = 4136

const Len free_nodes_cache_size = 256;
const Len free_blocks_cache_size = 256;

struct SuperBlock
{
	char special_header[6];// = "zhivko";

	Len block_size_in_bytes;
	Len file_system_size_in_blocks;

	// cache the indexes of some free nodes
	Len nodes_free_count;
	NodeIndex nodes_free[free_nodes_cache_size];

	// cache the indexes of some free data blocks
	Len blocks_free_count;
	DataBlockIndex free_blocks[free_blocks_cache_size];

	Len nodes_all_count;
	Len data_blocks_all_count;

	Len start_address;

	SuperBlock() : SuperBlock(data_block_size_in_bytes) { }

	SuperBlock(Len block_size_)
	{
		special_header[0] = 'z';
		special_header[1] = 'h';
		special_header[2] = 'i';
		special_header[3] = 'v';
		special_header[4] = 'k';
		special_header[5] = 'o';

		this->block_size_in_bytes = block_size_;

		this->nodes_free_count = 0;
		std::memset(nodes_free, 0, sizeof(NodeIndex) * free_nodes_cache_size);

		this->blocks_free_count = 0;
		std::memset(free_blocks, 0, sizeof(DataBlockIndex) * free_blocks_cache_size);

		this->start_address = sizeof(SuperBlock); // + alignment
	}

	// Converts a node index to an address in the whole file system.
	// (The address can point inside the special header or the super block).
	Address get_node_address(NodeIndex index)
	{
		FS_ASSERT(index < this->nodes_all_count, L"Node index out of range!");

		return this->start_address + index * sizeof(Node);
	}

	// Converts a data block index to an address in the whole file system.
	// (The address can point inside the special header or the super block).
	Address get_data_block_address(DataBlockIndex index)
	{
		FS_ASSERT(index < this->data_blocks_all_count, L"Data block index out of range!");

		return this->start_address +
			nodes_all_count * sizeof(Node) + // skip the nodes
			index * sizeof(DataBlock);
	}

	// Get an address pointing to the beginning of the nodes_free cache.
	Address get_nodes_free_cache_address()
	{
		return offsetof(SuperBlock, nodes_free);
	}

	// Get an address pointing to the beginning of the data_blocks_free cache.
	Address get_data_blocks_free_cache_address()
	{
		return offsetof(SuperBlock, blocks_free_count);
	}

	// Can only be called when nodes_free cache is empty.
	/*void fill_nodes_free_cache();

	void write_node(NodeIndex idx, const Node* node);

	void read_node(NodeIndex idx, Node* node);

	void write_data_block(DataBlockIndex idx, const DataBlock* data_block);

	void read_data_block(DataBlockIndex idx, DataBlock* data_block);

	NodeIndex allocate_node();

	void free_node(NodeIndex idx);

	DataBlockIndex allocate_data_block();

	void create_root();

	NodeIndex create_node(NodeIndex parent, String name, NodeType type, RawData data);

	void add_child_node(NodeIndex parent, NodeIndex new_dir_idx, NodeType type);

	void append_file_data(DataBlockIndex file_data_idx, RawData data);	

	Len get_child_nodes_count(FileNode p);*/
};
