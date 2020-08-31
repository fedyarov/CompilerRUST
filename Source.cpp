#include <iostream>
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]) 
{
	char fileName[] = "AST_test.txt";
	Parser parser(fileName);

	create_new_log();

	parser.parse();

	return 0;
}