#include "pch.h"
#include "Console.h"

namespace XBDM
{
	Console::Console()
		: m_Socket(INVALID_SOCKET) {}

	Console::Console(const std::string& ipAddress)
		: m_IpAddress(ipAddress), m_Socket(INVALID_SOCKET) {}

	bool Console::OpenConnection()
	{
		m_Connected = false;
		addrinfo hints;
		addrinfo* addrInfo;
		ZeroMemory(&hints, sizeof(hints));

#ifdef _WIN32
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			return false;
#endif

		if (getaddrinfo(m_IpAddress.c_str(), "730", &hints, &addrInfo) != 0)
		{
			CleanupSocket();
			return false;
		}

		m_Socket = socket(AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP);
		if (m_Socket < 0)
		{
			CleanupSocket();
			return false;
		}

		timeval tv = { 5 ,0 };
		setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(timeval));

		if (connect(m_Socket, addrInfo->ai_addr, (int)addrInfo->ai_addrlen) == SOCKET_ERROR)
		{
			CloseSocket();
			return false;
		}

		if (m_Socket == INVALID_SOCKET)
		{
			CleanupSocket();
			return false;
		}

		if (Receive() != "201- connected\r\n")
			return false;

		m_Connected = true;
		return true;
	}

	bool Console::CloseConnection()
	{
		CloseSocket();
		CleanupSocket();

		m_Connected = false;
		return m_Socket == INVALID_SOCKET;
	}

	std::string Console::GetName()
	{
		SendCommand("dbgname");
		std::string response = Receive();

		std::string result = response.substr(5, response.length() - 5);
		return result;
	}

	std::vector<Drive> Console::GetDrives()
	{
		std::vector<Drive> drives;

		SendCommand("drivelist");
		std::string listResponse = Receive();

		std::vector<std::string> lines = SplitResponse(listResponse, "\r\n");

		for (auto& line : lines)
		{
			std::string driveName = GetStringProperty(line, "drivename");
			if (driveName == "")
				continue;

			Drive drive;
			drive.Name = driveName;

			// Gets the friendly name for volume, these are from neighborhood
			if (drive.Name == "DEVKIT" || drive.Name == "E")
				drive.FriendlyName = "Game Development Volume (" + drive.Name + ":)";
			else if (drive.Name == "HDD")
				drive.FriendlyName = "Retail Hard Drive Emulation (" + drive.Name + ":)";
			else if (drive.Name == "Y")
				drive.FriendlyName = "Xbox360 Dashboard Volume (" + drive.Name + ":)";
			else if (drive.Name == "Z")
				drive.FriendlyName = "Devkit Drive (" + drive.Name + ":)";
			else if (drive.Name == "D" || drive.Name == "GAME")
				drive.FriendlyName = "Active Title Media (" + drive.Name + ":)";
			else
				drive.FriendlyName = "Volume (" + drive.Name + ":)";

			// Gets the free space for each drive
			SendCommand("drivefreespace name=\"" + drive.Name + ":\\\"");
			std::string spaceResponse = Receive();

			drive.FreeBytesAvailable = (UINT64)GetIntegerProperty(spaceResponse, "freetocallerhi") << 32 | (UINT64)GetIntegerProperty(spaceResponse, "freetocallerlo");
			drive.TotalBytes = (UINT64)GetIntegerProperty(spaceResponse, "totalbyteshi") << 32 | (UINT64)GetIntegerProperty(spaceResponse, "totalbyteslo");
			drive.TotalFreeBytes = (UINT64)GetIntegerProperty(spaceResponse, "totalfreebyteshi") << 32 | (UINT64)GetIntegerProperty(spaceResponse, "totalfreebyteslo");
			drive.TotalUsedBytes = drive.TotalBytes - drive.FreeBytesAvailable;

			drives.push_back(drive);
		}

		return drives;
	}

	std::vector<File> Console::GetDirectoryContents(const std::string& directoryPath)
	{
		std::vector<File> files;

		SendCommand("dirlist name=\"" + directoryPath + "\"");
		std::string contentResponse = Receive();

		std::vector<std::string> lines = SplitResponse(contentResponse, "\r\n");

		if (lines[0][0] == '4')
			throw std::invalid_argument("Invalid directory path: " + directoryPath);

		for (auto& line : lines)
		{
			std::string fileName = GetStringProperty(line, "name");
			if (fileName == "")
				continue;

			File file;

			file.Name = fileName;
			file.Size = (UINT64)GetIntegerProperty(line, "sizehi") << 32 | (UINT64)GetIntegerProperty(line, "sizelo");
			file.IsDirectory = EndsWith(line, " directory");

			std::filesystem::path filePath(file.Name);
			file.IsXEX = filePath.extension() == ".xex";

			files.push_back(file);
		}

		return files;
	}

	std::string Console::Receive()
	{
		std::string result;
		char buffer[2048]{ 0 };

		while (recv(m_Socket, buffer, sizeof(buffer), 0) != SOCKET_ERROR)
		{
			SleepFor(10); // The Xbox 360 is old and slow, we need to give it some time...
			result += buffer;
		}

		return result;
	}

	void Console::SendCommand(const std::string& command)
	{
		std::string fullCommand = command + "\r\n";
		if (send(m_Socket, fullCommand.c_str(), (int)fullCommand.length(), 0) == SOCKET_ERROR)
		{
			CloseSocket();
			CleanupSocket();
		}
	}

	std::vector<std::string> Console::SplitResponse(const std::string& response, const std::string& delimiter)
	{
		std::vector<std::string> result;
		std::string responseCopy = response;
		size_t pos = 0;
		std::string line;

		while ((pos = responseCopy.find(delimiter)) != std::string::npos)
		{
			line = responseCopy.substr(0, pos);

			if (line != ".")
				result.push_back(line);

			responseCopy.erase(0, pos + delimiter.length());
		}

		return result;
	}

	bool Console::EndsWith(const std::string& line, const std::string& ending)
	{
		if (ending.size() > line.size())
			return false;

		return std::equal(ending.rbegin(), ending.rend(), line.rbegin());
	}

	DWORD Console::GetIntegerProperty(const std::string& line, const std::string& propertyName, bool hex)
	{
		if (line.find(propertyName) == std::string::npos)
			return (DWORD)std::string::npos;

		// all of the properties are like this: NAME=VALUE
		size_t startIndex = line.find(propertyName) + propertyName.size() + 1;
		size_t spaceIndex = line.find(' ', startIndex);
		size_t crIndex = line.find('\r', startIndex);
		size_t endIndex = (spaceIndex != std::string::npos) ? spaceIndex : crIndex;

		DWORD toReturn;
		if (hex)
			std::istringstream(line.substr(startIndex, endIndex - startIndex)) >> std::hex >> toReturn;
		else
			std::istringstream(line.substr(startIndex, endIndex - startIndex)) >> toReturn;

		return toReturn;
	}

	std::string Console::GetStringProperty(const std::string& line, const std::string& propertyName)
	{
		if (line.find(propertyName) == std::string::npos)
			return "";

		// all string properties are like this: NAME="VALUE"
		size_t startIndex = line.find(propertyName) + propertyName.size() + 2;
		size_t endIndex = line.find('"', startIndex);

		std::string toReturn = line.substr(startIndex, endIndex - startIndex);

		return toReturn;
	}

	void Console::CleanupSocket()
	{
#ifdef _WIN32
		WSACleanup();
#endif
	}

	void Console::CloseSocket()
	{
#ifdef _WIN32
		closesocket(m_Socket);
#else
		close(m_Socket);
#endif
		m_Socket = INVALID_SOCKET;
	}

	void Console::SleepFor(DWORD milliseconds)
	{
#ifdef _WIN32
		Sleep(milliseconds);
#else
		usleep(milliseconds);
#endif
	}
}
