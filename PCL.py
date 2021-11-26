import sys


class CommandExecutor:
    def __init__(self):
        self.commands = None
        self.calculationMapper = []

    def getType(self, variable):
        # returns the type of a given variable
        for command in self.commands:
            if command.name in ["override", "callOperator"] and command.arguments[1] == variable:
                return command.arguments[0]

    def containsNumber(self, string):
        # returns True if string is a float or int
        return "." in string or string.isdigit()

    def printError(self, message, line):
        print(f"Error on line {line}: {message}".format())
        sys.exit(1)

    def getVarValue(self, variableName, callLine):
        # this is the command, where the variable is created
        creationCommand = None

        for command in self.commands:
            if len(command.arguments) > 1 and command.arguments[1] == variableName:
                creationCommand = command
                creationCommandLine = command.line

        # variable was not found
        if creationCommand is None:
            self.printError(f"Variable with name {variableName} could not be found".format(), callLine + 1)

        returnValue = None

        if creationCommand.name == "override":
            # get the expression from the command 'override'
            expression = creationCommand.arguments[2:]
            cleanExpression = []

            # iterate over the expression
            for expressionIterator in expression:
                # if the iterator is a number or operator, add it to 'cleanExpression'
                if self.containsNumber(expressionIterator) or expressionIterator in ["(", ")", "+", "-", "*", "/", "**"]:
                    cleanExpression.append(expressionIterator)

                else:
                    # add the value of the variable to the expression
                    cleanExpression.append(str(self.getVarValue(expressionIterator, callLine)))

            # join the clean evaluation together and write it into returnValue
            print("Eval: " + " ".join(cleanExpression))
            returnValue = eval(" ".join(cleanExpression))

        elif creationCommand.name == "callOperator":
            mainOperator = creationCommand.arguments[0]
            matchingCalculations = [x for x in self.calculationMapper if x[0] == mainOperator]
            callArguments = creationCommand.arguments[2:]

            # map a type to an argument for later
            typeMapper = {self.getType(x): x for x in callArguments}

            if len(matchingCalculations) == 1:
                term = matchingCalculations[0][1:]
                termClear = []

                counter = 0

                # iterate over the term
                for termIterator in term:
                    # if iterator is a operator add the operator to 'termClear'
                    if termIterator in ["+", "-", "*", "/", "**", "(", ")"]:
                        termClear.append(termIterator)

                    else:
                        # get the value of the variable
                        typeOverload = termIterator

                        try:
                            matchingArgument = creationCommand.arguments[2 + counter]
                        except IndexError:
                            self.printError("Missing arguments", callLine)

                        matchingArgumentEval = self.getVarValue(matchingArgument, creationCommandLine)

                        # write the variable to 'termClear'
                        termClear.append(str(matchingArgumentEval))

                        counter += 1

            # join the clean term together and write it into returnValue
            print("Eval: " + " ".join(termClear))
            returnValue = eval(" ".join(termClear))

        return returnValue

    def execute(self, commands):
        self.commands = commands

        for command in commands:
            if command.name == "calc":
                self.calculationMapper.append(command.arguments)

        for command in commands:
            if command.name == "final":
                finalVariableName = command.arguments
                finalLineIndex = command.line

        return self.getVarValue(finalVariableName, finalLineIndex)


class Command:
    def __init__(self):
        self.name = None
        self.arguments = None
        self.line = None

    def __str__(self):
        # if str(instance of command class) gets called, it returns "name : [arguments]
        return str(self.name) + " : " + str(self.arguments)


class Parser:
    def __init__(self):
        pass

    def parse(self, file):
        lines = file.split("\n")
        commands = []

        counter = 1
        for lineIter in lines:
            # remove empty commands
            line = [x for x in lineIter.split(" ") if x != '']
            # create instance of Command
            command = Command()

            # if command is 'override'
            if len(line) >= 4 and line[2] == "=":
                command.name = "override"
                # set command.arguments to the arguments in line and remove the '='
                command.arguments = [x for x in line if x != "="]

            # if command is 'calc'
            elif len(line) >= 3 and line[0] == "calc":
                command.name = "calc"
                # set command.arguments to the arguments in line and remove the '='
                command.arguments = [x for x in line[1:] if x != ':']

            # if command is call operator
            elif len(line) >= 4 and line[2] == ':':
                command.name = "callOperator"
                # set command.arguments to the arguments in line and remove the ':' and ','
                command.arguments = [x if x[-1] != "," else x[:-1] for x in line if x != ':']

            # if command is final
            elif len(line) == 2 and line[0] == "final":
                command.name = "final"
                command.arguments = line[1]

            # skip empty lines and commands
            if lineIter == "" or lineIter[0] == "#":
                continue

            # skip command with name NONE
            if command.name is None:
                continue

            command.line = counter
            counter += 1

            commands.append(command)

        return commands

    
class Main:
    def __init__(self):
        self.Parser = Parser()
        self.CommandExecutor = CommandExecutor()

    def printIntro(self):
        print("+-------------------------------------------------+")
        print("| Welcome to PCL, a Physics Calculation Language! |")
        print("|                                                 |")
        print("| This Language was written by DataShibe and      |")
        print("|               partially by S1monr3dSt0ne07      |")
        print("+-------------------------------------------------+\n")

    def interpret(self, path):
        self.printIntro()

        # read content of file
        with open(path, "r") as fileStream:
            fileContent = fileStream.read()

        # parse file and get instances of Command back
        tokenStream = self.Parser.parse(fileContent)
        finalValue = self.CommandExecutor.execute(tokenStream)

        print(f"Output: {finalValue}".format())

if __name__ == '__main__':
    systemArgs = sys.argv[1:]
    path = systemArgs[0]

    Main().interpret(path)
