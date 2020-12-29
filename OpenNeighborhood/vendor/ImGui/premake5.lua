project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
        "imgui_custom_widgets.h",
        "imgui_custom_widgets.cpp",
		"imgui_draw.cpp",
        "imgui_impl_glfw.cpp",
        "imgui_impl_glfw.h",
        "imgui_impl_opengl3.cpp",
        "imgui_impl_opengl3.h",
		"imgui_internal.h",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
		"imgui_demo.cpp"
	}

    includedirs {
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "on"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
