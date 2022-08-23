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

	vector<Token> tokenBuffer = tokenList;

	while (!tokenBuffer.empty())
	{
		if (tokenBuffer[0].getType() == TokenTypes::COMMAND && tokenBuffer[0].getStr() == "final")
		{
			Token val = tokenBuffer[1];

			commandBuffer.push_back(Command(CommandTypes::FINAL, { val }));
	
			tokenBuffer.erase(tokenBuffer.begin(), tokenBuffer.begin() + 2);
		}
		else if (Utils::eql(getTypes(tokenBuffer, 4), {TokenTypes::NAME, TokenTypes::NAME, TokenTypes::OVR, TokenTypes::VAL}))
		{
			cout << tokenBuffer[0].getLine() << endl;

			Token type = tokenBuffer[0];
			Token name = tokenBuffer[1];
			
			vector<Token> val = Parser::getUntilNextLine(tokenBuffer[0].getLine(), tokenBuffer, 3);
			vector<Token> temp = { type, name };

			commandBuffer.push_back(Command(CommandTypes::OVRVAR, Utils::joinVectors(temp, val)));

			tokenBuffer.erase(tokenBuffer.begin(), tokenBuffer.begin() + 3 + val.size());
		}
		else if (Utils::eql(getTypes(tokenBuffer, 5), { TokenTypes::NAME, TokenTypes::NAME, TokenTypes::COL, TokenTypes::NAME, TokenTypes::NAME }))
		{
			Token type = tokenBuffer[0];
			Token var = tokenBuffer[1];
			Token type1 = Token(tokenBuffer[3].getType(), Utils::removeLastChar(tokenBuffer[3].getStr()), tokenBuffer[3].getLine());
			Token type2 = tokenBuffer[4];

			commandBuffer.push_back(Command(CommandTypes::CALCVAR, { type, var, type1, type2 }));

			tokenBuffer.erase(tokenBuffer.begin(), tokenBuffer.begin() + 5);
		}
		else if (tokenBuffer[0].getType() == TokenTypes::COMMAND && tokenBuffer[0].getStr() == "calc")
		{
			Token resType = tokenBuffer[1];
			Token type1 = tokenBuffer[3];
			Token op = tokenBuffer[4];
			Token type2 = tokenBuffer[5];

			commandBuffer.push_back(Command(CommandTypes::CALC, { resType, type1, op, type2 }));

			tokenBuffer.erase(tokenBuffer.begin(), tokenBuffer.begin() + 6);
		}
		else
		{
			Error::lineError(tokenBuffer[0].getLine() + 1, "Syntax error!");
		}
	}

	return commandBuffer;
}

vector<int> Parser::getTypes(vector<Token> tokenList, int n)
{
	vector<int> output;
	
	for (int i = 0; i < n; i++)
		output.push_back(tokenList[i].getType());

	return output;
}

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