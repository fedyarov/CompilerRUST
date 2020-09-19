#include <iostream>
#include "Generator.h"

using namespace std;

int main(int argc, char* argv[]) 
{
	string fileName = "Tests/condition_test/Condition.rs";
	Generator generator(fileName);

	create_new_log();

	try {
		generator.Generate();
	}
	catch (const logic_error& error) {
		cout << error.what() << endl;
	}

	return 0;
}