project "gtest"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"
	staticruntime "on"

	targetdir ("%{wks.location}/" .. TargetDir .. "/%{prj.name}")
	objdir ("%{wks.location}/" .. ObjDir .. "/%{prj.name}")

	files {
		"googletest/googletest/include/**.h",
        "googletest/googletest/src/**.cc",
	}

	excludes {
		"googletest/googletest/src/gtest-all.cc"
	}

	includedirs {
        "googletest/googletest/include",
        "googletest/googletest"
	}

	filter "system:linux"
		buildoptions {"-pthread"}

	filter "system:windows"
		systemversion "latest"
	
    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
