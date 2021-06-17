#pragma once

#include "Definitions.h"

namespace XBDM
{
	class Console
	{
	public:
		Console();
		Console(const std::string& ipAddress);

		bool OpenConnection();
		bool CloseConnection();

		std::string GetName();
		std::vector<Drive> GetDrives();
		std::vector<File> GetDirectoryContents(const std::string& directoryPath);
	private:
		bool m_Connected = false;
		std::string m_IpAddress;
		SOCKET m_Socket;

		std::string Receive();
		void SendCommand(const std::string& command);

		std::vector<std::string> SplitResponse(const std::string& response, const std::string& delimiter);
		bool EndsWith(const std::string& line, const std::string& ending);

		DWORD GetIntegerProperty(const std::string& line, const std::string& propertyName, bool hex = true);
		std::string GetStringProperty(const std::string& line, const std::string& propertyName);

		void CleanupSocket();
		void CloseSocket();

		void SleepFor(DWORD milliseconds);
	};
}
