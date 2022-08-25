#ifndef EXECUTER_H
#define EXECUTER_H

#include "Command.h"

#include <vector>


class Executer
{
public:
	Executer();

	void execute(std::vector<Command> commandList);

private:
	float getVal(std::vector<char> types, std::vector<float> values, char type);
};


#endif