#pragma once
#include <string>
#include "iostream"
using namespace std;

class menu {
public:
	menu(string title, bool isProtected) : title_(title), isProtected_(isProtected) {}
	string getTitle();
	virtual void run() = 0;
	bool getProtected() { return isProtected_; }
	bool getAccessGranted() { return isAccessGranted; }
	virtual ~menu() {}
protected:
	string title_;
	string password = "password";
	bool isProtected_;
	bool isAccessGranted = false;
	bool checkPassword();
};