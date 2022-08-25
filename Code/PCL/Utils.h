#ifndef UTILS_H
#define UTILS_H


#include "Token.h"

#include <string>
#include <vector>


class Utils
{
public:
	static bool in(std::string str, std::vector<std::string> vec);
	static bool in(char chr, std::vector<char> vec);
	static bool in(char chr, std::vector<std::string> vec);
	static bool isNumber(std::string input);
	static bool eql(std::vector<int> a, std::vector<int> b);
	static bool isDigit(char input);

	static std::vector<std::string> split(std::string input, char del);
	static std::vector<Token> joinVectors(std::vector<Token> a, std::vector<Token> b);
	static std::vector<Token> getFrom(std::vector<Token> a, int n);

	static std::string removeLastChar(std::string input);
	static std::string getString(std::vector<Token> a);
};


#endif