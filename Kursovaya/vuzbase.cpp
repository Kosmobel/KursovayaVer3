#include <iostream>
#include "menu.h"
#include "submenu.h"
#include "menuitem.h"
#include "vuzbase.h"




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
	subMenu sortByAgeMenu("Сортировка по возрасту", false);
	subMenu sortByEmailMenu("Сортировка по email", false);

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
