#include "linkedlist.h"

void LinkedList::clear() {
	Node* current = head;
	while (current != nullptr) {
		Node* temp = current;
		current = current->next;
		delete temp;
	}
	head = nullptr;
}

void LinkedList::add(person* p) {
	Node* new_node = new Node(p);
	if (head == nullptr) {
		head = new_node;
		return;
	}
	Node* current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = new_node;
}

void LinkedList::LoadFromFile(string filename) {
	ifstream infile(filename);
	if (!infile) {
		throw runtime_error("Файл с данными не найден!");
	}
	clear();
	string line;
	while (getline(infile, line)) {
		stringstream ss(line);
		string id_str, age_str, name, email, phoneNum, type;

		getline(ss, id_str, ';');
		getline(ss, age_str, ';');
		getline(ss, name, ';');
		getline(ss, email, ';');
		getline(ss, phoneNum, ';');
		getline(ss, type, ';');

		int id = stoi(id_str);
		int age = stoi(age_str);
		person* Person = new person(id, age, name, email, phoneNum, type);
		add(Person);
	}
	infile.close();
}

void LinkedList::SaveToFile(string filename) {
	ofstream outfile(filename);
	if (!outfile) {
		throw runtime_error("Ошибка создания файла!");
	}
	Node* current = head;

	while (current != nullptr) {
		outfile << current->data->getId() << ";"
			<< current->data->getAge() << ";"
			<< current->data->getName() << ";"
			<< current->data->getEmail() << ";"
			<< current->data->getPhone() << ";"
			<< current->data->getType() << endl;
		current = current->next;
	}
	outfile.close();
}