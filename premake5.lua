workspace "OpenNeighborhood"
	architecture "x86"
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

group "Dependencies"
	include "OpenNeighborhood/vendor/xbdm"
group ""

include "OpenNeighborhood"
