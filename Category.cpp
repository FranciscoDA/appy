/*
 * Category.cpp
 *
 *  Created on: May 13, 2016
 *      Author: francisco
 */

#include "Category.hpp"

/* https://standards.freedesktop.org/menu-spec/latest/apa.html */
std::list<Category::ptr_t> Category::mainCategories;
std::map<std::string, Category::ptr_t> Category::mainCategories_map;
void Category::initializeCategories()
{
	mainCategories.push_back (std::make_shared<Category> ("Multimedia", "applications-multimedia"));
	mainCategories_map["AudioVideo"] = mainCategories.back();
	mainCategories_map["Audio"] = mainCategories.back();
	mainCategories_map["Video"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Development","applications-development"));
	mainCategories_map["Development"] = mainCategories.back();
	mainCategories_map["Education"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Science","applications-science"));
	mainCategories_map["Science"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Games","applications-games"));
	mainCategories_map["Game"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Graphics","applications-graphics"));
	mainCategories_map["Graphics"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Internet","applications-internet"));
	mainCategories_map["Network"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Office","applications-office"));
	mainCategories_map["Office"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Settings","preferences-desktop"));
	mainCategories_map["Settings"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("System","applications-system"));
	mainCategories_map["System"] = mainCategories.back();

	mainCategories.push_back (std::make_shared<Category> ("Utilities","applications-utilities"));
	mainCategories_map["Utility"] = mainCategories.back();
}

Category::Category(std::string&& name, std::string&& iconName)
: Gtk::MenuItem()
, display_name(name)
{
	this->submenu.set_reserve_toggle_size(false);
	this->set_submenu(this->submenu);

	Glib::RefPtr<const Gio::Icon> icon = Gio::Icon::create(iconName);
	this->image.set(icon, Gtk::ICON_SIZE_DND);
	this->image.set_pixel_size(32);
	this->box.pack_start(this->image, false, false, 0);

	this->label.set_label(name);
	this->box.pack_start(this->label, false, false, 0);

	this->add(this->box);
}

const Category::item_ptr_t Category::addApplication(const Glib::RefPtr<Gio::DesktopAppInfo>& appinfo)
{
	auto item = std::make_shared<ApplicationItem> (appinfo);
	auto pair = this->applications.insert(item);
	/* if insertion took place (ie. the element was not repeated) */
	if (pair.second)
	{
		/* use the returned iter to determine the correct position*/
		int position = 0;
		for (auto it = pair.first; it != this->applications.cbegin(); --it)
		{
			position++;
		}
		/* then add to submenu */
		this->submenu.insert(*item, position);
	}
	/* return element whether it as added to the submenu or not */
	return *(pair.first);
}

const decltype(Category::applications)& Category::getApplications() const
{
	return this->applications;
}

const std::string& Category::getDisplayName() const
{
	return this->display_name;
}

std::list<Category::item_ptr_t> Category::categorize(const Glib::RefPtr<Gio::DesktopAppInfo>& appinfo)
{
	std::list<Category::item_ptr_t> applications;
	std::string catstr = appinfo->get_categories();
	std::string::size_type begin = 0;
	while (begin != std::string::npos && begin < catstr.size ())
	{
		std::string::size_type end = catstr.find(";", begin);
		std::string current_tag;
		if (end != std::string::npos)
		{
			current_tag = catstr.substr (begin, end - begin);
			begin = end + 1;
		}
		else
		{
			current_tag = catstr.substr (begin);
			begin = std::string::npos;
		}
		auto it = Category::mainCategories_map.find(current_tag);
		if (it != Category::mainCategories_map.end())
		{
			auto item = (*it).second->addApplication (appinfo);
			applications.push_back(item);
		}
	}
	return applications;
}
