#pragma once
#include "person.h"

class Node {
public:
	person* data;
	Node* next;
	Node(person* p) : data(p), next(nullptr) {}
	~Node();
};