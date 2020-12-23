#pragma once

#include "Core.h"
#include "Log.h"

#ifdef ENABLE_ASSERTS
	#define ASSERT(check, ...) { if(!(check)) { LOG_ERROR("Assertion Failed: ", __VA_ARGS__); DEBUGBREAK(); } }
#else
	#define ASSERT(...)
#endif
