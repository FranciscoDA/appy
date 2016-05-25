
#include <iostream>
#include <gtkmm.h>
#include <list>
#include <set>

#include "ApplicationItem.hpp"
#include "Category.hpp"

int main(int argc, char** argv)
{
	auto gtkapplication = Gtk::Application::create(argc, argv, "com.flacko.appy");
	Gtk::Menu menu;
	Gio::init();

	Category::initializeCategories();

	for (auto app : Gio::AppInfo::get_all ())
	{
		auto dapp = Gio::DesktopAppInfo::create(app->get_id());
		if (dapp && dapp->should_show() && dapp->get_icon())
		{
			auto appitems = Category::categorize(dapp);
			for (auto& app : appitems)
			{
				app->signal_activate().connect ([dapp] () {
					dapp->launch_uri("");
				});
			}
		}
	}

	for (auto& cat : Category::mainCategories)
	{
		menu.add(*cat);
		/*cat->signal_select().connect([&cat] () -> void {
			cat->expand();
		});*/
		std::cout << cat->getDisplayName() << std::endl;
		for (auto& app : cat->getApplications())
		{
			std::cout << '\t' << app->getName() << std::endl;
		}
	}

	menu.signal_deactivate().connect([&gtkapplication]() {
		gtkapplication->quit();
	});
	menu.signal_delete_event().connect ([&gtkapplication](GdkEventAny*) {
		gtkapplication->quit();
		return false;
	});

	menu.set_reserve_toggle_size (false);
	menu.show_all ();
	menu.popup (0, 0);

	/* this prevents gtk from exiting as there is no window */
	gtkapplication->hold();
	return gtkapplication->run();
}

