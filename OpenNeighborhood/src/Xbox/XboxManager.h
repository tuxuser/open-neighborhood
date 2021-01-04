#pragma once

#include <XBDM.h>

class XboxManager
{
public:
	static bool CreateConsole(const std::string& ipAddress, std::string& consoleName, bool keepConnectionOpen = false);

	inline static XBDM::Console GetConsole() { return s_Console; }
private:
	static XBDM::Console s_Console;
};
