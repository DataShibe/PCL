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

bool Utils::in(char chr, vector<string> vec)
{
	for (string i : vec)
		if (i[0] == chr) return true;

	return false;

}

bool Utils::isNumber(string s)
{
	//size_t char_pos(0);
	int char_pos = 0;

	// check the significand
	if (s[char_pos] == '+' || s[char_pos] == '-') char_pos++;

	int n_nm, n_pt;
	for (n_nm = 0, n_pt = 0; isdigit(s[char_pos]) || s[char_pos] == '.'; ++char_pos) {
		s[char_pos] == '.' ? ++n_pt : ++n_nm;
	}
	if (n_pt > 1 || n_nm < 1) return false;

	return char_pos == s.size();
}

bool Utils::isDigit(char input)
{
	vector<char> digits = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };
	return in(input, digits);
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
		output += i.getStr() + " ";

	return Utils::removeLastChar(output);
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