#ifdef _WIN32 // Windows x64/x86
	#ifdef _WIN64 // windows x64
		#define PLATFORM_WINDOWS
	#else // Windows x86
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__linux__)
	#define PLATFORM_LINUX
#elif defined(__APPLE__)
	#define PLATFORM_MACOS
#else
	#error "Unknown platform!"
#endif
