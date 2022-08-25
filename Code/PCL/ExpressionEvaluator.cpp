#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include "ExpressionEvaluator.h"
#include "Utils.h"

using namespace std;

vector<string> ExpressionEvaluator::split(string tokens, char del)
{
	vector<string> output;
	string temp = "";

	for (char i : tokens)
	{
		if (i == del)
		{
			output.push_back(temp);
			temp = "";
			continue;
		}
		temp += i;
	}

	output.push_back(temp);

	return output;
}

int ExpressionEvaluator::precedence(char op) {
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}

float ExpressionEvaluator::applyOp(float a, float b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	}
}

float ExpressionEvaluator::evaluate(string tokens) {
	stack<float> values;
	stack<char> ops;

	vector<string> parts = split(tokens, ' ');

	for (int i = 0; i < parts.size(); i++) {
		if (parts[i] == "")
			continue;

		else if (parts[i] == " ")
			continue;

		else if (parts[i] == "(") {
			ops.push(parts[i][0]);
		}

		else if (Utils::isNumber(parts[i])) {
			values.push(stof(parts[i]));
			//		i--;
		}
		else if (parts[i] == ")")
		{
			while (!ops.empty() && ops.top() != '(')
			{
				float val2 = values.top();
				values.pop();

				float val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}
			if (!ops.empty())
				ops.pop();
		}
		else
		{
			while (!ops.empty() && precedence(ops.top()) >= precedence(parts[i][0])) {
				float val2 = values.top();
				values.pop();

				float val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			ops.push(parts[i][0]);
		}
	}
	while (!ops.empty()) {
		float val2 = values.top();
		values.pop();

		float val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}

	return values.top();
}