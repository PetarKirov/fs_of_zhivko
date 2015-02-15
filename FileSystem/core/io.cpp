#include "io.h"

#include "../common/assert.h"

void FileIO::open_existing(String real_file_path)
{
	auto str = std::wstring(real_file_path.begin(), real_file_path.size());

	this->data_.open(str, std::ios::binary | std::ios::in | std::ios::out);

	this->is_open_ = true;
}

void FileIO::create_new(String real_file_path)
{
	auto str = std::wstring(real_file_path.begin(), real_file_path.size());

	this->data_.open(str, std::ios::binary | std::ios::in | std::ios::out);
	this->data_.clear();
	this->data_.open(str, std::ios::out); //Actually create file.
	this->data_.close();
	this->data_.open(str,
		std::ios::binary | std::ios::in | std::ios::out);

	this->is_open_ = true;
}

void FileIO::write(Address addr, const void * data, Len data_size_in_bytes)
{
	FS_ASSERT( data != nullptr, L"No data to read from!" );
	FS_ASSERT( this->is_open_, L"Writing to a closed IO!" );

	this->data_.seekp(addr, std::ios_base::beg);
	this->data_.write((const char*)data, data_size_in_bytes);
}

void FileIO::read(Address addr, void * buffer, Len data_size_in_bytes)
{
	FS_ASSERT( buffer != nullptr, L"No buffer to write to!" );
	FS_ASSERT( this->is_open_, L"Reading from a closed IO!" );

	this-> data_.seekg(addr, std::ios_base::beg);
	this->data_.read((char*)buffer, data_size_in_bytes);
}

bool FileIO::is_open()
{
	return this->is_open_;
}
