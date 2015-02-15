#include "file_system.h"

#include "../common/assert.h"
#include "../common/string_helpers.h"

bool FileSystem::IsOpen()
{
	return this->io.is_open();
}

// Returns true if file exists and the file begins with the special header and super block 
bool FileSystem::IsValidFSFile(String real_file_path)
{
	auto file = std::fstream(real_file_path.begin(), std::ios::binary | std::ios::in | std::ios::out);

	if (!file.is_open() || !file.good())
		return false;

	file.seekg(0, file.end);
	long long length = file.tellg();

	if (length < sizeof(SuperBlock))
		return false;

	const Len special_header_len = sizeof(SuperBlock::special_header);

	file.seekg(0, file.beg);
	char buffer[special_header_len + 1];
	buffer[special_header_len] = '\0';

	file.read(buffer, special_header_len);

	Slice<const char> str = { buffer, (size_t)special_header_len };
	return starts_with(str, "zhivko");
}

FileSystem::FileSystem(String real_file_path)
{
	this->io.open_existing(real_file_path);
}

FileSystem::FileSystem(String real_file_path, Len initial_size)
{
	io.create_new(real_file_path);

	super_block.file_system_size_in_blocks = initial_size;

	io.write(0, &this->super_block, sizeof(SuperBlock));

	create_root();
}

bool FileSystem::ImportDirectory(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::ExportDirectory(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::RemoveDirectory(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::MoveDirectory(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::CopyDirectory(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::DirectoryInfo(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::CreateDirectory(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";	

	String parent_dir_name = dir_name(path);
	String dir_name = file_name(path);

	NodeIndex parent_dir_node_index = find_dir(parent_dir_name);
	create_node(parent_dir_node_index, dir_name, NodeType::Dir, RawData{});

	return true;
}

bool FileSystem::CreateFile(String path, RawData data)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	std::cout << "data: `" << std::string((const char*)data.begin(), data.size()) << "`\n";
	

	String parent_dir_name = dir_name(path);
	String dir_name = file_name(path);

	NodeIndex parent_dir_node_index = find_dir(parent_dir_name);
	create_node(parent_dir_node_index, dir_name, NodeType::File, data);

	return true;
}

bool FileSystem::AppendToFile(String path, RawData data)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	std::cout << "data: `" << std::string((const char*)data.begin(), data.size())<< "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::ImportFile(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::ExportFile(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::RemoveFile(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::MoveFile(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::CopyFile(String source_path, String dest_path)
{
	std::wcout
		<< "source_path: `" << std::wstring(source_path.begin(), source_path.size()) << "`\n"
		<< "dest_path: `" << std::wstring(dest_path.begin(), dest_path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::FileInfo(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	FS_ASSERT( false, L"Not Implemented:" );
	return false;
}

bool FileSystem::ViewFile(String path)
{
	std::wcout << "path: `" << std::wstring(path.begin(), path.size()) << "`\n";
	FS_ASSERT(false, L"Not Implemented:");
	return false;
}

// ====================== Internal =========================

const Address RootDirAddress = 1;
const String RootDirName = make_str(L"Z:");

void FileSystem::create_root()
{
	Node root = Node(NodeType::Dir);
	string_copy(root.name, RootDirName);

	NodeIndex node_idx = RootDirAddress;
	write_node(node_idx, &root);
}

NodeIndex FileSystem::create_node(NodeIndex parent, String name, NodeType type, RawData data)
{
	// 1) Create a new_node
	Node new_node = Node(type);
	string_copy(new_node.name, name);
	new_node.parent = parent;

	NodeIndex new_node_idx = allocate_node();
	write_node(new_node_idx, &new_node);

	if (type == NodeType::File && !data.empty())
	{
		DataBlockIndex new_file_data_idx = allocate_data_block();

		append_file_data(new_file_data_idx, data);
	}

	// 2) Add the new_node to the parent dir
	add_child_node(parent, new_node_idx, NodeType::Dir);

	return new_node_idx;
}

Len FileSystem::get_child_nodes_count(FileNode p)
{
	return Len();
}

void FileSystem::add_child_node(NodeIndex parent, NodeIndex new_dir_idx, NodeType type)
{
	DirNode parent_node;
	read_node(parent, &parent_node);

	DataBlockIterator it;

	if (type == NodeType::File)
		it = DataBlockIterator(parent_node.dir_info.files, this);
	else if (type == NodeType::Dir)
		it = DataBlockIterator(parent_node.dir_info.dirs, this);

	while (it.current.node_indexes.count >= DataBlockIndexesCapacity)
		it.move();

	it.current.node_indexes.elements[it.current.node_indexes.count++] = new_dir_idx;
	it.commit_changes();
}

void FileSystem::append_file_data(DataBlockIndex file_data_idx, RawData data)
{
	DataBlockIterator it;

	it = DataBlockIterator(file_data_idx, this);

	while (it.current.file_data.bytes_used >= DataBlockFileCapacity)
		it.move();

	//it.cu


}

NodeIndex FileSystem::find_dir(String path)
{
	return RootDirAddress;
}

NodeIndex FileSystem::allocate_node()
{
	if (super_block.nodes_free_count != 0)
	{
		return super_block.nodes_free[super_block.nodes_free_count--];
	}
	else // free nodes cache is empty
	{
		NodeIndex result = super_block.nodes_free[0];

		fill_nodes_free_cache();

		return result;
	}
}

void FileSystem::free_node(NodeIndex idx)
{
	// TODo
}

DataBlockIndex FileSystem::allocate_data_block()
{
	FS_ASSERT(false, L"Not implemeted!");
	return 0;
}

void FileSystem::free_data_block(DataBlockIndex idx)
{
	FS_ASSERT(false, L"Not implemeted!");
}

void FileSystem::fill_nodes_free_cache()
{
	SuperBlock& sb = this->super_block;

	Address cache_ptr = sb.get_nodes_free_cache_address();

	for (NodeIndex i = 1; i < free_nodes_cache_size; i++)
	{
		Node current_node;
		read_node(i, &current_node);

		// If the current node is empty, add it to the nodes_free cache.
		if (current_node.type == NodeType::Empty)
		{
			io.write(cache_ptr, &i, sizeof(NodeIndex));
			cache_ptr += sizeof(NodeIndex);
		}
	}
}

void FileSystem::write_node(NodeIndex idx, const Node * node)
{
	Address node_addr = super_block.get_node_address(idx);

	io.write(node_addr, node, sizeof(Node));
}

void FileSystem::read_node(NodeIndex idx, Node * node)
{
	Address node_addr = super_block.get_node_address(idx);

	io.read(node_addr, node, sizeof(Node));
}

void FileSystem::write_data_block(DataBlockIndex idx, const DataBlock * data_block)
{
	Address data_block_addr = super_block.get_data_block_address(idx);

	io.write(data_block_addr, data_block, sizeof(DataBlock));
}

void FileSystem::read_data_block(DataBlockIndex idx, DataBlock * data_block)
{
	Address data_block_addr = super_block.get_data_block_address(idx);

	io.read(data_block_addr, data_block, sizeof(DataBlock));
}
