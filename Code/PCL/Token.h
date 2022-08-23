#ifndef TOKEN_H
#define TOKEN_H

#include <string>


class Token
{
public:
	Token(int type, std::string str, int line);

	std::string toString();
	std::string getStr();

	int getType();
	int getLine();

private:
	int type;
	int line;

	std::string str;
};


#endif