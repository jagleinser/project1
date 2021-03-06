#include "infix_parser.h"


bool infix_parser::isOperator(char c) {
	size_t found = OPERATORS.find(c);
	return found != std::string::npos;
}

//Validates the expression and tokenizes it.
void infix_parser::tokenize(string mString, vector<string> &tokens) {
	for (int i = 0; i < mString.size(); i++)
	{
		//Check for errors.
		try {
			if (i == 0 && (mString[i] == ')' || mString[i] == ']')) {
				throw "Expession can't start with a closing parenthesis @ char: ";

			}
			if (i == 0 && (mString[i] == '&' || mString[i] == '<' || mString[i] == '>' || mString[i] == '^')) {
				throw "Expression can't start with a binary operator @ char: ";
			}
			if (i >= 2) {
				if (((mString[i] == '&' && mString[i - 1] == '&') || (mString[i] == '|' && mString[i - 1] == '|')) && (mString[i - 2] == '|' || mString[i - 2] == '&')) {
					throw "Two binary operators in a row @ char: ";
				}
				if ((mString[i] == '&' && mString[i - 1] == '|') || mString[i] == '|' && mString[i - 1] == '&') {
					throw "Two binary operators in a row @ char: ";
				}

			}
			if (i >= 2) {
				if ((mString[i] == '<' || mString[i] == '>' || mString[i] == '&' || mString[i] == '|') && ((mString[i - 1] == '+' && mString[i - 2] == '+') || (mString[i - 1] == '-' && mString[i - 2] == '-'))) {
					throw "A unary operand can't be followed by a binary operator @ char: ";
				}
			}
			if (i > 1) {
				if (mString[i - 1] == '/' && mString[i] == '0') {
					throw "Division by zero @ char: ";
				}

			}
			if (i > 2) {
				if ((mString[i] == '1' || mString[i] == '2' || mString[i] == '3' || mString[i] == '4' || mString[i] == '5' || mString[i] == '6' || mString[i] == '7' || mString[i] == '8' || mString[i] == '9' || mString[i] == '0') && (mString[i - 1] == ' ')
					&& (mString[i - 2] == '1' || mString[i - 2] == '2' || mString[i - 2] == '3' || mString[i - 2] == '4' || mString[i - 2] == '5' || mString[i - 2] == '6' || mString[i - 2] == '7' || mString[i - 2] == '8' || mString[i - 2] == '9' || mString[i - 2] == '0')) {
					throw "Two operands in a row @ char: ";
				}
			}
		}
		//If an error is found, print out where and quit the program.
		catch (const char* err)
		{
			cout << err << i << endl;
			std::system("pause");
			exit(0);
		}

		//Otherwise, tokenize
		if (isalnum(mString[i]) && !isalnum(mString[i + 1]))
		{
			tokens.push_back(mString.substr(i, 1));
		}
		else if (isalnum(mString[i]) && isalnum(mString[i + 1]))
		{
			tokens.push_back(mString.substr(i, 2));
			i++;
		}
		else if (isOperator(mString[i]) && !isOperator(mString[i + 1]))
		{
			tokens.push_back(mString.substr(i, 1));
		}
		else if (isOperator(mString[i]) && isOperator(mString[i + 1]))
		{
			tokens.push_back(mString.substr(i, 2));
			i++;
		}
		else if (mString[i] == '(' || mString[i] == ')')
		{
			tokens.push_back(mString.substr(i, 1));
		}

	}
}


void infix_parser::eval(string expression)
{
stack<int> operands;
stack<string> operators;
vector <string> tokens;
tokenize(expression, tokens);

//converts expression into postfix notation 
//using shunting-yard algorithm
//then evaluates that expression

//includes exceptions for single operators such as - ++ -- !

for (int i = 0; i < tokens.size(); i++)
{
	if (isdigit(tokens[i][0]))
	{
		operands.push(stoi(tokens[i])); //stoi converts string to int
	}

	//if single operator - evaluate the digit after and increment i
	//cant process single operators like others because our process 
	//function requires 2 operators
	else if (tokens[i] == "!")
	{
		int val = stoi(tokens[i + 1]);
		operands.push(!val);
		i++;

	}
	else if (tokens[i] == "-" && i == 0)
	{
		operands.push(stoi(tokens[i + 1]) * -1);
		i++;
	}
	else if (tokens[i] == "++")
	{
		if (isdigit(tokens[i + 1][0]))
		{
			operands.push(stoi(tokens[i + 1]) + 1);
			i = i + 1;
		}
		else if (tokens[i + 1] == "++")
		{
			operands.push(stoi(tokens[i + 2]) + 2);
			i = i + 2;
		}

	}
	else if (tokens[i] == "--")
	{
		if (isdigit(tokens[i + 1][0]))
		{
			operands.push(stoi(tokens[i + 1]) - 1);
			i = i + 1;
		}
		else if (tokens[i + 1] == "--")
		{
			operands.push(stoi(tokens[i + 2]) - 2);
			i = i + 2;
		}
	}
	else if (tokens[i] == "(")
	{
		operators.push(tokens[i]);
	}
	else if (tokens[i] == ")")
	{
		while (!operators.empty() && operators.top() != "(")
		{
			//initialize value2 before value1 since stack is reverse of original expression
			int value2 = operands.top();
			operands.pop();
			int value1 = operands.top();
			operands.pop();
			string op = operators.top();

			operands.push(process(value1, value2, op));

			operators.pop();

		}
		operators.pop();
	}
	else
	{
		while (!operators.empty() && getPres(tokens[i]) <= getPres(operators.top()))
		{

			int value2 = operands.top();
			operands.pop();
			int value1 = operands.top();
			operands.pop();

			string op = operators.top();
			operators.pop();

			operands.push(process(value1, value2, op));
		}

		operators.push(tokens[i]);
	}



}

//after the expression has been converted
//evaluates ops left over 
while (!operators.empty())
{
	int value2 = operands.top();
	operands.pop();
	int value1 = operands.top();
	operands.pop();
	string op = operators.top();
	operators.pop();

	operands.push(process(value1, value2, op));

}
cout << expression << " = " << operands.top() << endl;

}
int infix_parser::getPres(string op){ //establishes order of operations


	if (op == "||")
		return 1;
	else if (op == "&&")
		return 2;
	else if (op == "==" || op == "!=")
		return 3;
	else if (op == ">" || op == ">=" || op == "<" || op == "<=")
		return 4;
	else if (op == "+" || op == "-")
		return 5;
	else if (op == "*" || op == "/" || op == "%")
		return 6;
	else if (op == "^")
		return 7;
	else
		return 0;

}
int infix_parser::process(int value1, int value2, string op){

	if (op == "+")
		return value1 + value2;
	else if (op == "-")
		return value1 - value2;
	else if (op == "*")
		return value1 * value2;
	else if (op == "%")
		return value1 % value2;
	else if (op == "/")
		return value1 / value2;
	else if (op == "^")
		return pow(value1, value2);
	else if (op == "<=")
		return value1 <= value2;
	else if (op == "<")
		return value1 < value2;
	else if (op == ">")
		return value1 > value2;
	else if (op == ">=")
		return value1 >= value2;
	else if (op == "&&")
		return value1 == 1 && value2 == 1;
	else if (op == "||")
		return value1 == 1 || value2 == 1;
	else if (op == "==")
		return value1 == value2;
	else if (op == "!=")
		return value1 != value2;

	else
		return 0;
}