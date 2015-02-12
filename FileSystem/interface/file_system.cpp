#include "file_system.h"

#include "../common/assert.h"
#include "../common/string_helpers.h"

bool FileSystem::IsOpen()
{
	return this->is_open_;
}

FileSystem::FileSystem()
{
	this->is_open_ = false;
}

FileSystem::FileSystem(String real_file_path, nullptr_t)
{
	open_existring_file_system(real_file_path);

	this->is_open_ = true;
}

FileSystem::FileSystem(String real_file_path, Len initial_size)
{
	this->create_empty_file_system(real_file_path, initial_size);
}

void FileSystem::create_empty_file_system(String real_file_path, Len initial_size)
{
	this->data_ = std::fstream(real_file_path.begin(), std::ios::binary | std::ios::in | std::ios::out);
	this->data_.clear();
	this->data_.open(real_file_path.begin(), std::ios::out); //Create file.
	this->data_.close();
	this->data_.open(real_file_path.begin(), std::ios::binary | std::ios::in | std::ios::out);

	this->data_.seekp(0, std::ios_base::beg);
	this->data_ << special_header.begin();

	this->data_.write((const char*)&this->super_block, sizeof this->super_block);
}

void FileSystem::open_existring_file_system(String real_file_path)
{
	auto file = std::fstream(real_file_path.begin(), std::ios::binary | std::ios::in | std::ios::out);
}

// Returns true if file exists and the file begins with the special header and super block 
bool FileSystem::IsValidFSFile(String real_file_path)
{
	auto file = std::fstream(real_file_path.begin(), std::ios::binary | std::ios::in | std::ios::out);

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

	Slice<const char> str = { buffer, special_header_len };
	return starts_with(str,  special_header.begin());
}


bool FileSystem::ImportDirectory(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::ExportDirectory(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::RemoveDirectory(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::MoveDirectory(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::CopyDirectory(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::DirectoryInfo(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::CreateDirectory(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::CreateFile(String path, String data)
{
	std::wcout
		<< "path: `" << std::wstring(path.begin(), path.size()) << "`\n"
		<< "data: `" << std::wstring(data.begin(), data.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::AppendToFile(String path, String data)
{
	std::wcout
		<< "path: `" << std::wstring(path.begin(), path.size()) << "`\n"
		<< "data: `" << std::wstring(data.begin(), data.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::ImportFile(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::ExportFile(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::RemoveFile(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::MoveFile(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::CopyFile(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}

bool FileSystem::FileInfo(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	fs_assert(false, L"Not Implemented:", __func__);
	return false;
}
