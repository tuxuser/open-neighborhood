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

namespace XBDM
{
	struct Drive
	{
		std::string Name;
		UINT64 FreeBytesAvailable;
		UINT64 TotalBytes;
		UINT64 TotalFreeBytes;
		UINT64 TotalUsedBytes;
		std::string FriendlyName;
	};

	struct File
	{
		std::string Name;
		UINT64 Size;
		bool IsXEX;
		bool IsDirectory;
	};
};
