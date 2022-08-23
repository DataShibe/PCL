#ifndef ERROR_H
#define ERROR_H


#include <string>


class Error
{
public:
	static void lineError(int line, std::string message);
};


#endif