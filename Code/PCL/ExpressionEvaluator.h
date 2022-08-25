#ifndef EXPREVAL_H
#define EXPREVAL_H


#include <string>
#include <vector>


class ExpressionEvaluator
{
public:
	static float evaluate(std::string tokens);

private:
	static int precedence(char op);

	static float applyOp(float a, float b, char op);

	static std::vector<std::string> split(std::string input, char del);
};


#endif