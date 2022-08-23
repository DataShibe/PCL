#include "Interpreter.h"
#include "Tokenizer.h"
#include "Executer.h"
#include "Token.h"
#include "Parser.h"
#include "Command.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;


Interpreter::Interpreter() 
{
	this->tokenizer = Tokenizer();
	this->parser = Parser();
	this->executer = Executer();
}

void Interpreter::interpret(string code, bool debugOutput)
{
	vector<Token> tokenList = this->tokenizer.tokenize(code);

	if (debugOutput)
	{
		cout << "==== TOKENS ====\n";
		for (Token token : tokenList)
			cout << token.toString() << endl;
		cout << "================\n\n";
	}

	vector<Command> commandList = this->parser.parse(tokenList);
	
	if (debugOutput)
	{
		cout << "==== COMMANDS ====\n";
		for (Command command : commandList)
			cout << command.toString() << endl;
		cout << "===================\n\n";
	}

	this->executer.execute(commandList);
}