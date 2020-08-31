#include "Node.h"

Node::Node(node_type type, const string value = "", Node* operand1 = nullptr,
	Node* operand2 = nullptr, Node* operand3 = nullptr, Node* operand4 = nullptr)
{
	this->type = type;
	this->value = value;
	this->operand1 = operand1;
	this->operand2 = operand2;
	this->operand3 = operand3;
	this->operand4 = operand4;
}
