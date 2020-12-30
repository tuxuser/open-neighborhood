#include "pch.h"
#include "Xbox/XboxManager.h"

XBDM::Console XboxManager::s_Console;

void XboxManager::CreateConsole(const std::string& ipAddress)
{
	s_Console = XBDM::Console(ipAddress);
}
