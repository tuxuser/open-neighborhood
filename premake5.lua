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

group "Dependencies"
	include "OpenNeighborhood/vendor/xbdm"
	include "OpenNeighborhood/vendor/GLFW"
group ""

include "OpenNeighborhood"
