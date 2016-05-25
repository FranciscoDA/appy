
#ifndef _MENUITEM_HPP_
#define _MENUITEM_HPP_

#include <list>

#include <gtkmm.h>


class ApplicationItem : public Gtk::MenuItem {
public:
	ApplicationItem(const Glib::RefPtr<Gio::DesktopAppInfo>& appinfo);

	/* copy ctor is invalid for Gtk::Widgets*/
	ApplicationItem(const ApplicationItem&) = delete;

	/* force creation of move ctor, otherwise,
	 * the stl will try to use copy ctor */
	ApplicationItem(ApplicationItem&&) = default;

	const std::string& getName() const;
	const Glib::RefPtr<Gio::DesktopAppInfo>& getAppInfo() const;

	bool operator==(const ApplicationItem& other) const;
	bool operator!=(const ApplicationItem& other) const;
	bool operator<(const ApplicationItem& other) const;

private:
	Glib::RefPtr<Gio::DesktopAppInfo> appinfo;
	std::string name;
	Gtk::Image image;
	Gtk::Label label;
	Gtk::Box box;
};

#endif
