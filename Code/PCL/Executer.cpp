#include "Executer.h"
#include "Tokenizer.h"
#include "Error.h"
#include "ExpressionEvaluator.h"
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

float Executer::getVal(vector<char> types, vector<float> values, char type)
{
	for (int i = 0; i < types.size(); i++)
	{
		if (types[i] == type) return values[i];
	}

	return -1;
}

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

			float value = ExpressionEvaluator::evaluate(Utils::getString(Utils::getFrom(command.getArgs(), 2)));

			if (find(typeNameBuffer.begin(), typeNameBuffer.end(), type) != typeNameBuffer.end())
				typeNameBuffer.push_back(type);

			variableBuffer.push_back(Variable(type, name, value));
		}
		else if (command.getType() == CommandTypes::CALC)
		{
			string name = command.getArgs()[0].getStr();
			string def = Utils::getString(Utils::getFrom(command.getArgs(), 1));

			typeBuffer.push_back(Type(name, def));
			typeNameBuffer.push_back(name);
		}
		else if (command.getType() == CommandTypes::CALCVAR)
		{
			string type = command.getArgs()[0].getStr();
			string name = command.getArgs()[1].getStr();
			string vars = Utils::getString(Utils::getFrom(command.getArgs(), 2));

			string def;

			for (Type t : typeBuffer)
				if (t.getName() == type)
					def = t.getDef();

			vector<char> types;
			vector<float> values;
			for (int i = 0; i < def.size(); i++)
			{
				if (def[i] == ' ') continue;
				else types.push_back(def[i]);
			}

			for (int i = 0; i < types.size(); i++)
			{
				values.push_back(0);
			}

			for (Variable v : variableBuffer)
			{
				for (int i = 0; i < types.size(); i++)
				{
					if (v.getType()[0] == types[i]) values[i] = v.getValue();
				}
			}

			string expr = "";

			for (int i = 0; i < def.size(); i++)
			{
				if (!Utils::in(def[i], Tokenizer().operators) && def[i] != ' ')
				{
					expr += to_string(getVal(types, values, def[i]));
					continue;
				}
				expr += def[i];
			}

			variableBuffer.push_back(Variable(type, name, ExpressionEvaluator::evaluate(expr)));
		}
		else if (command.getType() == CommandTypes::FINAL)
		{
			string var = command.getArgs()[0].getStr();

			float value = -69;

			for (Variable variable : variableBuffer)
			{
				if (variable.getName() == var)
					value = variable.getValue();
			}

			if (value == -69) Error::lineError(command.getArgs()[0].getLine(), "Unknown variable: '" + var + "'!");

			cout << value << endl;
		}
	}
}