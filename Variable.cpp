#include "Variable.h"

Variable::Variable(const string& variable_name, variable_type var_type)
{
	this->name = variable_name;
	this->type = var_type;
}

Variable::~Variable()
{

}

string Variable::get_name()
{
	return name;
}

variable_type Variable::get_type()
{
	return type;
}