#pragma once
#include <iostream>

using namespace std;

enum variable_type {
	INTEGER = 0x001000,
};

class Variable
{
	string name;
	variable_type type;
public:
	Variable(const string& variable_name, variable_type var_type);
	~Variable();

	string get_name();
	variable_type get_type();
};

