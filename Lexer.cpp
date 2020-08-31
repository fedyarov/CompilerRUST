#include "Lexer.h"

Lexer::Lexer(const char* file)
{
	ifstream file_with_code(file);
	if (file_with_code.is_open()) {
		char ch;
		while (!file_with_code.eof()) {
			file_with_code.get(ch);
			code += ch;
		}
		code[code.size()-1] = EOF;
		cout << "INFO: Code have been written to string" << endl;
	}

	current_token_index = 0;
}

void Lexer::split()
{
	string temp_token;

	for (char symbol : code) {
		if (is_split_symbol(symbol)) {
			if (!temp_token.empty()) {
				Token* new_token = new Token(temp_token);
				tokens.push_back(new_token);

				temp_token.clear();
			}
			if (symbol != ' ' && symbol != 10 && symbol != 9) {
				temp_token = symbol;
				Token* new_token = new Token(temp_token);
				tokens.push_back(new_token);
				temp_token.clear();
			}
		}
		else {
			temp_token += symbol;
		}
	}
}

bool Lexer::is_split_symbol(char symbol)
{
	return symbol == '+' || symbol == '-' ||
		symbol == '/' || symbol == '*' ||
		symbol == '(' || symbol == ')' ||
		symbol == '{' || symbol == '}' ||
		symbol == '\"' || symbol == ',' ||
		symbol == ' ' || symbol == '=' ||
		symbol == '>' || symbol == '<' ||
		symbol == ';' ||
		symbol == 9 || // 9 - Horizontal Tabulation
		symbol == 10; // 10 - Line Feed (enter)
}

void Lexer::print() // Write to log file
{
	for (const auto token : tokens) {
		cout_log(token->get_lexeme());
		cout_log(" WITH TYPE ");
		cout_log(token->get_type());
		endl_log();
		
	}
	cout << "INFO: Token vector writed successfully" << endl;
}

void Lexer::next_token()
{
	if (current_token_index < tokens.size() - 1) {
		current_token_index++;
	}
}

token_type Lexer::current_token_type()
{
	return tokens[current_token_index]->get_type();
}

Token* Lexer::current_token()
{
	return tokens[current_token_index];
}
