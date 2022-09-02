#ifndef UTILS_H
#define UTILS_H


#include "Token.h"

#include <string>
#include <vector>


namespace Utils
{
	bool in(std::string str, std::vector<std::string> vec);
	bool in(char chr, std::vector<char> vec);
	bool in(char chr, std::vector<std::string> vec);
	bool isNumber(std::string input);
	bool eql(std::vector<int> a, std::vector<int> b);
	bool isDigit(char input);

	std::vector<std::string> split(std::string input, char del);
	std::vector<Token> joinVectors(std::vector<Token> a, std::vector<Token> b);
	std::vector<Token> getFrom(std::vector<Token> a, int n);

	std::string removeLastChar(std::string input);
	std::string getString(std::vector<Token> a);
};


#endif