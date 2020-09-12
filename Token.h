#pragma once
#include <string>
#include <iostream>

using namespace std;

enum token_type 
{
	IDENTIFIER,

	LET,
	MUT,

	NUMBER_TOKEN,

	TRUE,
	FALSE,

	IF_TOKEN,
	ELSE_TOKEN,

	FOR_TOKEN, // for
	IN, // in
	DOUBLE_POINT, // ..

	SET_TOKEN, // =
	EQUALITY_TOKEN, // ==

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

	MORE_TOKEN,	 // >
	LESS_TOKEN,	 // <
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

