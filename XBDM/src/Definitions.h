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

	enum class DebugMemStatus
	{
		NoAdditionalMemory = 0,
		AdditionalMemoryDisabled = 1,
		AdditionalMemoryEnabled = 2,

		Undefined = 0xFF
	};

	enum class DumpMode
	{
		Smart = 0,
		Enabled = 1,
		Disabled = 2,

		Undefined = 0xFF
	};

	enum class DumpReport
	{
		Prompt = 0,
		Always = 1,
		Never = 2,

		Undefined = 0xFF
	};

	enum class DumpDestination
	{
		Local = 0,
		Remote = 1,

		Undefined = 0xFF
	};

	enum class DumpFormat
	{
		FullHeap = 0,
		PartialHeap = 1,
		NoHeap = 2,         
		Retail = 3,

		Undefined = 0xFF
	};

	enum class MemoryRegionFlags
	{
		Execute = 0x10,
		ExecuteRead = 0x20,
		ExecuteReadWrite = 0x40,
		ExecuteWriteCopy = 0x80,
		Guard = 0x100,
		NoAccess = 1,
		NoCache = 0x200,
		ReadOnly = 2,
		ReadWrite = 4,
		UserReadOnly = 0x1000,
		UserReadWrite = 0x2000,
		WriteCombine = 0x400,
		WriteCopy = 8,

		Undefined = 0xFF
	};

	struct MemoryRegion
	{
		DWORD BaseAddress;
		DWORD Size;
		std::string Protection;
	};

	struct DumpSettings
	{
		DumpReport Report;
		DumpDestination Destination;
		DumpFormat Format;

		std::string Path;
	};

	struct Drive
	{
		std::string Name;
		UINT64 FreeBytesAvailable;
		UINT64 TotalBytes;
		UINT64 TotalFreeBytes;
		std::string FriendlyName;
	};

	struct SystemInformation
	{
		bool HddEnabled;
		std::string Platform;
		std::string System;
		std::string BaseKernelVersion;
		std::string KernelVersion;
		std::string RecoveryVersion;
	};

	struct FileEntry
	{
		std::string Name;
		UINT64 Size;
		time_t CreationTime;
		time_t ModifiedTime;

		bool IsDirectory;
	};

	struct ModuleSection
	{
		std::string Name;
		DWORD BaseAddress;
		DWORD Size;
		DWORD Index;
		DWORD Flags;
	};

	struct Module
	{
		std::string Name;
		DWORD BaseAddress;
		DWORD Size;
		DWORD Checksum;
		DWORD Timestamp;
		DWORD DataAddress;
		DWORD DataSize;
		DWORD ThreadId;
		DWORD OriginalSize;

		std::vector<ModuleSection> Sections;
	};

	struct LocalDirent
	{
		std::string Name;
		bool IsDirectory;
	};

	struct Thread
	{
		DWORD Id;
		DWORD SuspendCount;
		DWORD Priority;
		DWORD TlsBaseAddress;
		DWORD BaseAddress;
		DWORD StartAddress;
		DWORD StackBaseAddress;
		DWORD StackLimitAddress;
		time_t CreationTime;
		DWORD StackSlackSpace;
		DWORD NameAddress;
		DWORD NameLength;
		WORD CurrentProcessor;
		DWORD LastError;
	};

	struct GamepadState
	{
		bool DpadUp : 1;
		bool dpadDown : 1;
		bool DpadLeft : 1;
		bool DpadRight : 1;
		bool Start : 1;
		bool Back : 1;
		bool LeftStick : 1;
		bool RightStick : 1;
		bool LeftBumper : 1;
		bool RightBumper : 1;
		bool CenterButton : 1;
		bool ButtonBind : 1;
		bool A : 1;
		bool B : 1;
		bool X : 1;
		bool Y : 1;

		// the amount of pressure put on the trigger
		BYTE LeftTrigger;
		BYTE LightTrigger;

		// Each of the thumbstick axis members is a signed
		// value describing the position of the thumbstick.
		// A value of 0 is centered. Negative values signify down
		// or to the left. Positive values signify up or to the right.
		SHORT LeftStickX;
		SHORT LeftStickY;
		SHORT RightStickX;
		SHORT RightStickY;
	};
};
