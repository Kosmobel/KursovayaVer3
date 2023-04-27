#pragma once
#include "node.h"
#include "person.h"
#include <iostream>
#include <sstream>
#include <fstream>

class LinkedList {
public:
	LinkedList() : head(nullptr) {};
	void clear();
	void add(person* p);
	void LoadFromFile(string filename);
	void SaveToFile(string filename);
	int getSize() const;
	Node* head;
};