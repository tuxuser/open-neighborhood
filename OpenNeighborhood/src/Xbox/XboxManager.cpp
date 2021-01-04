#include "pch.h"
#include "Xbox/XboxManager.h"

XBDM::Console XboxManager::s_Console;

bool XboxManager::CreateConsole(const std::string& ipAddress, std::string& consoleName, bool keepConnectionOpen)
{
	bool success;
	s_Console = XBDM::Console(ipAddress);

	if (s_Console.OpenConnection())
	{
		consoleName = s_Console.GetConsoleName(&success);
		
		if (!keepConnectionOpen)
			s_Console.CloseConnection();

		return true;
	}
	else
		return false;
}
