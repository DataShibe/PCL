#include "Executer.h"
#include "Command.h"
#include "CommandTypes.h"
#include "Variable.h"
#include "Type.h"
#include "Utils.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


Executer::Executer() {}

void Executer::execute(vector<Command> commandList)
{
	vector<Variable> variableBuffer;
	vector<string> typeNameBuffer;
	vector<Type> typeBuffer;

	for (Command command : commandList)
	{
		if (command.getType() == CommandTypes::OVRVAR)
		{
			string type = command.getArgs()[0].getStr();
			string name = command.getArgs()[1].getStr();
			
			float value = Utils::eval(Utils::getString(Utils::getFrom(command.getArgs(), 2)));

			if (find(typeNameBuffer.begin(), typeNameBuffer.end(), type) != typeNameBuffer.end())
				typeNameBuffer.push_back(type);

			variableBuffer.push_back(Variable(type, name, value));
		}
		else if (command.getType() == CommandTypes::CALC)
		{
			string name = command.getArgs()[0].getStr();
			string def = command.getArgs()[1].getStr() + command.getArgs()[2].getStr() + command.getArgs()[3].getStr();
			
			typeBuffer.push_back(Type(name, def));
			typeNameBuffer.push_back(name);
		}
		else if (command.getType() == CommandTypes::CALCVAR)
		{
			string type = command.getArgs()[0].getStr();
			string name = command.getArgs()[1].getStr();
			string var1 = command.getArgs()[2].getStr();
			string var2 = command.getArgs()[3].getStr();

			string def;

			for (Type t : typeBuffer)
				if (t.getName() == type)
					def = t.getDef();

			char t1 = def[0];
			char op = def[1];
			char t2 = def[2];

			float t1Val = 0;
			float t2Val = 0;

			for (Variable v : variableBuffer)
			{
				if (v.getType()[0] == t1) t1Val = v.getValue();
				if (v.getType()[0] == t2) t2Val = v.getValue();
			}

			variableBuffer.push_back(Variable(type, name, Utils::eval(to_string(t1Val) + op + to_string(t2Val))));
		}
		else if (command.getType() == CommandTypes::FINAL)
		{
			string var = command.getArgs()[0].getStr();
			
			float value = 0;

			for (Variable variable : variableBuffer)
			{
				if (variable.getName() == var)
					value = variable.getValue();
			}

			cout << value << endl;
		}
	}
}