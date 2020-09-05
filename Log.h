#pragma once
#include <fstream>
#include <iostream>

#define LOG_PATH "Log/log.txt"

using namespace std;

void create_new_log();

void cout_log(string message);
void cout_log(int num);

void endl_log();