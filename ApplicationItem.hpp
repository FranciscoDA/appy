
#ifndef _MENUITEM_HPP_
#define _MENUITEM_HPP_

#include <list>
#include <gtkmm.h>

using String = std::string;

class ApplicationItem : public Gtk::MenuItem {
private:
	Glib::RefPtr<Gio::DesktopAppInfo> appinfo;
	String                            name;
	Gtk::Image                        image;
	Gtk::Label                        label;
	Gtk::Box                          box;
public:
	ApplicationItem (const Glib::RefPtr<Gio::DesktopAppInfo>& appinfo);

	/* copy ctor is invalid for Gtk::Widgets */
	ApplicationItem (const ApplicationItem&) = delete;

	/* force creation of move ctor */
	ApplicationItem (ApplicationItem&&) = default;

	const String&             getName()    const;
	const decltype (appinfo)& getAppInfo() const;
};

/***
 * Comares two ApplicationItem instances
 * the smaller one of the two is the one
 * whose name should be alphabetically
 * ordered first.
 */
bool operator<(const ApplicationItem& a, const ApplicationItem& b);

#endif
