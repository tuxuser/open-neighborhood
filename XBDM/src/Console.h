#pragma once

#include "Definitions.h"

/**
* This library is inspired (pretty much copied) by Experiment5X's library also called XBDM (https://github.com/Experiment5X/XBDM).
* I would use his library instead of making one but his repository does not contain a license, 
* which prevents me from using it and republishing it.
*/

namespace XBDM {
	class Console
	{
	public:
		Console();
		Console(const std::string& ipAddress);

		bool OpenConnection();
		bool CloseConnection();

		std::string GetConsoleName(bool* success);
		std::vector<Drive> GetDrives(bool* success);
		std::vector<FileEntry> GetDirectoryContents(const std::string& directoryPath, bool* success);
	private:
		bool m_Connected = false;
		std::string m_IpAddress;
		SOCKET m_Socket;

		void CleanupSocket();
		void CloseSocket();

		bool SendBinary(const char* buffer, DWORD length);
		bool SendCommand(const std::string& command);
		bool SendCommand(const std::string& command, std::string* response);

		bool ReceiveTextBuffer(char* buffer, DWORD length);
		bool ReceiveResponse(std::string* response);
		bool ReceiveBinary(char* buffer, int length, int flags = 0);

		std::vector<std::string> SplitResponse(const std::string& response, const std::string& delimiter);
		DWORD GetIntegerProperty(const std::string& line, const std::string& propertyName, bool* success, bool hex);
		std::string GetStringProperty(const std::string& line, const std::string& propertyName, bool* success);

		void SleepFor(DWORD milliseconds);
	};
}
