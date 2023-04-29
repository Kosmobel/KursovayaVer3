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

	//Добавление людей, импорт, вывод списка, экспорт списка
	menuItem addPersonItem("Добавить нового человека", false, [this]() {this->addPerson(); });
	menuItem importFromCSV("Импорт из CSV", false, [this]() {this->importPerson(); });
	menuItem showPersonList("Просмотреть список людей", false, [this]() {this->showPersonList(); });
	menuItem exportToCSV("Экспорт в CSV", false, [this]() {this->exportPerson(); });


	//сортировки по разным параметрам
	menuItem sortById("Сортировка по id", false, [this]() {this->sortById(this->personList); });
	menuItem sortByAge("Сортировка по возрасту", false, [this]() {this->sortByAge(this->personList); });
	menuItem sortByName("Сортировка по ФИО в алфавитном порядке", false, [this]() {this->sortByName(this->personList); });
	menuItem sortByType("Сортировка по преподавателям/студентам", false, [this]() {this->sortByType(this->personList); });

	//поиск по разным параметрам
	menuItem findById("Поиск по id", false, [this]() {this->findById(this->personList); });
	menuItem findByAge("Поиск по возрасту", false, [this]() {this->findByAge(this->personList); });
	menuItem findByName("Поиск по ФИО", false, [this]() {this->findByName(this->personList); });
	menuItem findByType("Поиск преподавателям/студентам", false, [this]() {this->findByType(this->personList); });

	//удаление по параметрам
	menuItem removeById("Удаление по id", false, [this]() {this->removeById(this->personList); });
	//menuItem removeByAge("Удаление по возрасту", false, [this]() {this->removeByAge(this->personList); }); а стоит ли?
	menuItem removeByName("Удаление по ФИО", false, [this]() {this->removeByName(this->personList); });
	//menuItem removeByType("Удаление студентов/преподавателей", false, [this]() {this->removeById(this->personList); }); тоже под вопросом



	adminMenu.add_item(&addPersonItem);
	adminMenu.add_item(&importFromCSV);

	adminMenu.add_item(&findMenu);

	//добавляем в подменю действия
	sortMenu.add_item(&sortById);
	sortMenu.add_item(&sortByName);
	sortMenu.add_item(&sortByAge);
	sortMenu.add_item(&sortByType);

	//Добавляем действия в подменю поиска
	findMenu.add_item(&findById);
	findMenu.add_item(&findByName);
	findMenu.add_item(&findByAge);
	findMenu.add_item(&findByType);

	//добавляем действия в removeMenu
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

void vuzBase::exportPerson() {
	string filename;
	cout << "Введите путь к файлу: ";
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
	cout << "Введите id человека, о котором хотите узнать: ";
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
	cout << "Введите возраст людей, о которых хотите узнать: ";
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
	cout << "Введите ФИО человека, о котором хотите узнать: ";
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
	cout << "Введите, этот человек Студент или Преподаватель: ";
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
	cout << "Введите id человека, которого надо удалить: ";
	cin >> id;
	Node* current = personList->head;
	int size = personList->getSize();

	for (int j = 0; j < size; j++) {
		//выход из цикла если текущий елемент nullptr
		if (current == nullptr) {
			break;
		}

		//следующий элемент есть, следующий после него тоже есть, т.е. ситуация "посередине" + плюс проверка не является ли элемент первым
		if (current->next != nullptr && current->next->next != nullptr && current->data->getId() != id) {
			if (current->next->data->getId() == id) {
				Node* temp = current->next->next;
				delete current->next;
				current->next = temp;
				break;
			}
		}

		//проверяем последний элеменнт
		if (current->next != nullptr && current->next->next == nullptr) {
			if (current->next->data->getId() == id) {
				Node* temp = current->next->next;
				delete current->next;
				current->next = temp;
				break;
			}
		}
		//если первый элемент
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
	cout << "Введите ФИО человека, которого надо удалить: ";
	getline(cin, name);
	Node* current = personList->head;
	int size = personList->getSize();

	for (int j = 0; j < size; j++) {
		//выход из цикла если текущий елемент nullptr
		if (current == nullptr) {
			break;
		}

		//следующий элемент есть, следующий после него тоже есть, т.е. ситуация "посередине" + плюс проверка не является ли элемент первым
		if (current->next != nullptr && current->next->next != nullptr && current->data->getName() != name) {
			if (current->next->data->getName() == name) {
				Node* temp = current->next->next;
				delete current->next;
				current->next = temp;
				break;
			}
		}

		//проверяем последний элеменнт
		if (current->next != nullptr && current->next->next == nullptr) {
			if (current->next->data->getName() == name) {
				Node* temp = current->next->next;
				delete current->next;
				current->next = temp;
				break;
			}
		}
		//если первый элемент
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