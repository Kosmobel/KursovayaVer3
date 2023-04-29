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
	void exportPerson();

	//сортировки
	void sortById(LinkedList* vuzList);
	void sortByAge(LinkedList* vuzList);
	void sortByName(LinkedList* vuzList);
	void sortByType(LinkedList* vuzList);

	//функции поиска
	void findById(LinkedList* vuzList);
	void findByAge(LinkedList* vuzList);
	void findByName(LinkedList* vuzList);
	void findByType(LinkedList* vuzList);

	//функции удаления
	void removeById(LinkedList* vuzList);
	void removeByAge(LinkedList* vuzList);
	void removeByName(LinkedList* vuzList);
	void removeByType(LinkedList* vuzList);


	const string personBaseFile = "personbase.csv";
};