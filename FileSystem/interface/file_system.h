#pragma once

#include <fstream>

#include "../common/slice.h"
#include "../core/io.h"
#include "../core/super_block.h"
#include "path.h"

class FileSystem
{
	FileIO io;

	SuperBlock super_block;

	friend class DataBlockIterator;

public:

	// Creates a NEW file system at the specified file path with the specified size
	FileSystem(String real_file_path, Len initial_file_system_size_in_blocks);

	// Opens an EXISTING file system at the specified file path
	FileSystem(String real_file_path);

	bool IsOpen();

	static bool IsValidFSFile(String real_file_path);

	// ========= Directory interface ==============
	bool CreateDirectory(String path);

	//Import an already existing directory in the real file system
	bool ImportDirectory(String source_path, String dest_path);

	//Export a directory
	bool ExportDirectory(String source_path, String dest_path);

	bool RemoveDirectory(String path);

	bool MoveDirectory(String source_path, String dest_path);

	bool CopyDirectory(String source_path, String dest_path);

	bool DirectoryInfo(String path);

	// ========= File interface ==============
	bool CreateFile(String path, RawData data);

	bool AppendToFile(String file_path, RawData data);

	bool ImportFile(String source_path, String dest_path);

	bool ExportFile(String source_path, String dest_path);

	bool RemoveFile(String path);

	bool MoveFile(String source_path, String dest_path);

	bool CopyFile(String source_path, String dest_path);

	bool FileInfo(String path);

	bool ViewFile(String path);

private:

	// INTERNAL:

	void create_root();

	NodeIndex create_node(NodeIndex parent, String name, NodeType type, RawData data);

	Len get_child_nodes_count(FileNode p);

	// SUPER INTERNAL:

	void add_child_node(NodeIndex parent, NodeIndex new_dir_idx, NodeType type);

	void append_file_data(DataBlockIndex file_data_idx, RawData data);

	NodeIndex find_dir(String path);

	// Can only be called when nodes_free cache is empty.
	void fill_nodes_free_cache();

	NodeIndex allocate_node();

	void free_node(NodeIndex idx);

	DataBlockIndex allocate_data_block();

	void free_data_block(DataBlockIndex idx);

	void write_node(NodeIndex idx, const Node * node);

	void read_node(NodeIndex idx, Node* node);

	void write_data_block(DataBlockIndex idx, const DataBlock* data_block);

	void read_data_block(DataBlockIndex idx, DataBlock* data_block);
};

class DataBlockIterator
{
private:
	FileSystem* fs;
	DataBlockIndex current_idx;

public:
	DataBlock current;

	DataBlockIterator() = default;

	DataBlockIterator(DataBlockIndex idx, FileSystem* file_sys)
		: fs(file_sys), current_idx(idx)
	{
		fs->read_data_block(idx, &current);
	}

	void move()
	{
		current_idx = current.next;
		fs->read_data_block(current.next, &current);
	}

	// writes the (changed) current data block to the file system
	void commit_changes()
	{
		fs->write_data_block(current.next, &current);
	}

	DataBlockIndex get_index()
	{
		return this->current_idx;
	}
};

