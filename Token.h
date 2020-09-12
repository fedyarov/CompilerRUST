#pragma once
#include <string>
#include <iostream>

using namespace std;

enum class token_type 
{
	IDENTIFIER,

	LET,
	MUT,

	NUMBER,

	TRUE,
	FALSE,

	IF,
	ELSE,

	FOR, // for
	IN, // in
	DOUBLE_POINT, // ..

	SET, // =
	EQUALITY, // ==

	PLUS,	 // +
	MINUS,	 // -
	STAR,    // *
	SLASH,   // /

	LPAR,    // (
	RPAR,    // )
	LBRACE,  // {
	RBRACE,  // }

	QUOTES,  // "
	COMMA,   // ,
	SEMICOLON, // ;

	MORE,	 // >
	LESS,	 // <
	OR,      // |
	AND,     // &

	PRINTLN,
};

class Token
{
	string lexeme;
	token_type type;
public:
	Token(const string& lexeme);

	token_type get_type();
	string get_lexeme();

	bool is_integer(const string& lexeme);
	bool is_correct_identifier(const string& lexeme);
};

