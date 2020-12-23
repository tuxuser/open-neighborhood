#pragma once

#include "PlatformDetector.h"

#ifdef DEBUG
	#if defined(PLATFORM_WINDOWS)
		#define DEBUGBREAK() __debugbreak()
	#elif defined(PLATFORM_LINUX)
		#include <signal.h>
		#define DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define ENABLE_ASSERTS
#else
	#define DEBUGBREAK()
#endif
