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

Node* Parser::program()
{
	Node* statement_node = statement();
	return statement_node;
}

Node* Parser::statement()
{
	Node* expression_node = expression();
	return expression_node;
}

Node* Parser::expression()
{
	Node* additive_expression_node = additive_expression();
	return additive_expression_node;
}

Node* Parser::additive_expression()
{
	Node* multiplicative_node = multiplicative_expression();

	if (lex->current_token_type() == token_type::PLUS) {
		lex->next_token();

		Node* additive_temp_node = additive_expression();

		Node* additive = new Node(node_type::ADD, multiplicative_node,
			additive_temp_node);

		return additive;
	}
	else if (lex->current_token_type() == token_type::MINUS) {
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

	if (lex->current_token_type() == token_type::STAR) {
		lex->next_token();

		Node* multiplicative_temp_node = multiplicative_expression();

		Node* multiplicative_expression = new Node(node_type::MUL, primary_node,
			multiplicative_temp_node);

		return multiplicative_expression;
	}
	else if (lex->current_token_type() == token_type::SLASH) {
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
	if (lex->current_token_type() == token_type::NUMBER) {
		Node* number_node = number();
		
		return number_node;
	}
	else if (lex->current_token_type() == token_type::LPAR) {
		Node* parenthesized_expression_node = parenthesized_expression();

		return parenthesized_expression_node;
	}
	return nullptr;
}

Node* Parser::parenthesized_expression()
{
	if (lex->current_token_type() != token_type::LPAR) {
		error("'(' expected");
	}
	lex->next_token();

	Node* expression_node = expression();

	if (lex->current_token_type() != token_type::RPAR) {
		error("')' expected");
	}

	lex->next_token();

	return expression_node;
}

Node* Parser::number()
{
	if (lex->current_token_type() != token_type::NUMBER) {
		error("Number expected!");
	}
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
