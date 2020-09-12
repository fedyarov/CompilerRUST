#pragma once
#include <fstream>
#include <iostream>
#include "Token.h"

#define LOG_PATH "Log/log.txt"

using namespace std;

void create_new_log();

void cout_log(string message);
void cout_log(token_type type);

void endl_log();