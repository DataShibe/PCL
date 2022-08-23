#ifndef COMMAND_H
#define COMMAND_H

#include "Token.h"

#include <vector>
#include <string>


class Command
{
public:
	Command(int type, std::vector<Token> args);

	std::string toString();

	int getType();

	std::vector<Token> getArgs();

private:
	int type;
	std::vector<Token> args;
};


#endif