#include "Variable_table.h"

Variable_table::Variable_table()
{
	vars.clear();
}

Variable_table::~Variable_table()
{
	vars.clear();
}

void Variable_table::add_variable(Variable* var)
{
	vars.push_back(var);
}

Variable* Variable_table::get_variable_by_name(const string& var_name)
{
	for (auto variable : vars) {
		if (variable->get_name() == var_name) {
			return variable;
		}
	}

	throw logic_error("Variable not found");
}

bool Variable_table::has_variable(const string& var_name)
{
	for (auto variable : vars) {
		if (variable->get_name() == var_name) {
			return true;
		}
	}

	return false;
}

size_t Variable_table::size()
{
	return vars.size();
}

void Variable_table::designate_variables_recursive(Node* current_node)
{
	if (current_node == nullptr) {
		return;
	}

	if (current_node->type == node_type::DCLRT) { 
		string name = current_node->operand1->operand1->value;
		Variable* var = new Variable(name, INTEGER);

		vars.push_back(var);
	}

	designate_variables_recursive(current_node->operand1);
	designate_variables_recursive(current_node->operand2);
	designate_variables_recursive(current_node->operand3);
	designate_variables_recursive(current_node->operand4);
}

void Variable_table::print_vars()
{
	cout_log("------ VARIABLES ------");
	endl_log();
	for (auto variable : vars) {
		cout_log("INTEGER ");
		cout_log(variable->get_name());
		endl_log();
	}
}
