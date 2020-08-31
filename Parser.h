#pragma once
#include <iostream>
#include "Lexer.h"
#include "Node.h"
#include "Ast.h"
#include "Log.h"

using namespace std;

class Parser
{
	Lexer* lex;
	Ast* ast;
public:
	Parser(const char* file_path);
	~Parser();

	void parse();

	Node* program();
	Node* statement();
	Node* expression();
	Node* additive_expression();
	Node* multiplicative_expression();
	Node* primary_expression();
	Node* parenthesized_expression();
	Node* number();

	void error(const string message);
};

