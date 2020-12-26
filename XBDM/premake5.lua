project "XBDM"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	files {
		"src/**.h",
		"src/**.cpp",
		"vendor/**.h",
		"vendor/**.cpp"
	}

	includedirs {
		"src",
		"vendor/dirent"
	}

	filter "system:windows"
		systemversion "latest"
		links {
			"Ws2_32.lib"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
