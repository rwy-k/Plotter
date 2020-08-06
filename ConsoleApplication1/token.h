double expression(double z);
double term(double z);
double primary(double z);
double calculate(double z);

#include "TOKENSTREAM.h"
TokStr ts;
string s;

const double Pi = 3.141592;
const double e = 2.7;

double expression(double z) { // +,-
	double left = term(z);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+': {
			left += term(z);
			t = ts.get();
			break;
		}
		case '-': {
			left -= term(z);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}
double term(double z) { //*,/
	double left = primary(z);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*': {
			left *= primary(z);
			t = ts.get();
			break;
		}
		case '/': {
			double d = primary(z);
			left /= d;
			t = ts.get();
			break;
		}
		case '%': {
			double d = primary(z);
			int i1 = (int)left;
			int i2 = (int)d;
			left = i1 % i2;
			t = ts.get();
			break;
		}
		case '^': {
		double d = primary(z);
		if (fabs(d) < 1) {
			int k = 1 / fabs(d);
			if (k % 2 != 0) {
				if (left < 0) {
					if (d < 0) left = 1 / (-pow(-left, -d));
					else left = - pow(-left, d);
				}
				else {
					if (d < 0) left = 1 / (pow(left, -d));
					else	left = pow(left, d);
				}
			}
			else {
				if (left < 0) {
					left = -100000;
				}
				else {
					if (d < 0) left = 1 / (pow(left, -d));
					else	left = pow(left, d);
				}
			}
		}
		else {
			if (d < 0) left = 1 / (pow(left, -d));
			else	left = pow(left, d);
		}
		t = ts.get();
		break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}
double primary(double z) {//(1234)
	Token t = ts.get();
	switch (t.kind) {
	case '(': {
		double d = expression(z);
		t = ts.get();
		if (t.kind != ')') {
			cout << ("   ')'expected");
			_getch(); exit(2);
		}
		return d;
	}
	case func: {
			Token q = ts.get();
			if (q.kind != '(') {
				cout << "   '()' expected";
				_getch(); exit(2);
			}
			else ts.putback(q);
		double d = primary(z);
		if (t.func == "sin")
		return sin(Pi*d/180);
		if (t.func == "cos")
			return cos(d*Pi/180);
		if (t.func == "tan")
			return tan(d*Pi / 180);
		if (t.func == "ctan")
			return 1/tan(d*Pi / 180);
		if (t.func == "log") {
			if (d < 0)
				return -100000; else return log(d);
		}
		}
			   
	case number: return t.value;
	case 'e': return e;
	case 'x': return z;
	case '-': return -primary(z);
	case '+': return primary(z);
	default: {
		cout << ("  Expression was expected");
		_getch(); exit(2); }
	}
}
double calculate(double z)  {
		ts.Set(s);
		Token t = ts.get();
		while (t.kind == plot) t = ts.get();
		ts.putback(t);
		return expression(z);
	}
	


