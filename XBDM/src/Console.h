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

		bool SendBinary(const BYTE* buffer, DWORD length);
		bool SendCommand(const std::string& command);
		bool SendCommand(const std::string& command, std::string& response, DWORD responseLength = 0x400, DWORD statusLength = -1);
		bool SendCommand(const std::string& command, std::string& response, ResponseStatus& status, DWORD responseLength = 0x400, DWORD statusLength = -1);

		bool ReceiveTextBuffer(BYTE* buffer, DWORD length);
		bool ReceiveBinary(BYTE* buffer, DWORD length, DWORD& bytesRecieved);
		bool ReceiveResponse(std::string& response, ResponseStatus& status, DWORD responseLength = 0x400, DWORD statusLength = -1);
		bool ReceiveTimeout(char* buffer, int length, int flags, DWORD& bytesReceived);

		std::vector<std::string> SplitResponse(const std::string& response, const std::string& delimiter);
		DWORD GetIntegerProperty(std::string& response, const std::string& propertyName, bool* success, bool hex, bool update = false);
		std::string GetStringProperty(std::string& response, const std::string& propertyName, bool* success, bool update = false);

		void SleepFor(DWORD milliseconds);
	};
}
