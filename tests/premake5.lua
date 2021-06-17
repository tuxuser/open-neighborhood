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

	defines {
		"GLFW_INCLUDE_NONE"
	}

	links {
		"XBDM",
		"gtest"
	}

	filter "system:linux"
		linkoptions {"-pthread"}

	filter "system:windows"
		systemversion "latest"
	
    filter "configurations:Debug"
		runtime "Debug"
		defines "DEBUG"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		defines "RELEASE"
		optimize "on"