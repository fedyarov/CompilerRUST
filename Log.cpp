#include "Log.h"

void create_new_log()
{
	ofstream log_file(LOG_PATH);
	if (log_file.is_open()) {
		log_file.close();

		cout << "INFO: New log file created successfully" << endl;
	}
}

void cout_log(string message)
{
	ofstream log_file(LOG_PATH, ios::app);
	if (log_file.is_open()) {
		log_file << message;

		log_file.close();
	}
}

void cout_log(int num)
{
	ofstream log_file(LOG_PATH, ios::app);
	if (log_file.is_open()) {
		log_file << num;

		log_file.close();
	}
}

void endl_log()
{
	ofstream log_file(LOG_PATH, ios::app);
	if (log_file.is_open()) {
		log_file << endl;

		log_file.close();
	}
}