#include <iostream>
#include "menu.h"
#include "submenu.h"
#include "menuitem.h"
#include "vuzbase.h"
#include <algorithm>


using namespace std;


void vuzBase::run() {
	subMenu mainmenu("���������� ����", false);

	subMenu adminMenu("���� �������������� �����������", true);
	subMenu userMenu("�������� �����������", false);

	subMenu sortMenu("����������", false);
	subMenu findMenu("����� �� ����", false);
	subMenu removeMenu("��������", false);

	//���������� �����, ������, ����� ������, ������� ������
	menuItem addPersonItem("�������� ������ ��������", false, [this]() {this->addPerson(); });
	menuItem importFromCSV("������ �� CSV", false, [this]() {this->importPerson(); });
	menuItem showPersonList("����������� ������ �����", false, [this]() {this->showPersonList(); });
	menuItem exportToCSV("������� � CSV", false, [this]() {this->exportPerson(); });


	//���������� �� ������ ����������
	menuItem sortById("���������� �� id", false, [this]() {this->sortById(this->personList); });
	menuItem sortByAge("���������� �� ��������", false, [this]() {this->sortByAge(this->personList); });
	menuItem sortByName("���������� �� ��� � ���������� �������", false, [this]() {this->sortByName(this->personList); });
	menuItem sortByType("���������� �� ��������������/���������", false, [this]() {this->sortByType(this->personList); });

	//����� �� ������ ����������
	menuItem findById("����� �� id", false, [this]() {this->findById(this->personList); });
	menuItem findByAge("����� �� ��������", false, [this]() {this->findByAge(this->personList); });
	menuItem findByName("����� �� ���", false, [this]() {this->findByName(this->personList); });
	menuItem findByType("����� ��������������/���������", false, [this]() {this->findByType(this->personList); });

	//�������� �� ����������
	menuItem removeById("�������� �� id", false, [this]() {this->removeById(this->personList); });
	//menuItem removeByAge("�������� �� ��������", false, [this]() {this->removeByAge(this->personList); }); � ����� ��?
	menuItem removeByName("�������� �� ���", false, [this]() {this->removeByName(this->personList); });
	//menuItem removeByType("�������� ���������/��������������", false, [this]() {this->removeById(this->personList); }); ���� ��� ��������



	adminMenu.add_item(&addPersonItem);
	adminMenu.add_item(&importFromCSV);

	adminMenu.add_item(&findMenu);

	//��������� � ������� ��������
	sortMenu.add_item(&sortById);
	sortMenu.add_item(&sortByName);
	sortMenu.add_item(&sortByAge);
	sortMenu.add_item(&sortByType);

	//��������� �������� � ������� ������
	findMenu.add_item(&findById);
	findMenu.add_item(&findByName);
	findMenu.add_item(&findByAge);
	findMenu.add_item(&findByType);

	//��������� �������� � removeMenu
	removeMenu.add_item(&removeById);
	removeMenu.add_item(&removeByName);

	adminMenu.add_item(&sortMenu);
	adminMenu.add_item(&removeMenu);
	adminMenu.add_item(&exportToCSV);


	userMenu.add_item(&sortMenu);
	userMenu.add_item(&findMenu);
	userMenu.add_item(&exportToCSV);

	adminMenu.add_item(&showPersonList);
	userMenu.add_item(&showPersonList);

	mainmenu.add_item(&adminMenu);
	mainmenu.add_item(&userMenu);

	mainmenu.run();


}

vuzBase::vuzBase() {
	personList = new LinkedList();
	try {
		personList->LoadFromFile(personBaseFile);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}
}


vuzBase::~vuzBase() {
	try {
		personList->SaveToFile(personBaseFile);
	}
	catch (exception& ex) {
		cerr << ex.what() << endl;
	}
	personList->clear();
	delete personList;
}

