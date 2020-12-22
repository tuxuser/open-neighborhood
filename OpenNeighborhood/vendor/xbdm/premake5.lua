project "xbdm"
	kind "StaticLib"
	language "C++"
	cppdialect "C++14"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"**.h",
		"**.cpp"
	}

	filter "system:windows"
		systemversion "latest"
		links {
			"Ws2_32.lib",
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
		
		defines {
			"__WIN32" -- XBDM uses __WIN32 instead of WIN32 to detect Windows
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
