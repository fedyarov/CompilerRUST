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
	return nullptr;
}

Node* Parser::statement()
{
	return nullptr;
}

Node* Parser::expression()
{
	return nullptr;
}

Node* Parser::additive_expression()
{
	return nullptr;
}

Node* Parser::multiplicative_expression()
{
	return nullptr;
}

Node* Parser::primary_expression()
{
	return nullptr;
}

Node* Parser::parenthesized_expression()
{
	return nullptr;
}

Node* Parser::number()
{
	return nullptr;
}

void Parser::error(const string message)
{
	cout << "PARSE ERROR!" << message << " ";
	cout << "Current token: " << lex->current_token()->get_lexeme() << endl;

	throw logic_error(message);
}
