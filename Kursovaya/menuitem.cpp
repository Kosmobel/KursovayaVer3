#include "menuitem.h"
#include "submenu.h"
#include "windows.h"




void hr_dashed(int width) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 48);
	cout << "|" << endl;
	for (int i = 1; i < width; i++) {
		cout << "-";
	}
	cout << "|";
}

void hr(int width) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 48);
	cout << "|";
	for (int i = 1; i < width; i++) {
		cout << "_";
	}
	cout << "|";
}

void menuItem::run() {
	if (getProtected() && !getAccessGranted()) {
		if (!this->checkPassword()) {
			return;
		}
	}
	system("cls");
	//hr_dashed(40);
	cout << "\t\t" << title_ << endl;
	//hr(40);
	(action_)();
}