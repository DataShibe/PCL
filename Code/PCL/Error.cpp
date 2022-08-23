#include "Error.h"

#include <string>
#include <iostream>

using namespace std;


void Error::lineError(int line, string message)
{
	cout << "Error at line " << to_string(line) << ": " << message << endl;
	exit(-1);
}