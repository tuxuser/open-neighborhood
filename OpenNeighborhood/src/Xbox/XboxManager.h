#pragma once

#include <XBDM.h>

class XboxManager
{
public:
	static void CreateConsole(const std::string& ipAddress);

	static XBDM::Console GetConsole() { return s_Console; }
private:
	static XBDM::Console s_Console;
};
