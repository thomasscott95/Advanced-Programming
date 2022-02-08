#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono> 

using namespace std;

class Manager
{
private:
	static string encyrpt(string);
	int offset = 0;



public:
	Manager();
	string output;
	void createUsernamePassword();
	void logIn();
	char randomChar(int start, int size);
	void randomPasswordGenerator10000();
	void randomPasswordGenerator20000();
	string Cracked(string& encrypted_password, int startInt = 0, int offset = 0);
	//void Cracked();
	void readCrack();
};