#include <iostream>
#include "menu.h"
#include "submenu.h"
#include "menuitem.h"
#include "vuzbase.h"
#include <algorithm>


using namespace std;


void vuzBase::run() {
	subMenu mainmenu("Справочник ВУЗа", false);

	subMenu adminMenu("Меню администратора справочника", true);
	subMenu userMenu("Просмотр справочника", false);

	subMenu sortMenu("Сортировка", false);
	subMenu findMenu("Поиск по базе", false);
	subMenu removeMenu("Удаление", false);
	subMenu exportMenu("Экспорт справочника", false);

	subMenu sortByIdMenu("Сортировка по Id", false);
	subMenu sortByNameMenu("Сортировка по имени", false);
	subMenu sortByEmailMenu("Сортировка по email", false);

	menuItem addPersonItem("Добавить нового человека", false, [this]() {this->addPerson(); });
	menuItem importFromCSV("Импорт из CSV", false, [this]() {this->importPerson(); });
	menuItem showPersonList("Просмотреть список людей", false, [this]() {this->showPersonList(); });

	//menuItem sortedById("Элементы списка отсортированные по Id", false, [this]() {this->sortById(); });
	menuItem sortByAge("Отсортировать людей по возрасту: ", false, [this]() {this->sortByAge(this->personList); });


	adminMenu.add_item(&addPersonItem);
	adminMenu.add_item(&importFromCSV);

	adminMenu.add_item(&findMenu);


	sortMenu.add_item(&sortByIdMenu);
	sortMenu.add_item(&sortByNameMenu);
	sortMenu.add_item(&sortByAge);
	sortMenu.add_item(&sortByEmailMenu);
	adminMenu.add_item(&sortMenu);
	adminMenu.add_item(&removeMenu);
	adminMenu.add_item(&exportMenu);


	userMenu.add_item(&sortMenu);
	userMenu.add_item(&findMenu);
	userMenu.add_item(&exportMenu);

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
	cout << "Введите порядковый номер: ";
	cin >> idPerson;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Введите возраст: ";
	cin >> agePerson;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Введите имя человека в формате Фамилия Имя Отчество: ";
	getline(cin, namePerson);

	cout << "Электронную почту человека: ";
	getline(cin, emailPerson);

	cout << "Введите номер телефона человека ";
	getline(cin, phonePerson);

	cout << "Укажите, этот человек студент или преподаватель: ";
	getline(cin, typePerson);

	person* personItem = new person(idPerson, agePerson, namePerson, emailPerson, phonePerson, typePerson);
	personList->add(personItem);
}

void vuzBase::importPerson() {
	string filename;
	cout << "Введите путь к файлу: ";
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

void vuzBase::showPersonList() {
	this->printresult(personList);
	getchar();
}

void vuzBase::printresult(LinkedList* personList) {
	Node* current = personList->head;
	while (current != nullptr) {
		cout << current->data->getId() << ";"
			<< current->data->getAge() << ";"
			<< current->data->getName() << ";"
			<< current->data->getEmail() << ";"
			<< current->data->getPhone() << ";"
			<< current->data->getType() << endl;
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