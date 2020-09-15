#include "Parser.h"

Parser::Parser(const string file_path)
{
	lex = new Lexer(file_path);
	ast = new Ast();
	var_table = new Variable_table();
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

	var_table->designate_variables_recursive(ast->tree); // fill the var_table
	var_table->print_vars(); // Write all vars to the log file
}

Node* Parser::getAst()
{
	return ast->tree;
}

Variable_table* Parser::getVariable_table()
{
	return var_table;
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
	lex->next_token(); // fn
	lex->next_token(); // main
	lex->next_token(); // (
	lex->next_token(); // )
	Node* statement_node = statement();
	return statement_node;
}

Node* Parser::statement()
{
	if (tryEat(token_type::LBRACE)) {
		Node* compound_node = compound_statement();
		return compound_node;
	}
	else if (tryEat(token_type::LET)) {
		Node* declaration_node = declaration();
		return declaration_node;
	}
	else if (tryEat(token_type::IDENTIFIER)) {
		Node* assign_node = set();
		return assign_node;
	}
	else if (tryEat(token_type::IF)) {
		Node* selection_node = selection_statement();
		return selection_node;
	}
	else if (tryEat(token_type::FOR)) {
		Node* cycle_for_node = cycle_for();
		return cycle_for_node;
	}
	else if (tryEat(token_type::PRINTLN)) {
		Node* println_node = println();
		return println_node;
	}
}

Node* Parser::declaration() // Создать таблицу переменных
{
	lex->next_token();
	eat(token_type::MUT);
	lex->next_token();

	Node* set_node = set();

	Node* declaration_node = new Node(node_type::DCLRT, set_node);
	return declaration_node;
}

Node* Parser::set()
{
	Node* identifier_node = identifier();
	
	eat(token_type::SET);
	lex->next_token();

	Node* additive_node = additive_expression();
	Node* set_node = new Node(node_type::SET, identifier_node, additive_node);

	eat(token_type::SEMICOLON);
	lex->next_token();
	
	return set_node;
}

Node* Parser::selection_statement()
{
	lex->next_token();

	Node* expression_node = expression();

	eat(token_type::LBRACE);
	Node* compound_node = compound_statement();

	Node* selection_node = new Node(node_type::IF, expression_node, compound_node);

	if (tryEat(token_type::ELSE)) {
		lex->next_token();

		Node* compound_else_node = compound_statement();
		Node* else_node = new Node(node_type::ELSE, compound_else_node);
		selection_node->operand3 = else_node;
	}

	return selection_node;
}

Node* Parser::cycle_for()
{
	lex->next_token();

	Node* identifier_node = identifier();

	eat(token_type::IN);
	lex->next_token();

	Node* additive_first_node = additive_expression();

	eat(token_type::DOUBLE_POINT);
	lex->next_token();

	Node* additive_second_node = additive_expression();

	eat(token_type::LBRACE);
	Node* compound_node = compound_statement();

	Node* cycle_for_node = new Node(node_type::FOR, identifier_node, additive_first_node,
		"", additive_second_node, compound_node);

	return cycle_for_node;
}

Node* Parser::compound_statement()
{
	lex->next_token();

	Node* statement_node = new Node(node_type::SEQ);
	Node* last_node = statement_node;
	if (!tryEat(token_type::RBRACE)) last_node->operand1 = statement();

	while (!tryEat(token_type::RBRACE)) {

		last_node->operand2 = new Node(node_type::SEQ, statement());

		last_node = last_node->operand2;
	}
	lex->next_token();
	
	return statement_node;
}

Node* Parser::expression()
{
	Node* additive_expression_node = additive_expression();

	if (tryEat(token_type::MORE)) {
		lex->next_token();
		Node* additive_second_node = additive_expression();
		Node* logic_expression_node = new Node(node_type::MORE, additive_expression_node, additive_second_node);
		return logic_expression_node;
	}
	else if (tryEat(token_type::LESS)) {
		lex->next_token();
		Node* additive_second_node = additive_expression();
		Node* logic_expression_node = new Node(node_type::LESS, additive_expression_node, additive_second_node);
		return logic_expression_node;
	}
	else if (tryEat(token_type::EQUALITY)) {
		lex->next_token();
		Node* additive_second_node = additive_expression();
		Node* logic_expression_node = new Node(node_type::EQUALITY, additive_expression_node, additive_second_node);
		return logic_expression_node;
	}

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
	else if (tryEat(token_type::IDENTIFIER)) {
		Node* identifier_node = identifier();

		return identifier_node;
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
	
	Node* additive_node = additive_expression();

	eat(token_type::RPAR);
	lex->next_token();

	return additive_node;
}

Node* Parser::number()
{
	eat(token_type::NUMBER);

	string number_str = lex->current_token()->get_lexeme();
	lex->next_token();

	Node* number_node = new Node(node_type::NUMBER, nullptr, nullptr, number_str);
	return number_node;
}

Node* Parser::identifier()
{
	eat(token_type::IDENTIFIER);

	string variable_str = lex->current_token()->get_lexeme();
	lex->next_token();

	Node* identifier_node = new Node(node_type::VARIABLE, nullptr, nullptr, variable_str);
	return identifier_node;
}

Node* Parser::println()
{
	lex->next_token(); // skip "println!"

	eat(token_type::LPAR);
	lex->next_token();

	eat(token_type::QUOTES);
	lex->next_token();

	eat(token_type::LBRACE);
	lex->next_token();

	eat(token_type::RBRACE);
	lex->next_token();

	eat(token_type::QUOTES);
	lex->next_token();

	eat(token_type::COMMA);
	lex->next_token();

	Node* additive_node = additive_expression();

	eat(token_type::RPAR);
	lex->next_token();

	eat(token_type::SEMICOLON);
	lex->next_token();

	Node* println_node = new Node(node_type::PRINTLN, additive_node);
	return println_node;
}

void Parser::error(const string message)
{
	cout << "PARSE ERROR!" << message << " ";
	cout << "Current token: " << lex->current_token()->get_lexeme() << endl;

	throw logic_error(message);
}
