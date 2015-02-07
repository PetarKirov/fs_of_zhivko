#include <iostream>
#include <string>
using namespace std;

#include "file_system.h"

bool AskUser(string msg);
bool isExit(string);
void mainLoop();

int main(int argc, const char **argv)
{
	string real_path_to_file_system;
	FileSystem fs;

	if (argc == 1)
	{
		cout << "Enter file path: ";
		cin >> real_path_to_file_system;
	}
	else // else (argc > 1)
	{
		real_path_to_file_system = string(argv[1]);
	}

	if (!FileSystem::IsValidFSFile(real_path_to_file_system))
	{
		if (AskUser("The file does not exist. Do you want to create a new file? (y/ne): "))
		{
			fs = FileSystem(real_path_to_file_system, true);
		}
		else
		{
			cout << "Fuck off" << endl;
			return 0;
		}
	} // the file is valid
	else
	{
		fs = FileSystem(real_path_to_file_system, false);
	}

	mainLoop();
}

bool AskUser(string msg)
{
	cout << msg;

	string input;
	cin >> input;

	if (input == "y" || input == "Y" || input == "yes" || input == "YES")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void mainLoop()
{
	string input;
	while (cin >> input && !isExit(input))
	{
		// TODO Execute some command
	}
}

bool isExit(string input)
{
	return input == "exit" ||
		input == "EXIT";
}