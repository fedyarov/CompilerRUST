#include <iostream>
#include "Token.h"
#include "Lexer.h"

using namespace std;

int main(int argc, char* argv[]) 
{
	char fileName[] = "test.txt";
	Lexer lexer(fileName);

	create_new_log();

	lexer.split();
	lexer.print();

	return 0;
}