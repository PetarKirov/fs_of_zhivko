#pragma once

#include <string>
#include <fstream>

class FileSystem
{
	std::fstream data_;
	bool is_open_;

	void create_empty_file_system(std::string real_file_path);
	void open_existring_file_system(std::string real_file_path);

public:
	static bool IsValidFSFile(std::string real_file_path);

	// Creates an empty un-initialized FS
	FileSystem();

	// Creates a NEW file system at the specified file path
	FileSystem(std::string real_file_path, bool create_new_file);

	bool IsOpen();

	//Import an already existing file system
	bool ImportFileSystem(std::string real_file_path);

	bool AddDirectory(std::string path, std::string name);
	bool AddFile(std::string path, std::string name);

	// Exports the whole 
	bool Export(std::string real_path);
	bool Import(std::string);
};