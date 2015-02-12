#include "app.h"

bool ask_user(std::wstring msg)
{
	std::wcout << msg;

	std::wstring input;
	std::wcin >> input;

	if (input == L"y" || input == L"Y" || input == L"yes" || input == L"YES")
		return true;

	return false;
}

void main_loop(FileSystem& fs)
{
	std::wstring str;
	bool is_quit_requested = false;

	do
	{
		std::wcout << "> ";
		std::getline(std::wcin >> std::ws, str); //ignore leading whitespace

		String input = { str.c_str(), str.size() };
		trim_space_ref(input);

		execute_command(input, is_quit_requested, fs);
	}
	while (!std::wcout.eof() && !is_quit_requested);
}

std::wstring version = L"		~==== Zhivko Virtual FileSystem v0.01 ====~		";

void print_version()
{
	std::wcout << version << std::endl;
}

void print_help()
{
	std::wcout
		<< std::endl
		<< version 
		<< std::endl
		<< R"(
	You can use following commands in the interactive prompt:

		============ General ============
	* help
	Displays the list of available commands.

	* version
	Displays the current version of the program.

	* exit
	Closes the program.

		============ Directory operations ============
	* mkdir <path>
	Makes a new directory at the specified <path>.

	* import_dir <source_path - in real fs> <dest_path - in vfs>
	Imports a directory from your filesystem (specified by <source_path>) and
	places it in the virtual filesystem (specified by <dest_path>).

	* export_dir <source_path - in vfs> <dest_path - in real fs>
	Exports a directory from the virtual filesystem (specified by <source_path>)
	to a location in your real filesystem (specified by <dest_path>).

	* rmdir <path>
	Removes a directory (specified by <path>), along with its contents.

	* mvdir <source_path> <dest_path>
	Moves a directory from <source_path> to <dest_path>.
	Can also be used for renaming.

	* cpdir <source_path> <dest_path>
	Copies a directory from <source_path> to <dest_path>.
		
	* ls <path>
	Displays the contents of the directory at <path>.

		============ File operations ============
	* mkfile <path> (data)
	Makes a new file at the <path>. If (data) is specified,
	fills the file with it. If the file already exists,
	displays error message and exits.

	* append <path> <data>
	Appends <data> at the end of an already existing file.
	If the file doesn't exist, displays error message and exits.

	* import_file <source_path - in real fs> <dest_path - in vfs>
	Imports a file from your filesystem (specified by <source_path>) and
	places it in the virtual filesystem (specified by <dest_path>).

	* export_file <source_path - in vfs> <dest_path - in real fs>
	Exports a file from the virtual filesystem (specified by <source_path>)
	to a location in your real filesystem (specified by <dest_path>).
		
	* rmfile <path>
	Removes a file specified by <path>.

	* mvfile <source_path> <dest_path>
	Moves a file from <source_path> to <dest_path>.
	Can also be used for renaming.

	* cpfile <source_path> <dest_path>
	Copies a file from <source_path> to <dest_path>.

	* statfile <path>
	Displays information about a file.

	----------------------------------------------------------------
	The general syntax of the commands is:
	`command <required_arg_1> .. <required_arg_N> (optional_arg_1) .. (optional_arg_N)`

	(You should not to write `<`, `>`, `(` or `)` - these symbols
	are used only for illustration purposes in the docs.)

	You can enclose arguments containing whitespace with quotes.
	
	For example: `mvdir "/home/dir name containing space/child dir"`.		
	)" << std::endl;
}

bool check_for_trailing_args(String input)
{
	if (input.empty())
		return false;
	
	std::wcout << L"Error unused arguments: `" << input.begin() << L"`\n";
	return true;
}

void execute_command(String input, bool& is_quit, FileSystem& fs)
{
	is_quit = false;

	// General Commands
	if (eat_command(input, L"help")) { print_help(); }

	else if (eat_command(input, L"version")) { print_version(); }

	else if (eat_command(input, L"exit")) { is_quit = true; return; }

	// Directory commands
	else if (eat_command(input, L"mkdir"))
	{
		auto path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.CreateDirectory(path);
	}
	// FIXME: import_dir "E:\some dir" /r/place
	else if (eat_command(input, L"import_dir"))
	{
		auto source_path = eat_arg(input);
		auto dest_path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.ImportDirectory(source_path, dest_path);
	}

	else if (eat_command(input, L"export_dir"))
	{
		auto source_path = eat_arg(input);
		auto dest_path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.ExportDirectory(source_path, dest_path);
	}

	else if (eat_command(input, L"rmdir"))
	{
		auto path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.RemoveDirectory(path);
	}

	// FIXME: mvdir /urs/d "E:\some folder"
	else if (eat_command(input, L"mvdir"))
	{
		auto source_path = eat_arg(input);
		auto dest_path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.MoveDirectory(source_path, dest_path);
	}

	else if (eat_command(input, L"cpdir"))
	{
		auto source_path = eat_arg(input);
		auto dest_path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.CopyDirectory(source_path, dest_path);
	}

	else if (eat_command(input, L"ls"))
	{
		auto path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.DirectoryInfo(path);
	}

	// File commands
	else if (eat_command(input, L"mkfile"))
	{
		auto path = eat_arg(input);
		auto data = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.CreateFile(path, data);
	}

	else if (eat_command(input, L"append"))
	{
		auto path = eat_arg(input);
		auto data = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.AppendToFile(path, data);
	}

	else if (eat_command(input, L"import_file"))
	{
		auto source_path = eat_arg(input);
		auto dest_path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.ImportFile(source_path, dest_path);
	}

	else if (eat_command(input, L"export_file"))
	{
		auto source_path = eat_arg(input);
		auto dest_path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.ExportFile(source_path, dest_path);
	}

	else if (eat_command(input, L"rmfile"))
	{
		auto path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.RemoveFile(path);
	}

	// FIXME: mvdir /urs/d "E:\some folder"
	else if (eat_command(input, L"mvfile"))
	{
		auto source_path = eat_arg(input);
		auto dest_path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.MoveFile(source_path, dest_path);
	}

	else if (eat_command(input, L"cpfile"))
	{
		auto source_path = eat_arg(input);
		auto dest_path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.CopyFile(source_path, dest_path);
	}

	else if (eat_command(input, L"statfile"))
	{
		auto path = eat_arg(input);

		if (check_for_trailing_args(input)) return;

		fs.FileInfo(path);
	}

	else
	{
		std::wcout << "Unknown command: `"
			<< input.begin()
			<< "`.\n"
			<< "Type `help` for a list of available commands.\n";
	}
}

bool eat_command(String &input, const CharType *command)
{
	// skip command
	auto remaining = skip_string(input, command);

	// skip whitespace
	skip_space_ref(remaining);

	if (remaining == input) // input does not contain command
		return false;

	// assign to input the part after the command
	input = remaining; 
	return true;
}

String eat_arg(String &input)
{
	// Extract argument by skipping characters until we hit whitespace,
	// unless we are inside quotes - in that case we skip the quotes too.

	auto rem = input; // remaining
	bool in_quotes = input[0] == '\"';

	size_t i = 1;
	while (i < input.size() && (!space_in_front(rem) || in_quotes))
	{
		if (input[i] == '"' && input[i - 1] != '\\')
			in_quotes = !in_quotes;

		i++;
		rem.pop_front();
	}

	auto arg = input;
	input = rem.slice(1, rem.size());

	if (arg[0] == '\"' && arg[i - 1] == '\"')
		return arg.slice(1, i - 1);
	else
		return arg.slice(0, i);
}
