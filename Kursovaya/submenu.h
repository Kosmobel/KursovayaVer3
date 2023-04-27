#pragma once
#include "menu.h"
#include "vector"
using namespace std;


class subMenu : public menu {
public:
	subMenu(const string& title, bool isProtected) : menu(title, isProtected) {}
	void add_item(menu* menuitem) {
		items_.push_back(menuitem);
	}
	void run() override;
	~subMenu() {}
private:
	vector<menu*> items_;
};