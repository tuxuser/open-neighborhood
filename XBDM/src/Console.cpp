#include "pch.h"
#include "Console.h"

#include <filesystem>

namespace XBDM {
	Console::Console()
		: m_Socket(INVALID_SOCKET) {}

	Console::Console(const std::string& ipAddress)
		: m_IpAddress(ipAddress), m_Socket(INVALID_SOCKET) {}

	bool Console::OpenConnection()
	{
		m_Socket = INVALID_SOCKET;
		struct addrinfo* result = NULL,
						* ptr = NULL,
						hints;
		int iResult;

#ifdef _WIN32
		// Initialize Winsock
		WSADATA wsaData;
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0)
			return false;
#endif

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iResult = getaddrinfo(m_IpAddress.c_str(), "730", &hints, &result);
		if (iResult != 0)
		{
			CleanupSocket();
			return false;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
			// Create a socket for connecting to server
			m_Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (m_Socket == INVALID_SOCKET)
			{
				CleanupSocket();
				return false;
			}

			// set timeouts
			struct timeval tv = { 5, 0 };
			setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

			// Connect to console
			iResult = connect(m_Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR)
			{
				CloseSocket();
				m_Socket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		// make sure that the connection succeeded
		freeaddrinfo(result);
		if (m_Socket == INVALID_SOCKET)
		{
			CleanupSocket();
			return false;
		}

		// read the crap placed on teh queue, should be "201- connected"
		BYTE buffer[0x80] = { 0 };
		ReceiveTextBuffer(buffer, 0x80);
		DWORD cmp = strcmp((char*)buffer, "201- connected\r\n");

		return m_Connected = (cmp == 0);

		return true;
	}

	bool Console::CloseConnection()
	{
		SendCommand("bye");

		shutdown(m_Socket, 1);
		CloseSocket();
		CleanupSocket();

		m_Connected = false;
		return true;
	}

	std::string Console::GetConsoleName(bool* success)
	{
		std::string consoleName;
		*success = SendCommand("dbgname", consoleName);
		
		return consoleName;
	}

	std::vector<Drive> Console::GetDrives(bool* success)
	{
		std::vector<Drive> drives;
		std::string response;
		SendCommand("drivelist", response);

		// get all of the drive names from the response
		*success = true;
		while (*success)
		{
			std::string driveName = GetStringProperty(response, "drivename", success, true);

			if (*success)
			{
				Drive d = { driveName, 0, 0, 0 };
				drives.push_back(d);
			}
		}

		// now that all of the drive names are loaded, let's get the drive size information
		for (Drive& drive : drives)
		{
			SendCommand("drivefreespace name=\"" + drive.Name + ":\\\"", response);

			drive.FreeBytesAvailable = ((UINT64)GetIntegerProperty(response, "freetocallerhi", success, true) << 32) |
				(UINT64)GetIntegerProperty(response, "freetocallerlo", success, true);
			drive.TotalBytes = ((UINT64)GetIntegerProperty(response, "totalbyteshi", success, true) << 32) |
				(UINT64)GetIntegerProperty(response, "totalbyteslo", success, true);
			drive.TotalFreeBytes = ((UINT64)GetIntegerProperty(response, "totalfreebyteshi", success, true) << 32) |
				(UINT64)GetIntegerProperty(response, "totalfreebyteslo", success, true);

			// get the friendly name for volume, these are from neighborhood
			if (drive.Name == "DEVKIT" || drive.Name == "E")
				drive.FriendlyName = "Game Development Volume (" + drive.Name + ":)";
			else if (drive.Name == "HDD")
				drive.FriendlyName = "Retail Hard Drive Emulation (" + drive.Name + ":)";
			else if (drive.Name == "Y")
				drive.FriendlyName = "Xbox360 Dashboard Volume (" + drive.Name + ":)";
			else if (drive.Name == "Z")
				drive.FriendlyName = "Devkit Drive (" + drive.Name + ":)";
			else
				drive.FriendlyName = "Volume (" + drive.Name + ":)";
		}

		return drives;
	}

	std::vector<FileEntry> Console::GetDirectoryContents(const std::string& directoryPath, bool* success)
	{
		std::string response;
		*success = SendCommand("dirlist name=\"" + directoryPath + "\"", response);

		std::vector<std::string> lines = SplitResponse(response, "\r\n");

		std::vector<FileEntry> files;
		if (!*success || response.find("file not found\r\n") == 0)
			return files;

		for (auto& line : lines)
		{
			FileEntry entry;

			entry.Name = GetStringProperty(line, "name", success);
			entry.Size = ((UINT64)GetIntegerProperty(line, "sizehi", success, true) << 32) | GetIntegerProperty(line, "sizelo", success, true);
			entry.CreationTime = FILETIME_TO_TIMET(((UINT64)GetIntegerProperty(line, "createhi", success, true) << 32) | GetIntegerProperty(line, "createlo", success, true));
			entry.ModifiedTime = FILETIME_TO_TIMET(((UINT64)GetIntegerProperty(line, "changehi", success, true) << 32) | GetIntegerProperty(line, "changelo", success, true));
			entry.IsDirectory = line.find(" directory") != std::string::npos;

			std::filesystem::path filePath(entry.Name);
			entry.IsXEX = filePath.extension() == ".xex";

			if (*success)
				files.push_back(entry);
		}

		return files;
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
	}

	bool Console::SendBinary(const BYTE* buffer, DWORD length)
	{
		int iResult = send(m_Socket, (char*)buffer, length, 0);
		if (iResult == SOCKET_ERROR)
		{
			CloseSocket();
			CleanupSocket();
			return false;
		}
		return true;
	}

	bool Console::SendCommand(const std::string& command)
	{
		std::string response;
		return SendCommand(command, response);
	}

	bool Console::SendCommand(const std::string& command, std::string& response, DWORD responseLength, DWORD statusLength)
	{
		ResponseStatus status;
		return SendCommand(command, response, status, responseLength, statusLength);
	}

	bool Console::SendCommand(const std::string& command, std::string& response, ResponseStatus& status, DWORD responseLength, DWORD statusLength)
	{
		response = "";

		// send the command to the devkit
		std::string fullCommand = command + "\r\n";
		if (!SendBinary((BYTE*)fullCommand.c_str(), (DWORD)fullCommand.length()))
			return false;

		// time for the console to compile the response
		SleepFor(20);

		return ReceiveResponse(response, status, responseLength, statusLength);
	}

	bool Console::ReceiveTextBuffer(BYTE* buffer, DWORD length)
	{
		DWORD bytesReceived;
		if (!ReceiveTimeout((char*)buffer, length, MSG_PEEK, bytesReceived))
			return false;

		DWORD lenToGet = 0;

		while (lenToGet < length)
		{
			if (buffer[lenToGet] == 0)
				break;
			lenToGet++;
		}

		// now actually read the bytes off the queue
		ZeroMemory(buffer, length);
		if (!ReceiveTimeout((char*)buffer, lenToGet, 0, bytesReceived))
			return false;
		return true;
	}

	bool Console::ReceiveBinary(BYTE* buffer, DWORD length, DWORD& bytesRecieved)
	{
		return ReceiveTimeout((char*)buffer, length, 0, bytesRecieved);
	}

	bool Console::ReceiveResponse(std::string& response, ResponseStatus& status, DWORD responseLength, DWORD statusLength)
	{
		// get the response from the console, first just read the status
		std::unique_ptr<BYTE[]> buffer(new BYTE[responseLength]);
		ZeroMemory(buffer.get(), responseLength);

		// read the status
		DWORD bytesRecieved;
		if (!ReceiveBinary(buffer.get(), 5, bytesRecieved))
			return false;

		// get the status from the response
		int statusInt;
		std::istringstream(std::string((char*)buffer.get()).substr(0, 3)) >> statusInt;
		status = (ResponseStatus)statusInt;

		// parse the response
		switch ((ResponseStatus)statusInt)
		{
			case ResponseStatus::OK:
			case ResponseStatus::ReadyToAcceptData:
				if (!ReceiveTextBuffer(buffer.get(), responseLength))
					return false;
				response = std::string((char*)buffer.get());
				break;

			case ResponseStatus::Multiline:
				if (!ReceiveBinary(buffer.get(), (statusLength == -1) ? 0x1C : statusLength, bytesRecieved))
					return false;
				ZeroMemory(buffer.get(), responseLength);

				// the end of the response always contains "\r\n." or ".\r\n"
				while (response.find("\r\n.") == std::string::npos && response.find(".\r\n") == std::string::npos)
				{
					ZeroMemory(buffer.get(), 0x400);

					if (!ReceiveTextBuffer(buffer.get(), 0x400))
						return false;
					response += std::string((char*)buffer.get(), 0x400);
				}
				break;

			case ResponseStatus::Binary:
				// read off "binary response follows"
				if (!ReceiveBinary(buffer.get(), (statusLength == -1) ? 0x19 : statusLength, bytesRecieved))
					return false;

				// let the caller deal with reading the stream
				break;

			case ResponseStatus::Error:
				if (!ReceiveTextBuffer(buffer.get(), responseLength))
					return false;
				response = std::string((char*)buffer.get());

				break;
			default:
				return false;
		}

		// trim off the leading and trailing whitespace
		response.erase(response.begin(), std::find_if(response.begin(), response.end(), [](unsigned char c) { return !std::isspace(c); }));
		response.erase(std::find_if(response.rbegin(), response.rend(), [](unsigned char c) { return !std::isspace(c); }).base(), response.end());

		return true;
	}

	bool Console::ReceiveTimeout(char* buffer, int length, int flags, DWORD& bytesReceived)
	{
		bytesReceived = recv(m_Socket, buffer, length, flags);
		if (bytesReceived == SOCKET_ERROR)
			return false;
		return true;
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

	DWORD Console::GetIntegerProperty(std::string& response, const std::string& propertyName, bool* success, bool hex, bool update)
	{
		// all of the properties are like this: NAME=VALUE
		size_t startIndex = response.find(propertyName) + propertyName.size() + 1;
		size_t spaceIndex = response.find(' ', startIndex);
		size_t crIndex = response.find('\r', startIndex);
		size_t endIndex = (spaceIndex != -1 && spaceIndex < crIndex) ? spaceIndex : crIndex;

		if (response.find(propertyName) == std::string::npos)
		{
			*success = false;
			return 0;
		}

		DWORD toReturn;
		if (hex)
			std::istringstream(response.substr(startIndex, endIndex - startIndex)) >> std::hex >> toReturn;
		else
			std::istringstream(response.substr(startIndex, endIndex - startIndex)) >> toReturn;

		if (update)
			response = response.substr(endIndex);

		*success = true;

		return toReturn;
	}

	std::string Console::GetStringProperty(std::string& response, const std::string& propertyName, bool* success, bool update)
	{
		// all string properties are like this: NAME="VALUE"
		size_t startIndex = response.find(propertyName) + propertyName.size() + 2;
		size_t endIndex = response.find('"', startIndex);

		if (response.find(propertyName) == std::string::npos)
		{
			*success = false;
			return "";
		}

		std::string toReturn = response.substr(startIndex, endIndex - startIndex);

		if (update)
			response = response.substr(endIndex);
		*success = true;
		return toReturn;
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
