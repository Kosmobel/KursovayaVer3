#include <iostream>
#include "menu.h"
#include "submenu.h"
#include "menuitem.h"
#include "vuzbase.h"




void vuzBase::run() {
	subMenu mainmenu("���������� ����", false);

	subMenu adminMenu("���� �������������� �����������", true);
	subMenu userMenu("�������� �����������", false);

	subMenu sortMenu("����������", false);
	subMenu findMenu("����� �� ����", false);
	subMenu removeMenu("��������", false);
	subMenu exportMenu("������� �����������", false);

	subMenu sortByIdMenu("���������� �� Id", false);
	subMenu sortByNameMenu("���������� �� �����", false);
	subMenu sortByAgeMenu("���������� �� ��������", false);
	subMenu sortByEmailMenu("���������� �� email", false);

	adminMenu.add_item(&findMenu);
	sortMenu.add_item(&sortByIdMenu);
	sortMenu.add_item(&sortByNameMenu);
	sortMenu.add_item(&sortByAgeMenu);
	sortMenu.add_item(&sortByEmailMenu);
	adminMenu.add_item(&sortMenu);
	adminMenu.add_item(&removeMenu);
	adminMenu.add_item(&exportMenu);


	userMenu.add_item(&sortMenu);
	userMenu.add_item(&findMenu);
	userMenu.add_item(&exportMenu);

	mainmenu.add_item(&adminMenu);
	mainmenu.add_item(&userMenu);

	mainmenu.run();


}

vuzBase::vuzBase() {}
vuzBase::~vuzBase() {}
