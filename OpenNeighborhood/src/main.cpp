#include "pch.h"

#include <Xbdm.h>

using namespace XBDM;

int main()
{
	DevConsole console("192.168.1.104");
	
	if (!console.OpenConnection())
	{
		LOG_ERROR("Couldn't connect to console!");
		return 0;
	}

	LOG_SUCCESS("Connected to console successfully!");

	if (!console.CloseConnection())
	{
		LOG_ERROR("Couldn't disconnect from console!");
		return 0;
	}

	LOG_SUCCESS("Disconnected from console successfully!");

	return 0;
}
