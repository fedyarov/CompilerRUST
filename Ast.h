#pragma once
#include "Node.h"
#include "Log.h"
#include "Variable_table.h"

class Ast
{
public:
	Node* tree;
public:
	Ast();
	~Ast();

	void descent_recursive(Node* current_node);
	void print_recursive(Node* current_node, size_t level);
	void print();
};

