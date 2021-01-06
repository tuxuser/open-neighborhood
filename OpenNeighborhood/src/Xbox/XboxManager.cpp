#include "pch.h"
#include "Xbox/XboxManager.h"

XBDM::Console XboxManager::s_Console;
std::string XboxManager::s_CurrentLocation;

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

std::string XboxManager::GoToDirectory(const std::string& directory)
{
	if (directory.front() != '\\' && !s_CurrentLocation.empty())
		s_CurrentLocation += '\\';

	if (s_CurrentLocation.empty())
		s_CurrentLocation += (directory + ':');
	else
		s_CurrentLocation += directory;

	return s_CurrentLocation;
}

std::string XboxManager::GoToParent()
{
	size_t lastSeparatorIndex = s_CurrentLocation.find_last_of('\\');
	if (lastSeparatorIndex != std::string::npos)
		s_CurrentLocation = s_CurrentLocation.substr(0, lastSeparatorIndex);

	return s_CurrentLocation;
}
