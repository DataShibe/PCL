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

	std::vector<std::string> operators;

private:
	std::vector<std::string> commands;

	std::string prep(std::string code);

	char ovr;
	char col;
};


#endif