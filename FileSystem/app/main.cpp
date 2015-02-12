#include "app.h"

int wmain(int argc, const wchar_t **argv)
{
	String real_path_to_file_system;
	FileSystem fs;
	std::wstring tmp;

	if (argc == 1)
	{
		std::wcout << "Enter file path: ";
		std::wcin >> tmp;

		real_path_to_file_system = String(tmp.c_str(), tmp.size());
	}
	else // else (argc > 1)
	{
		real_path_to_file_system = make_str(argv[1]);
	}

	if (!FileSystem::IsValidFSFile(real_path_to_file_system))
	{
		std::wcout << real_path_to_file_system.begin() << L"\n";

		if (ask_user(L"The file does not exist. Do you want to create a new file? (y/ne): "))
		{
			fs = FileSystem(real_path_to_file_system, nullptr);
			std::wcout << L"File opened successfully." << std::endl;
		}
		else
		{
			std::wcout << "Fuck off" << std::endl;
			return 0;
		}
	}
	else // the file is valid
	{
		fs = FileSystem(real_path_to_file_system, nullptr);
		std::wcout << "File opened successfully." << std::endl;
	}

	main_loop(fs);
}