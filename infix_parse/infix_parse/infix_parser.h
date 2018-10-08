#pragma once
#ifndef INFIX_PARSER
#define INFIX_PARSER
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
class infix_parser {
public:
	infix_parser() { mstring = "EMPTY EXPRESSION"; }
	~infix_parser(){}
	bool isOperator(char c); 
	void tokenize(string m, vector<string> &mVector); 
	void eval(string expression);
	int getPres(string op);
	int process(int value1, int value2, string op);
	string OPERATORS = "!++--^*/%+>=<===!=&&||";

private:
	string mstring;

};

#endif