void vuzBase::addPerson() {
	int idPerson, agePerson;
	string namePerson, emailPerson, phonePerson, typePerson;
	cout << "������� ���������� �����: ";
	cin >> idPerson;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "������� �������: ";
	cin >> agePerson;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "������� ��� �������� � ������� ������� ��� ��������: ";
	getline(cin, namePerson);

	cout << "����������� ����� ��������: ";
	getline(cin, emailPerson);

	cout << "������� ����� �������� �������� ";
	getline(cin, phonePerson);

	cout << "�������, ���� ������� ������� ��� �������������: ";
	getline(cin, typePerson);

	person* personItem = new person(idPerson, agePerson, namePerson, emailPerson, phonePerson, typePerson);
	personList->add(personItem);
}

void vuzBase::importPerson() {
	string filename;
	cout << "������� ���� � �����: ";
	cin >> filename;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	try {
		personList->LoadFromFile(filename);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
		getchar();
	}
}

void vuzBase::exportPerson() {
	string filename;
	cout << "������� ���� � �����: ";
	cin >> filename;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	try {
		personList->SaveToFile(filename);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
		getchar();
	}
}

void vuzBase::showPersonList() {
	this->printresult(personList);
	getchar();
}

void vuzBase::printresult(LinkedList* personList) {
	Node* current = personList->head;
	while (current != nullptr) {
		cout << current->data->getId() << ",\t"
			<< current->data->getAge() << ",\t"
			<< current->data->getName() << ",\t"
			<< current->data->getEmail() << ",\t"
			<< current->data->getPhone() << ",\t"
			<< current->data->getType() << "\n" << endl;
		current = current->next;
	}
}

void vuzBase::sortByAge(LinkedList* personList) {
	Node* current = personList->head;
	int size = personList->getSize();
	person* p = new person();
	Node* temp = new Node(p);
	for (int i = 0; i < size; i++) {
		current = personList->head;
		for (int j = 0; j < size; j++) {
			if (current->next == nullptr) {
				break;
			}
			if (current->data->getAge() < current->next->data->getAge()) {
				temp->data = current->next->data;
				current->next->data = current->data;
				current->data = temp->data;
			}
			current = current->next;
		}
	}
	
	this->showPersonList();
}

void vuzBase::sortById(LinkedList* personList) {
	Node* current = personList->head;
	int size = personList->getSize();
	person* p = new person();
	Node* temp = new Node(p);
	for (int i = 0; i < size; i++) {
		current = personList->head;
		for (int j = 0; j < size; j++) {
			if (current->next == nullptr) {
				break;
			}
			if (current->data->getId() > current->next->data->getId()) {
				temp->data = current->next->data;
				current->next->data = current->data;
				current->data = temp->data;
			}
			current = current->next;
		}
	}


	this->showPersonList();
}

void vuzBase::sortByName(LinkedList* personList) {
	Node* current = personList->head;
	int size = personList->getSize();
	person* p = new person();
	Node* temp = new Node(p);
	for (int i = 0; i < size; i++) {
		current = personList->head;
		for (int j = 0; j < size; j++) {
			if (current->next == nullptr) {
				break;
			}
			if (current->data->getName() > current->next->data->getName()) {
				temp->data = current->next->data;
				current->next->data = current->data;
				current->data = temp->data;
			}
			current = current->next;
		}
	}


	this->showPersonList();
}

void vuzBase::sortByType(LinkedList* personList) {
	Node* current = personList->head;
	int size = personList->getSize();
	person* p = new person();
	Node* temp = new Node(p);
	for (int i = 0; i < size; i++) {
		current = personList->head;
		for (int j = 0; j < size; j++) {
			if (current->next == nullptr) {
				break;
			}
			if (current->data->getType() > current->next->data->getType()) {
				temp->data = current->next->data;
				current->next->data = current->data;
				current->data = temp->data;
			}
			current = current->next;
		}
	}


	this->showPersonList();
}

void vuzBase::findById(LinkedList* personList) {
	int id;
	cout << "������� id ��������, � ������� ������ ������: ";
	cin >> id;
	Node* current = personList->head;
	int size = personList->getSize();
	LinkedList* findList = new LinkedList();

	for (int j = 0; j < size; j++) {
		if (current == nullptr) {
			break;
		}
		if (current->data->getId() == id) {
			findList->add(current->data);
		}
		current = current->next;
	}
	cout << "\n";
	this->printresult(findList);
	getchar();
	getchar();
}

