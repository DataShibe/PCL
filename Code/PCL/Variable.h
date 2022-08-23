#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>


class Variable
{
public:
	Variable(std::string type, std::string name, float value);

	std::string getName();
	std::string getType();

	
	float getValue();

private:
	std::string type;
	std::string name;

	
	float value;
};


#endif