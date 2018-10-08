#include <iostream>
#include "infix_parser.h"
using namespace std;


int main()
{

	infix_parser eval;
	eval.eval("1+2*3"); //expression to be evaluated.
	cout << endl;
	eval.eval("2+2^2*3");
	cout << endl;
	eval.eval("1==2");
	cout << endl;
	eval.eval("1+3 > 2");
	cout << endl;
	eval.eval("(4>=4) && 0");
	cout << endl;
	eval.eval("(1+2)*3");
	cout << endl;
	eval.eval("++++2-5*(3^2)");

	int o;
	cin >> o;
	
	



}




