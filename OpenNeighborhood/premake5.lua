project "OpenNeighborhood"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"%{IncludeDir.xbdm}"
	}

	links {
		"xbdm"
	}

	filter "system:windows"
		systemversion "latest"
		links {
			"kernel32.lib",
			"user32.lib",
			"gdi32.lib",
			"winspool.lib",
			"comdlg32.lib",
			"advapi32.lib",
			"shell32.lib",
			"ole32.lib",
			"oleaut32.lib",
			"uuid.lib",
			"odbc32.lib",
			"odbccp32.lib"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
