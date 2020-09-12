#pragma once
#include <iostream>

using namespace std;

enum class node_type {
	PROG, // HEAD OF TREE
	EXPR, // EXPRESSION
	DCLRT, // DECLARATION

	SEQ, // One statement

	SET, // =

	IF, 
	ELSE,

	FOR,

	VARIABLE,
	NUMBER, 

	MORE, // >
	LESS, // <
	EQUALITY, // ==
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

	Node(node_type type, Node* operand1 = nullptr, Node* operand2 = nullptr, 
		const string value="", Node* operand3 = nullptr, Node* operand4 = nullptr);

	Node* operand1;
	Node* operand2;
	Node* operand3;
	Node* operand4;
};

