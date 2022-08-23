#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Token.h"

#include <string>
#include <vector>


class Tokenizer
{
public:
	Tokenizer();

	std::vector<Token> tokenize(std::string code);

private:
	std::vector<std::string> commands;
	std::vector<std::string> operators;
	char ovr;
	char col;
};


#endif