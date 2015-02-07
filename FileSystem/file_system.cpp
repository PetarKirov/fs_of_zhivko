#include "file_system.h"

bool FileSystem::IsOpen()
{
	return this->is_open_;
}

FileSystem::FileSystem()
{
	this->is_open_ = false;
}

FileSystem::FileSystem(std::string real_file_path)
{
	open_existring_file_system(real_file_path);

	this->is_open_ = true;
}

FileSystem::FileSystem(std::string real_file_path, Len initial_size)
{
	this->create_empty_file_system(real_file_path, initial_size);
}

void FileSystem::create_empty_file_system(std::string real_file_path, Len initial_size)
{
	this->data_ = std::fstream(real_file_path, std::ios::binary | std::ios::in | std::ios::out);
	this->data_.clear();
	this->data_.open(real_file_path, std::ios::out); //Create file.
	this->data_.close();
	this->data_.open(real_file_path, std::ios::binary | std::ios::in | std::ios::out);

	this->data_.seekp(0, std::ios_base::beg);
	this->data_ << special_header;

	this->data_.write((const char*)&this->super_block, sizeof this->super_block);
}

void FileSystem::open_existring_file_system(std::string real_file_path)
{
	auto file = std::fstream(real_file_path, std::ios::binary | std::ios::in | std::ios::out);
}



// Returns true if file exists and the file begins with the special header and super block 
bool FileSystem::IsValidFSFile(std::string real_file_path)
{
	auto file = std::fstream(real_file_path, std::ios::binary | std::ios::in | std::ios::out);

	if (!file.is_open() || !file.good())
		return false;

	file.seekg(0, file.end);
	long long length = file.tellg();

	if (length < special_header_len + super_block_size)
		return false;

	file.seekg(0, file.beg);
	char buffer[special_header_len + 1];
	buffer[special_header_len] = '\0';

	file.read(buffer, special_header_len);

	std::string str = std::string(buffer);
	return str == special_header;
}


bool FileSystem::ImportFileSystem(std::string real_file_path)
{
	return false;
}

bool FileSystem::AddDirectory(std::string path, std::string name)
{
	return false;
}

bool FileSystem::AddFile(std::string path, std::string name)
{
	return false;
}

bool FileSystem::Export(std::string real_path)
{
	return false;
}

bool FileSystem::Import(std::string)
{
	return false;
}
