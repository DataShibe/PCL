#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Tokenizer.h"
#include "Parser.h"
#include "Executer.h"

#include <string>


class Interpreter
{
public:
	Interpreter();

	void interpret(std::string code, bool debugOutput);

private:
	Tokenizer tokenizer;
	Parser parser;
	Executer executer;
};


#endif