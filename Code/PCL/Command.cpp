#include "Command.h"
#include "Token.h"

#include <vector>
#include <string>

using namespace std;


Command::Command(int type, vector<Token> args)
{
	this->type = type;
	this->args = args;
}

string Command::toString()
{
	string output = to_string(type) + "  [";
	for (Token token : this->args)
	{
		output += token.getStr() + ", ";
	}
	output += "]";


	return output;
}

int Command::getType()
{
	return this->type;
}

vector<Token> Command::getArgs()
{
	return this->args;
}