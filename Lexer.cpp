#include "Lexer.h"

Lexer::Lexer(char* file)
{
	ifstream code(file);
	if (code.is_open()) {
		string line;
		char ch;
		while (!code.eof()) {
			code.get(ch);
			line += ch;
		}
		line[line.size()-1] = EOF;
		cout << "Code have been written to string" << endl;
	}
}
