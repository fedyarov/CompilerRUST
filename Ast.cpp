#include "Ast.h"

Ast::Ast()
{
	tree = nullptr;
}

Ast::~Ast()
{

}

void Ast::descent_recursive(Node* current_node)
{
	if (current_node == nullptr) {
		return;
	}

	descent_recursive(current_node->operand1);
	descent_recursive(current_node->operand2);
	descent_recursive(current_node->operand3);
	descent_recursive(current_node->operand4);
}

void Ast::print_recursive(Node* current_node, size_t level)
{
	if (current_node == nullptr) {
		return;
	}

	for (int i = 0; i < level; ++i) {
		cout_log("  ");
	}

	cout_log("+-");

	switch (current_node->type){
	case node_type::PROG:{
		cout_log("PROG");
		break;
	}
	case node_type::EXPR:{
		cout_log("EXPR");
		break;
	}
	case node_type::CONSTANT:{
		cout_log("CONST ");

		cout_log("(");
		cout_log(current_node->value);
		cout_log(")");
		break;
	}
	case node_type::ADD:{
		cout_log("ADD");
		break;
	}
	case node_type::SUB:{
		cout_log("SUB");
		break;
	}
	case node_type::MUL:{
		cout_log("MUL");
		break;
	}
	case node_type::DIV:{
		cout_log("DIV");
		break;
	}
	}

	endl_log();

	print_recursive(current_node->operand1, level + 1);
	print_recursive(current_node->operand2, level + 1);
	print_recursive(current_node->operand3, level + 1);
	print_recursive(current_node->operand4, level + 1);
}

void Ast::print() {
	print_recursive(tree, 0);
}
