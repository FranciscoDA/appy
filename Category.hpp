/*
 * Category.hpp
 *
 *  Created on: May 13, 2016
 *      Author: francisco
 */

#ifndef CATEGORY_HPP_
#define CATEGORY_HPP_

#include <map>
#include <set>
#include <gtkmm.h>
#include <string>

#include "ApplicationItem.hpp"

template <class ... Args> using List = std::list<Args...>;
template <class ... Args> using Map  = std::map<Args...>;
template <class ... Args> using Set  = std::set<Args...>;

using String = std::string;

class Category : public Gtk::MenuItem {
private:
	using ItemPtr = std::shared_ptr<ApplicationItem>;
	struct SetCmp
	{
		bool operator()(const ItemPtr& a, const ItemPtr& b)
		{
			return *a < *b;
		}
	};
protected:
	String               displayName;
	Set<ItemPtr, SetCmp> applications;
	Gtk::Image           image;
	Gtk::Label           label;
	Gtk::Box             box;
	Gtk::Menu            submenu;
public:
	Category (const String& name, const String& iconName);
	Category (Category&&) = default;

	void                        add (const ItemPtr& item);
	const Set<ItemPtr, SetCmp>& getApplications () const;
	const String&               getDisplayName()   const;

private:
	static Map<String, std::shared_ptr<Category>> mainCategoriesMap;
public:
	static List<std::shared_ptr<Category>> mainCategories;
	static void initializeCategories ();
	static void categorize (const Glib::RefPtr<Gio::DesktopAppInfo>& appinfo);
};

#endif /* CATEGORY_HPP_ */
