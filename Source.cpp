#include <iostream>
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]) 
{
	char fileName[] = "test.txt";
	Parser parser(fileName);

	create_new_log();

	return 0;
}