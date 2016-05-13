
#include <gtkmm.h>
#include <list>

#include "MenuItem.hpp"

int main(int argc, char** argv)
{
	auto gtkapplication = Gtk::Application::create(argc, argv, "com.altoe.appy");
	Gtk::Menu menu;
	Gio::init();
	std::list<MenuItem> items;

	for (auto app : Gio::DesktopAppInfo::get_all ())
	{
		if (app->should_show())
		{
			if (app->get_icon())
			{
				items.push_back (MenuItem (std::move (app)));
			}
		}
	}
	/* sort items according to operator< */
	items.sort();

	/* bind methods and add to menu */
	for (auto&& item : items)
	{
		item.signal_activate().connect (sigc::mem_fun(item, &MenuItem::execute));
		menu.add(item);
	}

	auto quit = [&gtkapplication](GdkEventAny* any) -> void
	{
		gtkapplication->quit();
	};

	/* bind nullptr to argument and connect to deactivate signal */
	menu.signal_deactivate().connect (sigc::bind (quit, nullptr));

	/* bind return false and connect to delete signal */
	menu.signal_delete_event().connect (sigc::bind_return (quit, false));

	menu.set_reserve_toggle_size(false);
	menu.show_all ();
	menu.popup (0, 0);

	/* this prevents gtk from exiting as there is no window */
	gtkapplication->hold();
	return gtkapplication->run();
}

