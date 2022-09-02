#include "Tokenizer.h"
#include "Token.h"
#include "TokenTypes.h"
#include "Utils.h"

#include <string>
#include <vector>

using namespace std;

Tokenizer::Tokenizer()
{
	this->commands = { "calc", "final" };
	this->operators = { "+", "-", "*", "/", "^", "(", ")" };
	this->ovr = '=';
	this->col = ':';
}

// for the expression evaluator you need to have spaces before and after the brackets
// so this just inserts these
string Tokenizer::prep(string code)
{
	string output = "";
	for (char i : code)
	{
		if (i == ')') output += " ";
		output += i;
		if (i == '(') output += " ";
	}

	return output;
}

vector<Token> Tokenizer::tokenize(string code)
{
	vector<Token> tokenBuffer;

	code = prep(code);

	// this variable is that everything after the 'final' keyword is getting ignored
	bool pastFinal = false;

	vector<string> lines = Utils::split(code, '\n');
	for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++)
	{
		if (pastFinal) break;

		string lineIter = lines[lineIndex];

		// ignore comments
		if (lineIter == "" || lineIter[0] == '#') continue;

		for (string splitLineIter : Utils::split(lineIter, ' '))
		{
			// if the 'word' is a command
			if (Utils::in(splitLineIter, this->commands))
			{
				if (splitLineIter == "final") pastFinal = true;

				// make a new command token
				tokenBuffer.push_back(Token(TokenTypes::COMMAND, splitLineIter, lineIndex));
			}

			// if the 'word' is an operator
			else if (Utils::in(splitLineIter, this->operators))
			{
				tokenBuffer.push_back(Token(TokenTypes::OPERATOR, splitLineIter, lineIndex));
			}

			// if the 'word' is '='
			else if (splitLineIter[0] == ovr)
			{
				tokenBuffer.push_back(Token(TokenTypes::OVR, splitLineIter, lineIndex));
			}

			// if the 'word' is ':'
			else if (splitLineIter[0] == col)
			{
				tokenBuffer.push_back(Token(TokenTypes::COL, splitLineIter, lineIndex));
			}

			// if it's a number (including floating point)
			else if (Utils::isNumber(splitLineIter))
			{
				tokenBuffer.push_back(Token(TokenTypes::VAL, splitLineIter, lineIndex));
			}

			else
			{
				tokenBuffer.push_back(Token(TokenTypes::NAME, splitLineIter, lineIndex));
			}
		}
	}

	return tokenBuffer;
}