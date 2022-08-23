#include "Type.h"

#include <string>


Type::Type(std::string name, std::string def)
{
	this->name = name;
	this->def = def;
}

std::string Type::getName()
{
	return this->name;
}

std::string Type::getDef()
{
	return this->def;
}