#pragma once
#include <iostream>
#include <vector>
#include "Variable.h"
#include "Node.h"
#include "Log.h"

using namespace std;

class Variable_table
{
	vector<Variable*> vars;
public:
	Variable_table();
	~Variable_table();

	void add_variable(Variable* var);
	Variable* get_variable_by_name(const string& var_name);
	bool has_variable(const string& var_name);

	void designate_variables_recursive(Node* current_node);

	void print_vars();
};

