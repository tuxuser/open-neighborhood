#pragma once
#include "pch.h"

#ifndef _WIN32
	typedef uint8_t     BYTE;
	typedef int16_t     SHORT;
	typedef uint16_t    WORD;
	typedef uint32_t    DWORD;
	typedef uint64_t    UINT64;

	#define ZeroMemory(buff, len) memset(buff, 0, len)
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1

	typedef int SOCKET;
#endif

#define FILETIME_TO_TIMET(time) ((time_t)(time / 10000000L - 11644473600L))

namespace XBDM
{
	enum class ResponseStatus
	{
		OK = 200,
		Multiline = 202,
		Binary = 203,
		ReadyToAcceptData = 204,
		Error = 405
	};

	struct Drive
	{
		std::string Name;
		UINT64 FreeBytesAvailable;
		UINT64 TotalBytes;
		UINT64 TotalFreeBytes;
		std::string FriendlyName;
	};

	struct FileEntry
	{
		std::string Name;
		UINT64 Size;
		time_t CreationTime;
		time_t ModifiedTime;

		bool IsDirectory;
	};
};
