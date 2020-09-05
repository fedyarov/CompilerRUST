#include "Parser.h"

Parser::Parser(const char* file_path)
{
	lex = new Lexer(file_path);
	ast = new Ast();
}

Parser::~Parser()
{
	delete lex;
	delete ast;
}

void Parser::parse()
{
	lex->split(); // Receiving tokens
	lex->print(); // Write tokens to the log file

	ast->tree = program(); // Call Recursive descent parser
	ast->print(); // Write AST to the log file
}

string Parser::eat(token_type type)
{
	if (!tryEat(type)) {
		error(to_string((int)type) + " expected!");
	}

	string value = lex->current_token_value();

	return value;
}

bool Parser::tryEat(token_type type)
{
	return lex->current_token_type() == type;
}

Node* Parser::program()
{
	Node* statement_node = statement();
	return statement_node;
}

Node* Parser::statement()
{
	if (tryEat(token_type::LBRACE)) {
		Node* compound_node = compound_statement();
		return compound_node;
	}
	else{
		Node* expression_node = expression();
		return expression_node;
	}
}

Node* Parser::compound_statement()
{
	lex->next_token();

	Node* statement_node = nullptr;

	while (!tryEat(token_type::RBRACE)) {
		statement_node = new Node(node_type::SEQ, statement());

		if (!tryEat(token_type::RBRACE)) {
			statement_node->operand2 = new Node(node_type::SEQ, statement());
		}
	}
	lex->next_token();
	
	return statement_node;
}

Node* Parser::expression()
{
	Node* additive_expression_node = additive_expression();

	return additive_expression_node;
}

Node* Parser::additive_expression()
{
	Node* multiplicative_node = multiplicative_expression();

	if (tryEat(token_type::PLUS)) {
		lex->next_token();

		Node* additive_temp_node = additive_expression();

		Node* additive = new Node(node_type::ADD, multiplicative_node,
			additive_temp_node);

		return additive;
	}
	else if (tryEat(token_type::MINUS)) { 
		lex->next_token();

		Node* additive_temp_node = additive_expression();

		Node* additive = new Node(node_type::SUB, multiplicative_node,
			additive_temp_node);

		return additive;
	}

	return multiplicative_node;
}

Node* Parser::multiplicative_expression()
{
	Node* primary_node = primary_expression();

	if (tryEat(token_type::STAR)) {
		lex->next_token();

		Node* multiplicative_temp_node = multiplicative_expression();

		Node* multiplicative_expression = new Node(node_type::MUL, primary_node,
			multiplicative_temp_node);

		return multiplicative_expression;
	}
	else if (tryEat(token_type::SLASH)) {
		lex->next_token();

		Node* multiplicative_temp_node = multiplicative_expression();

		Node* multiplicative_expression = new Node(node_type::DIV, primary_node,
			multiplicative_temp_node);

		return multiplicative_expression;
	}
	return primary_node;
}

Node* Parser::primary_expression()
{
	if (tryEat(token_type::NUMBER)) {
		Node* number_node = number();
		
		return number_node;
	}
	else if (tryEat(token_type::LPAR)) {
		Node* parenthesized_expression_node = parenthesized_expression();

		return parenthesized_expression_node;
	}
	
	error("Primary_expression expected");
}

Node* Parser::parenthesized_expression()
{
	eat(token_type::LPAR);
	lex->next_token();
	
	Node* expression_node = expression();

	eat(token_type::RPAR);
	lex->next_token();

	return expression_node;
}

Node* Parser::number()
{
	eat(token_type::NUMBER);

	string number_str = lex->current_token()->get_lexeme();
	lex->next_token();

	Node* number_node = new Node(node_type::CONSTANT, number_str);
	return number_node;
}

void Parser::error(const string message)
{
	cout << "PARSE ERROR!" << message << " ";
	cout << "Current token: " << lex->current_token()->get_lexeme() << endl;

	throw logic_error(message);
}
