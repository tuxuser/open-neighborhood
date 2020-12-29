project "OpenNeighborhood"
	kind "ConsoleApp"
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
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp"
	}

	includedirs {
		"src",
		"%{wks.location}/XBDM/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}"
	}

	defines {
		"GLFW_INCLUDE_NONE"
	}

	linkgroups "on"

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"XBDM"
	}

	filter "system:windows"
		systemversion "latest"
		links {
			"opengl32.lib"
		}

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		defines "RELEASE"
		optimize "on"
