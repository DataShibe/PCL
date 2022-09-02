#include "Interpreter.h"

#include <string>
#include <fstream>
#include <iostream>
#include <string_view>

using namespace std;


int main(int argc, char** argv)
{
	// if no input file is given, end the program
	if (argc == 0) // 1
	{
		cout << "You need to enter a file! Usage: PCL.exe example.pcl" << endl;
		return 0;
	}

	// if more than two arguments are given, output debug information
	bool debugOutput = argc != 2;

	string inputFile = argv[1];

	ifstream inputStream;
	inputStream.open(inputFile);

	string line;
	string code = "";

	// read the contents of the file
	while (getline(inputStream, line))
		code += line + "\n";

	// interpret the file contents
	Interpreter interpreter = Interpreter();
	interpreter.interpret(code, debugOutput);

	return 0;
}