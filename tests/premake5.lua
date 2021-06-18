project "tests"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/" .. TargetDir .. "/%{prj.name}")
	objdir ("%{wks.location}/" .. ObjDir .. "/%{prj.name}")

	files {
		"src/**.cpp"
	}

	includedirs {
		"%{wks.location}/XBDM/src",
		"vendor/googletest/googletest/include"
	}

	links {
		"XBDM",
		"gtest"
	}

	filter "system:not macosx"
		linkgroups "on"

	filter "system:windows"
		systemversion "latest"
		links {"Ws2_32.lib"}

	filter "system:linux"
		systemversion "latest"
		links {"pthread"}

	filter "system:macosx"
		linkoptions {
			"-framework Cocoa",
			"-framework IOKit",
			"-framework CoreFoundation"
		}

	
    filter "configurations:Debug"
		runtime "Debug"
		defines "DEBUG"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		defines "RELEASE"
		optimize "on"
