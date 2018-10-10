#include <iostream>
#include "infix_parser.h"
using namespace std;


int main()
{

	infix_parser eval;

	eval.eval("++++2-5*(3^2) ");
	eval.eval("1+2*3");
	eval.eval("1==2");
	eval.eval("2+2^2*3");
	eval.eval("1+3 > 2");
	eval.eval("(4>=4) && 0");
	eval.eval("(1+2)*3");
	eval.eval("++++2-5*(3^2)");
	system("pause");
}




