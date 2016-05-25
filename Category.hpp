/*
 * Category.hpp
 *
 *  Created on: May 13, 2016
 *      Author: francisco
 */

#ifndef CATEGORY_HPP_
#define CATEGORY_HPP_

#include <algorithm>
#include <map>
#include <set>
#include <gtkmm.h>
#include <string>

#include "ApplicationItem.hpp"

class Category : public Gtk::MenuItem {
public:
	typedef std::shared_ptr<Category> ptr_t;
	typedef std::shared_ptr<ApplicationItem> item_ptr_t;
private:
	struct set_comparator
	{
		bool operator()(const item_ptr_t& a, const item_ptr_t& b)
		{
			auto ita = a->getName().begin();
			auto itb = b->getName().begin();
			while (ita != a->getName().end() && itb != b->getName().end())
			{
				if (std::tolower (*ita) < std::tolower (*itb))
				{
					return true;
				}
				else if (std::tolower (*itb) < std::tolower (*ita))
				{
					return false;
				}
				++ita;
				++itb;
			}
			/* a was shorter */
			if (ita == a->getName().end())
				return true;
			return false;
		}
	};
protected:
	std::string display_name;
	static std::map<std::string, ptr_t> mainCategories_map;
	std::set<item_ptr_t, set_comparator> applications;
	Gtk::Image image;
	Gtk::Label label;
	Gtk::Box box;
	Gtk::Menu submenu;
public:
	Category(std::string&& name, std::string&& iconName);
	Category(Category&&) = default;

	const item_ptr_t addApplication (const Glib::RefPtr<Gio::DesktopAppInfo>& appinfo);
	const decltype(applications)& getApplications () const;
	const std::string& getDisplayName() const;

	static void initializeCategories ();
	static std::list<ptr_t> mainCategories;
	static std::list<item_ptr_t> categorize (const Glib::RefPtr<Gio::DesktopAppInfo>& appinfo);
};

#endif /* CATEGORY_HPP_ */
