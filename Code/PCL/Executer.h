#ifndef EXECUTER_H
#define EXECUTER_H

#include "Command.h"

#include <vector>


class Executer
{
public:
	Executer();

	void execute(std::vector<Command> commandList);
};


#endif