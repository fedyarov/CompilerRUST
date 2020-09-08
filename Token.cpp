#include "Token.h"

Token::Token(const string& lexeme)
{
	this->lexeme = lexeme;

	this->type = get_type();
}

token_type Token::get_type()
{
	if (lexeme == "let") {
		return token_type::LET;
	}
	if (lexeme == "mut") {
		return token_type::MUT;
	}
	if (is_integer(lexeme)) {
		return token_type::NUMBER_TOKEN;
	}
	if (lexeme == "true") {
		return token_type::TRUE;
	}
	if (lexeme == "false") {
		return token_type::FALSE;
	}
	if (lexeme == "if") {
		return token_type::IF_TOKEN;
	}
	if (lexeme == "else") {
		return token_type::ELSE_TOKEN;
	}
	if (lexeme == "for") {
		return token_type::FOR_TOKEN;
	}
	if (lexeme == "=") {
		return token_type::EQUALLY;
	}
	if (lexeme == "+") {
		return token_type::PLUS;
	}
	if (lexeme == "-") {
		return token_type::MINUS;
	}
	if (lexeme == "*") {
		return token_type::STAR;
	}
	if (lexeme == "/") {
		return token_type::SLASH;
	}
	if (lexeme == "(") {
		return token_type::LPAR;
	}
	if (lexeme == ")") {
		return token_type::RPAR;
	}
	if (lexeme == "{") {
		return token_type::LBRACE;
	}
	if (lexeme == "}") {
		return token_type::RBRACE;
	}
	if (lexeme == "\"") {
		return token_type::QUOTES;
	}
	if (lexeme == ",") {
		return token_type::COMMA;
	}
	if (lexeme == ";") {
		return token_type::SEMICOLON;
	}
	if (lexeme == ">") {
		return token_type::MORE;
	}
	if (lexeme == "<") {
		return token_type::LESS;
	}
	if (lexeme == "|") {
		return token_type::OR;
	}
	if (lexeme == "&") {
		return token_type::AND;
	}
	if (lexeme == "println!") {
		return token_type::PRINTLN;
	}

	if (is_correct_identifier(lexeme)) {
		return token_type::IDENTIFIER;
	}
	else {
		throw logic_error("Lexical error! Incorrect identifier " + lexeme + " !");
	}
}

bool Token::is_integer(const string& lexeme)
{
	for (const auto symbol : lexeme) {
		if (symbol < '0' || symbol > '9') {
			return false;
		}
	}
	return true;
}

bool Token::is_correct_identifier(const string& lexeme)
{
	if (!isalpha(lexeme[0]) && lexeme[0] != '_') {
		return false;
	}

	for (const auto& symbol : lexeme) {
		if (!isalpha(symbol) && !isdigit(symbol) && symbol != '_') {
			return false;
		}
	}

	return true;
}

string Token::get_lexeme()
{
	return this->lexeme;
}