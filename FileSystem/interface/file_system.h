#pragma once

#include <fstream>

#include "../common/slice.h"
#include "../core/super_block.h"

static const Slice<const char> special_header = make_narrow_str("zhivko");
static const size_t special_header_len = 6;//special_header.size();

class FileSystem
{
	std::fstream data_;
	bool is_open_;

	void create_empty_file_system(String real_file_path, Len initial_size_in_blocks);
	void open_existring_file_system(String real_file_path);

	SuperBlock super_block;

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
	bool CreateFile(String path, String data);

	bool AppendToFile(String file_path, String data);

	bool ImportFile(String source_path, String dest_path);

	bool ExportFile(String source_path, String dest_path);

	bool RemoveFile(String path);

	bool MoveFile(String source_path, String dest_path);

	bool CopyFile(String source_path, String dest_path);

	bool FileInfo(String path);
};
