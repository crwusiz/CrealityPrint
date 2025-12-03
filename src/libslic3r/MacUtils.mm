#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import "MacUtils.hpp"

namespace Slic3r {

bool is_macos_support_boost_add_file_log()
{
    if (@available(macOS 12.0, *)) {
		return true;
	} else {
	    return false;
	}
}
int is_mac_version_15()
{
    if (@available(macOS 15.0, *)) {//This code runs on macOS 15 or later.
        return true;
    } else {
        return false;
    }
}
void macos_set_menu_bar_hidden(bool enabled)
{
    [NSMenu setMenuBarVisible:!enabled];
}
}; // namespace Slic3r
