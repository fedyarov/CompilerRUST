#pragma once
#include <iostream>

using namespace std;

enum node_type {
	PROG, // HEAD OF TREE
	EXPR, // EXPRESSION

	CONSTANT, 
	ADD, // +
	SUB, // -
	MUL, // *
	DIV, // /
};

class Node
{
public:
	string value;
	node_type type;
public:

	Node(node_type type, const string value ="", Node* operand1 = nullptr,
		Node* operand2 = nullptr, Node* operand3 = nullptr, Node* operand4 = nullptr);
	Node(node_type type, Node* operand1 = nullptr, Node* operand2 = nullptr, 
		Node* operand3 = nullptr, Node* operand4 = nullptr);

	Node* operand1;
	Node* operand2;
	Node* operand3;
	Node* operand4;
};

