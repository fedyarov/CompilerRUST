#include <iostream>
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]) 
{
	char fileName[] = "Tests/test2.txt";
	Parser parser(fileName);
	
	create_new_log();

	try {
		parser.parse();
	}
	catch (const logic_error& error) {
		cout << error.what() << endl;
	}

	return 0;
}