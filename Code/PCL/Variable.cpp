#include "Variable.h"

#include <string>


Variable::Variable(std::string type, std::string name, float value)
{
	this->type = type;
	this->name = name;
	this->value = value;
}

std::string Variable::getName()
{
	return this->name;
}

std::string Variable::getType()
{
	return this->type;
}

float Variable::getValue()
{
	return this->value;
}