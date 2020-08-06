#include <sstream>
#include <math.h>
#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;
const char number = '$'; //signal symbol for a number 
const char plot = ';'; //signal symbol for plotting
const char func = '!'; //signal symbol for a function

class Token {
public:
	char kind;
	double value;
	string func;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string n) :kind(ch), func(n) {}
	~Token() {  }
};

class TokStr {
private:
	bool full;
	Token buffer;
	stringstream ss;
public:
	TokStr() :full(false), buffer(0) {}
	void Set(string f) { ss << f; }
	Token get() {
		if (full) {
			full = false;
			return buffer;
		}
		char ch;
		ss >> ch;

		switch (ch) {
		case plot:
		case '(':
		case ')':
		case '^':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
			{return Token(ch); }
		case '.':
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
			ss.putback(ch); 
			double val;
			ss >> val;
			ss >> ch;
			if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%' || ch == ')' || ch == ';') {
				ss.putback(ch);
				return Token(number, val);
			}
			else {
				cout << ("  ERROR: the operator is omitted after val"); _getch(); exit(2);
			}
			
			break;
		}
		default:
			if (isalpha(ch)) {
				if (ch == 'x') {
					ss.get(ch);
					if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%' || ch == ')' || ch == ';')
					{ 
						ss.putback(ch);
						return Token('x');
					}
					else {
						cout << ("  ERROR: the operator is omitted after var"); _getch(); exit(2);
					}
				}
				if (ch == 'e') return Token('e');
				string s;
				s += ch;
				while (ss.get(ch) && isalpha(ch))
					s += ch;
				ss.putback(ch);
				if (s != "sin" && s != "cos" && s != "tan" && s != "ctan" && s!="log") {

					cout << "   ERROR: it is not a function";
					_getch();  exit(2);
				} else return Token(func, s);
			}
			cout << ("   ERROR: function does not have a feasible description "); _getch(); exit(2);
		}
	}
	void putback(Token t) {
		if (full) cout << ("putback() to full buffer");
		buffer = t;
		full = true;
	}
	~TokStr(){}
};




