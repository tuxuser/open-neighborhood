workspace "OpenNeighborhood"
	architecture "x86_64"
	startproject "OpenNeighborhood"

	configurations {
		"Debug",
		"Release"
	}

	flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/OpenNeighborhood/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/OpenNeighborhood/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/OpenNeighborhood/vendor/ImGui"
IncludeDir["stb_image"] = "%{wks.location}/OpenNeighborhood/vendor/stb_image"

group "Dependencies"
	include "OpenNeighborhood/vendor/GLFW"
	include "OpenNeighborhood/vendor/Glad"
	include "OpenNeighborhood/vendor/ImGui"
group ""

include "OpenNeighborhood"
include "XBDM"
