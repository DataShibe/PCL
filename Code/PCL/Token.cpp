#include "Token.h"

#include <string>

using namespace std;


Token::Token(int type, string str, int line) 
{
	this->type = type;
	this->str = str;
	this->line = line;
}

string Token::toString()
{
	return to_string(this->line) + ":  " + to_string(this->type) + "   " + this->str;
}

string Token::getStr()
{
	return this->str;
}

int Token::getType()
{
	return this->type;
}

int Token::getLine()
{
	return this->line;
}