#pragma once

#include <XBDM.h>

class XboxManager
{
public:
	static bool CreateConsole(const std::string& ipAddress, std::string& consoleName, bool keepConnectionOpen = false);

	inline static XBDM::Console GetConsole() { return s_Console; }
	inline static std::string GetCurrentLocation() { return s_CurrentLocation; }

	static std::string GoToDirectory(const std::string& directory);
	static std::string GoToParent();
private:
	static XBDM::Console s_Console;
	static std::string s_CurrentLocation;
};
