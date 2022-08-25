#ifndef PARSER_H
#define PARSER_H

#include "Command.h"
#include "Token.h"

#include <vector>


class Parser
{
public:
	Parser();

	std::vector<Command> parse(std::vector<Token> tokenList);

private:
	std::vector<int> getTypes(std::vector<Token> tokenList, int n);
	std::vector<Token> getUntilNextLine(int line, std::vector<Token> tokenBuffer, int startingIndex);
	std::vector<Token> eraseUntilNextLine(int line, std::vector<Token> tokenBuffer);
};


#endif