
#include "ApplicationItem.hpp"

#include <vector>

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
}

const std::string& ApplicationItem::getName() const
{
	return this->name;
}

const Glib::RefPtr<Gio::DesktopAppInfo>& ApplicationItem::getAppInfo() const
{
	return this->appinfo;
}

bool ApplicationItem::operator==(const ApplicationItem& other) const
{
	return this->getAppInfo() == other.getAppInfo();
}

bool ApplicationItem::operator!=(const ApplicationItem& other) const
{
	return this->getAppInfo() != other.getAppInfo();
}

bool ApplicationItem::operator<(const ApplicationItem& other) const
{
	return this->getAppInfo() < other.getAppInfo();
}
