#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.h"
#include "Log.h"

using namespace std;

class Lexer
{
	string code;
	vector<Token*> tokens;
public:
	Lexer(char* file);

	void split();
	bool is_split_symbol(char symbol);

	void print();
};

