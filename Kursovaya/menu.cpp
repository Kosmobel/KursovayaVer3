#include "menu.h"



string menu::getTitle() {
	return title_;
}
bool menu::checkPassword() {
	system("cls");
	string pass;
	cout << "Для получения доступа введите пароль: " << endl;
	cin >> pass;
	if (pass != password) {
		cout << "Доступ запрещен, нажмите любую клавишу для продолжения" << endl;
		getchar();
		isAccessGranted = (pass == password);
		return isAccessGranted;
	}
}