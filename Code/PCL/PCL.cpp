#include "Interpreter.h"

#include <string>
#include <fstream>
#include <iostream>
#include <string_view>

using namespace std;
using namespace std::literals;


int main(int argc, char** argv)
{

	if (argc == 1)
	{
		cout << "You need to enter a file! Usage: PCL.exe example.pcl" << endl;
		return 0;
	}

	bool debugOutput = argc != 2;

	//string inputFile = "code.pcl";
	string inputFile = argv[1];

	ifstream inputStream;
	inputStream.open(inputFile);

	string line;
	string code = "";

	while (getline(inputStream, line))
		code += line + "\n";

	Interpreter interpreter = Interpreter();
	interpreter.interpret(code, debugOutput);

	return 0;
}