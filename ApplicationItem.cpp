
#include <algorithm>
#include <vector>

#include "ApplicationItem.hpp"

using String = std::string;

ApplicationItem::ApplicationItem(const Glib::RefPtr<Gio::DesktopAppInfo>& appinfo)
: Gtk::MenuItem()
, appinfo(appinfo)
{
	Glib::RefPtr<const Gio::Icon> icon = appinfo->get_icon ();
	this->image.set (icon, Gtk::ICON_SIZE_DND);
	this->image.set_pixel_size (32);
	this->box.pack_start (this->image, false, false, 0);

	this->name = appinfo->get_display_name();

	this->label.set_label (this->name);
	this->box.pack_start (this->label, false, false, 0);
	this->add (this->box);

	this->signal_activate().connect([appinfo]() {
		appinfo->launch(std::vector<Glib::RefPtr<Gio::File>>());
	});
}

const String& ApplicationItem::getName() const
{
	return this->name;
}

const Glib::RefPtr<Gio::DesktopAppInfo>& ApplicationItem::getAppInfo() const
{
	return this->appinfo;
}

bool operator< (const ApplicationItem& a, const ApplicationItem& b)
{
	auto cmp = [] (const char s, const char t) { return std::tolower(s) < std::tolower(t); };

	if (std::lexicographical_compare (a.getName().cbegin(), a.getName().cend(),
	                                  b.getName().cbegin(), b.getName().cend(), cmp)
	)
		return true; // a < b

	if (std::lexicographical_compare (b.getName().cbegin(), b.getName().cend(),
	                                  a.getName().cbegin(), a.getName().cend(), cmp)
	)
		return false; // b < a

	/* even if at this point the application names are the same, we must still
	 * make sure they're not the same application, so that an associative
	 * container can have multiple applications with the same display name */
	return a.getAppInfo() < b.getAppInfo();
}
