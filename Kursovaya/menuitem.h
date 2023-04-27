#pragma once
#include "menu.h"
#include <functional>

using namespace std;
class menuItem : public menu {
public:
	menuItem(const string& title, bool isProtected, function<void()> action) : menu(title, isProtected), action_(action) {}
	void run() override;
	~menuItem() {}
private:
	function<void()> action_;
};