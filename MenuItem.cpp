
#include <vector>
#include "MenuItem.hpp"

MenuItem::MenuItem(Glib::RefPtr<Gio::AppInfo>&& appinfo)
: Gtk::MenuItem()
, appinfo(appinfo)
{
	Glib::RefPtr<const Gio::Icon> icon = this->appinfo->get_icon();
	this->image.set (icon, Gtk::ICON_SIZE_DND);
	this->image.set_pixel_size(32);
	this->box.pack_start (this->image, false, false, 0);

	this->name = this->appinfo->get_display_name();

	this->label.set_label (this->name);
	this->box.pack_start (this->label, false, false, 0);
	this->add (this->box);
}

const std::string& MenuItem::getName() const
{
	return this->name;
}

void MenuItem::execute()
{
	auto ctx = Gdk::Display::get_default()->get_app_launch_context();
	this->appinfo->launch(std::vector<Glib::RefPtr<Gio::File>>(), ctx);
}

bool operator <(const MenuItem& m1, const MenuItem& m2)
{
	return m1.getName() < m2.getName();
}
