#include "Utils.h"
#include "Token.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;


bool Utils::in(string str, vector<string> vec)
{
	for (string i : vec)
		if (i == str) return true;

	return false;
}

bool Utils::in(char chr, vector<char> vec)
{
	for (char i : vec)
		if (i == chr) return true;

	return false;
}

bool Utils::isNumber(string input)
{
	vector<char> digits = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' , '.'};
	for (char i : input)
		if (!Utils::in(i, digits)) return false;

	return true;

}

bool Utils::eql(vector<int> a, vector<int> b)
{
	return a == b;
}

vector<string> Utils::split(string input, char del)
{
	vector<string> output;
	string buffer = "";

	for (char letter : input)
	{
		if (letter == del)
		{
			output.push_back(buffer);
			buffer = "";
			continue;
		}
		buffer += letter;
	}

	output.push_back(buffer);
	return output;
}

string Utils::removeLastChar(string input)
{
	string output = "";

	for (int i = 0; i < input.length() - 1; i++)
		output += input[i];

	return output;
}

string Utils::getString(vector<Token> a)
{
	string output = "";
	for (Token i : a)
		output += i.getStr();

	return output;
}


float Utils::eval(string expr)
{
	cout << expr << endl;

	vector<char> operators = { '+', '-', '*', '/', '^' };

	char op = ';';
	float v1;
	float v2;

	for (char letter : expr)
		if (Utils::in(letter, operators))
			op = letter;

	if (op == ';') return stof(expr);

	vector<string> parts = Utils::split(expr, op);

	v1 = stof(parts[0]);
	v2 = stof(parts[1]);

	float res = 0;

	switch (op)
	{
	case '+':
		res = v1 + v2;
		break;
	case '-':
		res = v1 - v2;
		break;
	case '*':
		res = v1 * v2;
		break;
	case '/':
		res = v1 / v2;
		break;
	case '^':
		res = pow(v1, v2);
	}

	return res;
}

vector<Token> Utils::joinVectors(vector<Token> a, vector<Token> b)
{
	vector<Token> output;
	for (Token t : a) output.push_back(t);
	for (Token t : b) output.push_back(t);

	return output;
}

vector<Token> Utils::getFrom(vector<Token> a, int n)
{
	vector<Token> output;
	for (int i = n; i < a.size(); i++) output.push_back(a[i]);

	return output;
}