#include <Xbdm.h>

using namespace XBDM;

int main()
{
	DevConsole console("192.168.1.104");
	
	if (!console.OpenConnection())
	{
		std::cout << "Couldn't connect to console!" << std::endl;
		return 0;
	}

	std::cout << "Connected to console successfully!" << std::endl;

	return 0;
}
