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
IncludeDir["xbdm"] = "%{wks.location}/OpenNeighborhood/vendor/xbdm"
IncludeDir["GLFW"] = "%{wks.location}/OpenNeighborhood/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/OpenNeighborhood/vendor/Glad/include"

group "Dependencies"
	include "OpenNeighborhood/vendor/xbdm"
	include "OpenNeighborhood/vendor/GLFW"
	include "OpenNeighborhood/vendor/Glad"
group ""

include "OpenNeighborhood"
