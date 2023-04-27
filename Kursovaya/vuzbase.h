#pragma once
#pragma once
#include "submenu.h"
#include "menuitem.h"
#include "linkedlist.h"
#include "person.h"
#include <iostream>
#include <sstream>
#include <locale>
#include <regex>
#include <limits>
#include <codecvt>



class vuzBase {
public:
	vuzBase();
	void run();
	~vuzBase();
private:
	LinkedList* personList;
	void addPerson();
	void importPerson();
	void showPersonList();
	void printresult(LinkedList* vuzList);
	//void sortById();
	const string personBaseFile = "personbase.csv";
};