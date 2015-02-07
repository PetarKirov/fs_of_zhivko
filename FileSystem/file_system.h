#pragma once

#include <string>
#include <fstream>

#include "SuperBlock.h"

static const std::string special_header = "zhivko";
static const size_t special_header_len = 6;//special_header.size();
static const size_t super_block_size = 4;

class FileSystem
{
	std::fstream data_;
	bool is_open_;

	void create_empty_file_system(std::string real_file_path, Len initial_size_in_blocks);
	void open_existring_file_system(std::string real_file_path);

	SuperBlock super_block;

public:
	static bool IsValidFSFile(std::string real_file_path);

	// Creates an empty un-initialized FS
	FileSystem();

	// Creates a NEW file system at the specified file path with the specified size
	FileSystem(std::string real_file_path, Len initial_file_system_size_in_blocks = 1024);

	// Opens an EXISTING file system at the specified file path
	FileSystem(std::string real_file_path);

	bool IsOpen();

	//Import an already existing file system
	bool ImportFileSystem(std::string real_file_path);

	bool AddDirectory(std::string path, std::string name);
	bool AddFile(std::string path, std::string name);

	// Exports the whole 
	bool Export(std::string real_path);
	bool Import(std::string);
};
