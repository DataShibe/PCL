#ifndef TYPE_H
#define TYPE_H

#include <string>


class Type
{
public:
	Type(std::string name, std::string def);

	std::string getName();
	std::string getDef();

private:
	std::string name;
	std::string def;
};


#endif