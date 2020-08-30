#include "Token.h"

Token::Token(const string& lexeme)
{
	this->lexeme = lexeme;

	this->type = get_type();
}

token_type Token::get_type()
{
	if (is_integer(lexeme)) {
		return token_type::NUMBER;
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
		return token_type::RPAR;
	}
	if (lexeme == ")") {
		return token_type::RPAR;
	}
	return token_type::UNDEFINED;
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

string Token::get_lexeme()
{
	return this->lexeme;
}