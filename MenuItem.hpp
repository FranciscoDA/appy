
#ifndef _MENUITEM_HPP_
#define _MENUITEM_HPP_

#include <gtkmm.h>

class MenuItem : public Gtk::MenuItem {
public:
	MenuItem(Glib::RefPtr<Gio::AppInfo>&& appinfo);
	MenuItem(const MenuItem&) = delete;

	/* force creation of move ctor, otherwise,
	 * the stl will try to use copy ctor
	 * which is invalid for Gtk::Widget */
	MenuItem(MenuItem&&) = default;

	const std::string& getName() const;

	void execute();
private:
	Glib::RefPtr<Gio::AppInfo> appinfo;
	std::string name;
	Gtk::Image image;
	Gtk::Label label;
	Gtk::Box box;
};

bool operator <(const MenuItem& m1, const MenuItem& m2);

#endif
