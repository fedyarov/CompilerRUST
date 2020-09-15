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
	Variable_table* var_table;
public:
	Parser(const string file_path);
	~Parser();

	void parse();
	Node* getAst();
	Variable_table* getVariable_table();
	string eat(token_type type);
	bool tryEat(token_type type);

	Node* program();
	Node* statement();
	Node* declaration();
	Node* set();
	Node* compound_statement();
	Node* selection_statement();
	Node* cycle_for();
	Node* expression();
	Node* additive_expression();
	Node* multiplicative_expression();
	Node* primary_expression();
	Node* parenthesized_expression();
	Node* number();
	Node* identifier();
	Node* println();

	void error(const string message);
};

