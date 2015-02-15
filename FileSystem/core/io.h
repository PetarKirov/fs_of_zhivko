#pragma once

#include "../common/type_def.h"
#include "../common/slice.h"

#include <fstream>

class IOInterface
{
	virtual void write(Address addr, const void* data, Len data_size_in_bytes) = 0;

	virtual void read(Address addr, void* buffer, Len data_size_in_bytes) = 0;
};

// In the distant future...
// class RAMIO : IOInterface { ... }

// IO backed by the file system
class FileIO : IOInterface
{
	std::fstream data_;
	bool is_open_;

public:
	void open_existing(String real_file_path);

	void create_new(String real_file_path);

	void write(Address addr, const void* data, Len data_size_in_bytes) override;

	void read(Address addr, void* buffer, Len data_size_in_bytes) override;

	bool is_open();
};
