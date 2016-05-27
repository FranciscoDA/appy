/*
 * Category.cpp
 *
 *  Created on: May 13, 2016
 *      Author: francisco
 */

#include "Category.hpp"

template <class ... Args> using List = std::list<Args...>;
template <class ... Args> using Map = std::map<Args...>;
template <class ... Args> using Set = std::set<Args...>;
using String = std::string;

/* https://standards.freedesktop.org/menu-spec/latest/apa.html */
List<std::shared_ptr<Category>> Category::mainCategories;
Map<String, std::shared_ptr<Category>> Category::mainCategoriesMap;
void Category::initializeCategories()
{
	mainCategories.push_back (std::make_shared<Category> ("Multimedia", "applications-multimedia"));
	mainCategoriesMap["AudioVideo"] = mainCategories.back();
	mainCategoriesMap["Audio"] = mainCategories.back();
	mainCategoriesMap["Video"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Development","applications-development"));
	mainCategoriesMap["Development"] = mainCategories.back();
	mainCategoriesMap["Education"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Science","applications-science"));
	mainCategoriesMap["Science"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Games","applications-games"));
	mainCategoriesMap["Game"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Graphics","applications-graphics"));
	mainCategoriesMap["Graphics"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Internet","applications-internet"));
	mainCategoriesMap["Network"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Office","applications-office"));
	mainCategoriesMap["Office"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Settings","preferences-desktop"));
	mainCategoriesMap["Settings"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("System","applications-system"));
	mainCategoriesMap["System"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Utilities","applications-utilities"));
	mainCategoriesMap["Utility"] = mainCategories.back();
}

Category::Category(const String& name, const String& iconName)
: Gtk::MenuItem()
, displayName(name)
{
	this->submenu.set_reserve_toggle_size(false);
	this->set_submenu(this->submenu);

	Glib::RefPtr<const Gio::Icon> icon = Gio::Icon::create(iconName);
	this->image.set(icon, Gtk::ICON_SIZE_DND);
	this->image.set_pixel_size(32);
	this->box.pack_start(this->image, false, false, 0);

	this->label.set_label(name);
	this->box.pack_start(this->label, false, false, 0);

	Gtk::MenuItem::add(this->box);
}

void Category::add (const ItemPtr& item)
{
	auto pair = this->applications.insert(item);
	/* if insertion took place (ie. the element was not repeated) */
	if (pair.second)
	{
		/* use the returned iter to determine the correct position in widget */
		int position = 0;
		for (auto it = pair.first; it != this->applications.cbegin(); --it)
		{
			position++;
		}
		/* then add to submenu */
		this->submenu.insert(*item, position);
	}
}

const decltype (Category::applications)& Category::getApplications () const
{
	return this->applications;
}

const String& Category::getDisplayName() const
{
	return this->displayName;
}

void Category::categorize(const Glib::RefPtr<Gio::DesktopAppInfo>& appinfo)
{
	String catstr = appinfo->get_categories();
	String::size_type begin = 0;
	String::size_type end;
	do {
		end = catstr.find(";", begin);
		String current_tag = catstr.substr (begin, end-begin);
		begin = end + 1;
		auto it = Category::mainCategoriesMap.find(current_tag);
		if (it != Category::mainCategoriesMap.end())
		{
			auto item = std::make_shared<ApplicationItem> (appinfo);
			(*it).second->add (item);
		}
	} while (end != String::npos);
}
