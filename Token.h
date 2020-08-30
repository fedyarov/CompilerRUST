#pragma once
#include <string>

using namespace std;

enum token_type 
{
	UNDEFINED,
	NUMBER,
	PLUS,
	MINUS,
	STAR,
	SLASH,
	LPAR, // (
	RPAR, // )
};

class Token
{
	string lexeme;
	token_type type;
public:
	Token(const string& lexeme);

	token_type get_type();
	bool is_integer(const string& lexeme);
};

