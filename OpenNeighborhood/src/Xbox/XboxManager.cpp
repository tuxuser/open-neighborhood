#include "pch.h"
#include "Xbox/XboxManager.h"

XBDM::Console XboxManager::s_Console;

bool XboxManager::CreateConsole(const std::string& ipAddress, std::string& consoleName)
{
	s_Console = XBDM::Console(ipAddress);

	if (s_Console.OpenConnection())
	{
		consoleName = s_Console.GetConsoleName();
		s_Console.CloseConnection();
		return true;
	}
	else
		return false;
}