void vuzBase::findByAge(LinkedList* personList) {
	int age;
	cout << "������� ������� �����, � ������� ������ ������: ";
	cin >> age;
	Node* current = personList->head;
	int size = personList->getSize();
	LinkedList* findList = new LinkedList();

	for (int j = 0; j < size; j++) {
		if (current == nullptr) {
			break;
		}
		if (current->data->getAge() == age) {
			findList->add(current->data);
		}
		current = current->next;
	}
	cout << "\n";
	this->printresult(findList);
	getchar();
	getchar();
}

void vuzBase::findByName(LinkedList* personList) {
	string name;
	cout << "������� ��� ��������, � ������� ������ ������: ";
	getline(cin, name);
	Node* current = personList->head;
	int size = personList->getSize();
	LinkedList* findList = new LinkedList();

	for (int j = 0; j < size; j++) {
		if (current == nullptr) {
			break;
		}
		if (current->data->getName() == name) {
			findList->add(current->data);
		}
		current = current->next;
	}
	cout << "\n";
	this->printresult(findList);
	getchar();
	getchar();
}

void vuzBase::findByType(LinkedList* personList) {
	string type;
	cout << "�������, ���� ������� ������� ��� �������������: ";
	cin >> type;
	Node* current = personList->head;
	int size = personList->getSize();
	LinkedList* findList = new LinkedList();

	for (int j = 0; j < size; j++) {
		if (current == nullptr) {
			break;
		}
		if (current->data->getType() == type) {
			findList->add(current->data);
		}
		current = current->next;
	}
	cout << "\n";
	this->printresult(findList);
	getchar();
	getchar();
}

void vuzBase::removeById(LinkedList* personList) {
	int id;
	cout << "������� id ��������, �������� ���� �������: ";
	cin >> id;
	Node* current = personList->head;
	int size = personList->getSize();

	for (int j = 0; j < size; j++) {
		//����� �� ����� ���� ������� ������� nullptr
		if (current == nullptr) {
			break;
		}

		//��������� ������� ����, ��������� ����� ���� ���� ����, �.�. �������� "����������" + ���� �������� �� �������� �� ������� ������
		if (current->next != nullptr && current->next->next != nullptr && current->data->getId() != id) {
			if (current->next->data->getId() == id) {
				Node* temp = current->next->next;
				delete current->next;
				current->next = temp;
				break;
			}
		}

		//��������� ��������� ��������
		if (current->next != nullptr && current->next->next == nullptr) {
			if (current->next->data->getId() == id) {
				Node* temp = current->next->next;
				delete current->next;
				current->next = temp;
				break;
			}
		}
		//���� ������ �������
		if (current->data->getId() == id) {
			personList->head = current->next;
			delete current;
			break;
		}

		current = current->next;
	}
	cout << "\n";
	this->showPersonList();
	getchar();
}
void vuzBase::removeByName(LinkedList* personList) {
	string name;
	cout << "������� ��� ��������, �������� ���� �������: ";
	getline(cin, name);
	Node* current = personList->head;
	int size = personList->getSize();

	for (int j = 0; j < size; j++) {
		//����� �� ����� ���� ������� ������� nullptr
		if (current == nullptr) {
			break;
		}

		//��������� ������� ����, ��������� ����� ���� ���� ����, �.�. �������� "����������" + ���� �������� �� �������� �� ������� ������
		if (current->next != nullptr && current->next->next != nullptr && current->data->getName() != name) {
			if (current->next->data->getName() == name) {
				Node* temp = current->next->next;
				delete current->next;
				current->next = temp;
				break;
			}
		}

		//��������� ��������� ��������
		if (current->next != nullptr && current->next->next == nullptr) {
			if (current->next->data->getName() == name) {
				Node* temp = current->next->next;
				delete current->next;
				current->next = temp;
				break;
			}
		}
		//���� ������ �������
		if (current->data->getName() == name) {
			personList->head = current->next;
			delete current;
			break;
		}

		current = current->next;
	}
	cout << "\n";
	this->showPersonList();
	getchar();
}