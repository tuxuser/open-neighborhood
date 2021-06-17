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

OutputDir = "%{cfg.buildcfg}-%{cfg.system}"
TargetDir = "bin/" .. OutputDir
ObjDir = "bin-int/" .. OutputDir

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/OpenNeighborhood/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/OpenNeighborhood/vendor/Glad/include"

group "Dependencies"
	include "OpenNeighborhood/vendor/GLFW"
	include "OpenNeighborhood/vendor/Glad"
	include "OpenNeighborhood/vendor/ImGui"
	include "tests/vendor"
group ""

include "OpenNeighborhood"
include "XBDM"
include "tests"
