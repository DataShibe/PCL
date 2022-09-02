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

// this function returns the first value of the variable that has the same type as given 
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
		// overriding a variable
		if (command.getType() == CommandTypes::OVRVAR)
		{
			string type = command.getArgs()[0].getStr();
			string name = command.getArgs()[1].getStr();

			// evaluate the expression
			float value = ExpressionEvaluator::evaluate(Utils::getString(Utils::getFrom(command.getArgs(), 2)));

			// if the type of the variable is not already existing, make a new one
			if (find(typeNameBuffer.begin(), typeNameBuffer.end(), type) != typeNameBuffer.end())
				typeNameBuffer.push_back(type);

			// make a new variable
			variableBuffer.push_back(Variable(type, name, value));
		}
		// calculating a type
		else if (command.getType() == CommandTypes::CALC)
		{
			string name = command.getArgs()[0].getStr();
			string def = Utils::getString(Utils::getFrom(command.getArgs(), 1));

			// the type defined in the calc command cannot be predefined in the program
			// so we can add it onto the typebuffer without needing to check if it's already existint
			typeBuffer.push_back(Type(name, def));
			typeNameBuffer.push_back(name);
		}
		// calculating a variable with the calc definition
		else if (command.getType() == CommandTypes::CALCVAR)
		{
			string type = command.getArgs()[0].getStr();
			string name = command.getArgs()[1].getStr();
			string vars = Utils::getString(Utils::getFrom(command.getArgs(), 2));

			// get the definition of the type variable
			string def;
			for (Type t : typeBuffer)
				if (t.getName() == type)
					def = t.getDef();

			// get all the types in the expression
			vector<char> types;
			vector<float> values;
			for (int i = 0; i < def.size(); i++)
			{
				if (def[i] == ' ') continue;
				else types.push_back(def[i]);
			}

			// override the values vector with 0's
			for (int i = 0; i < types.size(); i++)
			{
				values.push_back(0);
			}

			// go over every variable and check if it's type corresponds to the type we have and get the value
			for (Variable v : variableBuffer)
			{
				for (int i = 0; i < types.size(); i++)
				{
					if (v.getType()[0] == types[i]) values[i] = v.getValue();
				}
			}

			// build the expression with the values we extracted from the types
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

			// make a new variable with the result of the expression
			variableBuffer.push_back(Variable(type, name, ExpressionEvaluator::evaluate(expr)));
		}
		// final command
		else if (command.getType() == CommandTypes::FINAL)
		{
			string var = command.getArgs()[0].getStr();

			// get the value of the variable to print
			float value = -69;
			for (Variable variable : variableBuffer)
			{
				if (variable.getName() == var)
					value = variable.getValue();
			}

			// error if the value is not found
			if (value == -69) Error::lineError(command.getArgs()[0].getLine(), "Unknown variable: '" + var + "'!");

			cout << value << endl;
		}
	}
}