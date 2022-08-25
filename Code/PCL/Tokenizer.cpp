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

	bool pastFinal = false;

	vector<string> lines = Utils::split(code, '\n');
	for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++)
	{
		if (pastFinal) break;

		string lineIter = lines[lineIndex];

		if (lineIter == "" || lineIter[0] == '#') continue;

		for (string splitLineIter : Utils::split(lineIter, ' '))
		{

			if (Utils::in(splitLineIter, this->commands))
			{
				if (splitLineIter == "final") pastFinal = true;

				tokenBuffer.push_back(Token(TokenTypes::COMMAND, splitLineIter, lineIndex));
			}
			else if (Utils::in(splitLineIter, this->operators))
			{
				tokenBuffer.push_back(Token(TokenTypes::OPERATOR, splitLineIter, lineIndex));
			}
			else if (splitLineIter[0] == ovr)
			{
				tokenBuffer.push_back(Token(TokenTypes::OVR, splitLineIter, lineIndex));
			}
			else if (splitLineIter[0] == col)
			{
				tokenBuffer.push_back(Token(TokenTypes::COL, splitLineIter, lineIndex));
			}
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