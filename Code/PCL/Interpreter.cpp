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
	// tokenize the code
	vector<Token> tokenList = this->tokenizer.tokenize(code);

	// output the tokens
	if (debugOutput)
	{
		cout << "==== TOKENS ====\n";

		for (Token token : tokenList)
			cout << token.toString() << endl;

		cout << "================\n\n";
	}

	// parse the tokens
	vector<Command> commandList = this->parser.parse(tokenList);

	// output the commands
	if (debugOutput)
	{
		cout << "==== COMMANDS ====\n";

		for (Command command : commandList)
			cout << command.toString() << endl;

		cout << "===================\n\n";
	}

	// execute the commands
	this->executer.execute(commandList);
}