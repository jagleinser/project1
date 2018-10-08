#include <iostream>
#include "infix_parser.h"
using namespace std;

void check_string(string sent);

int main()
{

	infix_parser eval;
	string sent = "1/0";

	check_string(sent); // validates string

	
	eval.eval(sent); //expression to be evaluated.
	cout << endl;
	system("pause");



}


void check_string(string sent) {

	int index = 0;
	string::iterator it;

	// iterates through the string and finds the errors
	for (it = sent.begin(); it < sent.end(); it++, index++) {
		if (index == 0 && (*it == ')' || *it == ']')) {
			cout << "Expession can't start with a closing parenthesis @ char: " << index;
			break;
		}
		if (index == 0 && (*it == '&' || *it == '<' || *it == '>' || *it == '^')) {
			cout << "Expression can't start with a binary operator @ char: " << index;
			break;
		}
		if (index >= 2) {
			string::iterator prev = it - 1;
			string::iterator sec_prev = it - 2;
			if (((*it == '&' && *prev == '&') || (*it == '|' && *prev == '|')) && (*sec_prev == '|' || *sec_prev == '&')) {
				cout << "Two binary operators in a row @ char: " << index;
				break;
			}
			if ((*it == '&' && *prev == '|') || *it == '|' && *prev == '&') {
				cout << "Two binary operators in a row @ char: " << index;
				break;
			}

		}
		if (index >= 2) {
			string::iterator prev = it - 1;
			string::iterator sec_prev = it - 2;
			if ((*it == '<' || *it == '>' || *it == '&' || *it == '|') && ((*prev == '+' && *sec_prev == '+') || (*prev == '-' && *sec_prev == '-'))) {
				cout << "A unary operand can't be followed by a binary operator @ char: " << index;
				break;
			}
		}
		if (index > 1) {
			string::iterator prev = it - 1;
			if (*prev == '/' && *it == '0') {
				cout << "Division by zero @ char: " << index;
				break;
			}

		}
		if (index > 2) {
			string::iterator prev = it - 1;
			string::iterator sec_prev = it - 2;
			if ((*it == '1' || *it == '2' || *it == '3' || *it == '4' || *it == '5' || *it == '6' || *it == '7' || *it == '8' || *it == '9' || *it == '0') && (*prev == ' ')
				&& (*sec_prev == '1' || *sec_prev == '2' || *sec_prev == '3' || *sec_prev == '4' || *sec_prev == '5' || *sec_prev == '6' || *sec_prev == '7' || *sec_prev == '8' || *sec_prev == '9' || *sec_prev == '0')) {
				cout << "Two operands in a row @ char: " << index;
				break;
			}
		}
		
		
	}
	cout << endl;
	system("pause");
	exit(0);

	
}

