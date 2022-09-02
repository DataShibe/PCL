#include "Utils.h"
#include "Token.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;


namespace Utils
{
	bool in(string str, vector<string> vec)
	{
		for (string i : vec)
			if (i == str) return true;

		return false;
	}

	bool in(char chr, vector<char> vec)
	{
		for (char i : vec)
			if (i == chr) return true;

		return false;
	}

	bool in(char chr, vector<string> vec)
	{
		for (string i : vec)
			if (i[0] == chr) return true;

		return false;

	}

	bool isNumber(string input)
	{
		int charPosition = 0;

		if (input[charPosition] == '+' || input[charPosition] == '-') charPosition++;

		int nNm, nPt;
		for (nNm = 0, nPt = 0; isDigit(input[charPosition]) || input[charPosition] == '.'; charPosition++) {
			input[charPosition] == '.' ? nPt++ : nNm++;
		}
		if (nPt > 1 || nNm < 1) return false;

		return charPosition == input.size();
	}

	bool isDigit(char input)
	{
		vector<char> digits = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };
		return in(input, digits);
	}

	bool eql(vector<int> a, vector<int> b)
	{
		return a == b;
	}

	vector<string> split(string input, char del)
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

	string removeLastChar(string input)
	{
		string output = "";

		for (int i = 0; i < input.length() - 1; i++)
			output += input[i];

		return output;
	}

	string getString(vector<Token> a)
	{
		string output = "";
		for (Token i : a)
			output += i.getStr() + " ";

		return removeLastChar(output);
	}

	vector<Token> joinVectors(vector<Token> a, vector<Token> b)
	{
		vector<Token> output;
		for (Token t : a) output.push_back(t);
		for (Token t : b) output.push_back(t);

		return output;
	}

	vector<Token> getFrom(vector<Token> a, int n)
	{
		vector<Token> output;
		for (int i = n; i < a.size(); i++) output.push_back(a[i]);

		return output;
	}

}