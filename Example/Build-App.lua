project "Example"
kind "ConsoleApp"
language "C++"
cppdialect "C++23"
targetdir "Binaries/%{cfg.buildcfg}"
staticruntime "off"

files { "Source/**.h",              "Source/**.cpp",            "Source/**.hpp", 
        "ThirdParty\\imgui/**.cpp", "ThirdParty\\imgui/**.h",   "ThirdParty\\imgui/**.hpp", 
        "misc/Styles/**.cpp",       "misc/Styles/**.h",         "misc/Styles/**.hpp",
        "misc/Windows/**.cpp",      "misc/Windows/**.h",
        "misc/3D Utils/**.cpp",      "misc/3D Utils/**.h"}

includedirs {   "$(SolutionDir)Core\\Include", -- Include La Core
                "$(SolutionDir)Example\\ThirdParty\\imgui", 
                "$(SolutionDir)Example\\ThirdParty\\imgui\\backends",
                "$(SolutionDir)Example\\ThirdParty\\DirectXhelper\\Inc", 
                "$(SolutionDir)Example\\ThirdParty",
                "$(SolutionDir)Example\\misc",

                -- TODO: Fix this inclusion madness and have everything be one single include
                "$(SolutionDir)Core\\Source",
                "$(SolutionDir)Core\\ThirdParty\\AI_Pathfinding\\Recast\\Include",
                "$(SolutionDir)Core\\ThirdParty\\AI_Pathfinding\\Detour\\Include",
                "$(SolutionDir)Core\\ThirdParty\\mINI\\src\\mini", 
                "$(SolutionDir)Core\\ThirdParty\\csv\\single_include",
                "$(SolutionDir)Core\\ThirdParty\\spdlog\\include"
            }

removefiles {   "ThirdParty\\imgui\\backends\\imgui_impl_allegro5.cpp",
                "ThirdParty\\imgui\\backends\\imgui_impl_allegro5.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_android.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_android.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_dx10.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_dx10.h",
                "!ThirdParty\\imgui\\backends\\imgui_impl_dx11.cpp", -- Keep 
                "!ThirdParty\\imgui\\backends\\imgui_impl_dx11.h", -- Keep
                "ThirdParty\\imgui\\backends\\imgui_impl_dx12.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_dx12.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_dx9.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_dx9.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_glfw.cpp",
                "ThirdParty\\imgui\\backends\\imgui_impl_glfw.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_glut.cpp",
                "ThirdParty\\imgui\\backends\\imgui_impl_glut.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_metal.h", 
                "ThirdParty\\imgui\\backends\\imgui_impl_metal.mm",
                "ThirdParty\\imgui\\backends\\imgui_impl_opengl2.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_opengl2.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_opengl3.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_opengl3.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_opengl3_loader.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_osx.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_osx.mm",
                "ThirdParty\\imgui\\backends\\imgui_impl_sdl2.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_sdl2.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_sdl3.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_sdl3.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_sdlgpu3.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_sdlgpu3.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_sdlrenderer2.cpp",
                "ThirdParty\\imgui\\backends\\imgui_impl_sdlrenderer2.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_sdlrenderer3.cpp",
                "ThirdParty\\imgui\\backends\\imgui_impl_sdlrenderer3.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_vulkan.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_vulkan.h",
                "ThirdParty\\imgui\\backends\\imgui_impl_wgpu.cpp", 
                "ThirdParty\\imgui\\backends\\imgui_impl_wgpu.h",
                "!ThirdParty\\imgui\\backends\\imgui_impl_win32.cpp", -- Keep
                "!ThirdParty\\imgui\\backends\\imgui_impl_win32.h", -- Keep
                "ThirdParty\\imgui\\backends\\vulkan/*", 
                "ThirdParty\\imgui\\examples/**",
                "ThirdParty\\imgui\\misc\\freetype/**",
                "ThirdParty\\imgui\\misc\\fonts/**.cpp"}

links {"Core", "d3d11"}

-- Create virtual paths for modules
vpaths {
    ["Visualiser/ImGui"] = {"imgui/**.cpp", "imgui/**.h", "imgui/**.hpp"},
    ["Visualiser/misc"] = {"misc/Styles/**.cpp", "misc/Styles/**.h"},
    ["Visualiser/Windows"] = {"misc/Windows/**.cpp", "misc/Windows/**.h"},
    ["Visualiser/3D Utils"] = {"misc/3D Utils/**.cpp", "misc/3D Utils/**.h"}
}

targetdir("../Binaries/" .. OutputDir .. "/%{prj.name}")
objdir("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

filter "system:windows"
systemversion "latest"
defines {"WINDOWS"}

filter "configurations:Debug"
defines {"DEBUG", "FMT_UNICODE=0"}
runtime "Debug"
symbols "On"

filter "configurations:Release"
defines {"RELEASE", "FMT_UNICODE=0"}
runtime "Release"
optimize "On"
symbols "On"

filter "configurations:Dist"
defines {"DIST", "FMT_UNICODE=0"}
runtime "Release"
optimize "On"
symbols "Off"
