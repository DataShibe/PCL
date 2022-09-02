#include "Parser.h"
#include "Command.h"
#include "Token.h"
#include "TokenTypes.h"
#include "CommandTypes.h"
#include "Utils.h"
#include "Error.h"

#include <vector>
#include <iostream>

using namespace std;


Parser::Parser() {}

vector<Command> Parser::parse(vector<Token> tokenList)
{
	vector<Command> commandBuffer;
	// make a copy because we don't want the original to be modified
	vector<Token> tokenBuffer = tokenList;

	while (!tokenBuffer.empty())
	{
		// if the token is final
		if (tokenBuffer[0].getType() == TokenTypes::COMMAND && tokenBuffer[0].getStr() == "final")
		{
			// the second token is the variable that we want to print
			Token val = tokenBuffer[1];

			// create a new command with the type final and the value as argument
			commandBuffer.push_back(Command(CommandTypes::FINAL, { val }));

			// erase all the tokens in this line
			tokenBuffer = eraseUntilNextLine(tokenBuffer[0].getLine(), tokenBuffer);
		}

		// if the tokens are for overriding a variable
		else if (Utils::eql(getTypes(tokenBuffer, 3), { TokenTypes::NAME, TokenTypes::NAME, TokenTypes::OVR }))
		{
			Token type = tokenBuffer[0];
			Token name = tokenBuffer[1];

			// get all the arguments
			vector<Token> val = Parser::getUntilNextLine(tokenBuffer[0].getLine(), tokenBuffer, 3);
			vector<Token> temp = { type, name };

			// create a new command with the type "override variable" and give it the arguments
			commandBuffer.push_back(Command(CommandTypes::OVRVAR, Utils::joinVectors(temp, val)));

			// erase all the tokens in this line
			tokenBuffer = eraseUntilNextLine(tokenBuffer[0].getLine(), tokenBuffer);
		}

		// if the tokens are for calculating a type
		else if (Utils::eql(getTypes(tokenBuffer, 3), { TokenTypes::NAME, TokenTypes::NAME, TokenTypes::COL }))
		{
			Token type = tokenBuffer[0];
			Token var = tokenBuffer[1];

			// get all the arguments
			vector<Token> types = Parser::getUntilNextLine(tokenBuffer[0].getLine(), tokenBuffer, 2);
			vector<Token> temp = { type, var };

			// create a new command
			commandBuffer.push_back(Command(CommandTypes::CALCVAR, Utils::joinVectors(temp, types)));

			// erase all the stuff in this line
			tokenBuffer = eraseUntilNextLine(tokenBuffer[0].getLine(), tokenBuffer);
		}

		// if the tokens are for calculating
		else if (tokenBuffer[0].getType() == TokenTypes::COMMAND && tokenBuffer[0].getStr() == "calc")
		{

			// same stuff as before just look at the lines above
			Token resType = tokenBuffer[1];

			vector<Token> args = Parser::getUntilNextLine(tokenBuffer[0].getLine(), tokenBuffer, 3);
			vector<Token> temp = { resType };

			commandBuffer.push_back(Command(CommandTypes::CALC, Utils::joinVectors(temp, args)));

			tokenBuffer = eraseUntilNextLine(tokenBuffer[0].getLine(), tokenBuffer);
		}
		else
		{
			Error::lineError(tokenBuffer[0].getLine() + 1, "Syntax error!");
		}
	}

	return commandBuffer;
}

// get all the tokens from the beginning of the tokenList to the n'th index
vector<int> Parser::getTypes(vector<Token> tokenList, int n)
{
	vector<int> output;

	for (int i = 0; i < n; i++)
		output.push_back(tokenList[i].getType());

	return output;
}

// this gets all the tokens in one line with the offset of startingIndex
vector<Token> Parser::getUntilNextLine(int line, vector<Token> tokenBuffer, int startingIndex)
{
	vector<Token> output;

	for (int i = startingIndex; i < tokenBuffer.size(); i++)
	{
		Token t = tokenBuffer[i];

		if (t.getLine() != line) return output;

		output.push_back(t);
	}

	return output;
}

// does what it says: erases all the tokens that are within the same line
vector<Token> Parser::eraseUntilNextLine(int line, vector<Token> tokenBuffer)
{
	while (!tokenBuffer.empty() && tokenBuffer[0].getLine() == line)
		tokenBuffer.erase(tokenBuffer.begin(), tokenBuffer.begin() + 1);

	return tokenBuffer;
}