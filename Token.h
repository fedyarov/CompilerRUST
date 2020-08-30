#pragma once
#include <string>

using namespace std;

enum token_type 
{
	UNDEFINED,
	NUMBER, 
	PLUS,	 // +
	MINUS,	 // -
	EQUALLY, // =
	STAR,    // *
	SLASH,   // /
	LPAR,    // (
	RPAR,    // )
	LBRACE,  // {
	RBRACE,  // }
	QUOTES,  // "
	COMMA,   // ,
	MORE,	 // >
	LESS,	 // <
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
};

