project "Example"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files {  "Source/**.h",      "Source/**.cpp",    "Source/**.hpp", 
            "imgui/**.cpp",     "imgui/**.h",       "imgui/**.hpp", 
            "misc/Styles/**.cpp", "misc/Styles/**.h", "misc/Styles/**.hpp", 
            "misc/Windows/**.cpp", "misc/Windows/**.h" }

   includedirs
   {
        "Source",
        "imgui",
        "imgui\\backends",

        -- Include Core
        "$(SolutionDir)Core",
        "$(SolutionDir)Core\\Source",
        "$(SolutionDir)Core\\Include",
        "$(SolutionDir)Core\\ThirdParty\\csv\\single_include",
        "$(SolutionDir)Core\\ThirdParty\\spdlog\\include",
        "$(SolutionDir)Example\\imgui",
        "$(SolutionDir)Example\\imgui\\backends",
        "$(SolutionDir)Example\\misc"
   }


   removefiles
   {
    "imgui\\backends\\imgui_impl_allegro5.cpp",  
    "imgui\\backends\\imgui_impl_allegro5.h",    
    "imgui\\backends\\imgui_impl_android.cpp",   
    "imgui\\backends\\imgui_impl_android.h",     
    "!imgui\\backends\\imgui_impl_dx10.cpp",     -- Keep
    "!imgui\\backends\\imgui_impl_dx10.h",       -- Keep
    "!imgui\\backends\\imgui_impl_dx11.cpp",     -- Keep 
    "!imgui\\backends\\imgui_impl_dx11.h",       -- Keep
    "imgui\\backends\\imgui_impl_dx12.cpp",      
    "imgui\\backends\\imgui_impl_dx12.h",        
    "!imgui\\backends\\imgui_impl_dx9.cpp",      -- Keep
    "!imgui\\backends\\imgui_impl_dx9.h",        -- Keep
    "imgui\\backends\\imgui_impl_glfw.cpp",      
    "imgui\\backends\\imgui_impl_glfw.h",        
    "imgui\\backends\\imgui_impl_glut.cpp",      
    "imgui\\backends\\imgui_impl_glut.h",        
    "imgui\\backends\\imgui_impl_metal.h",       
    "imgui\\backends\\imgui_impl_metal.mm",      
    "imgui\\backends\\imgui_impl_opengl2.cpp",   
    "imgui\\backends\\imgui_impl_opengl2.h", 
    "imgui\\backends\\imgui_impl_opengl3.cpp",
    "imgui\\backends\\imgui_impl_opengl3.h",
    "imgui\\backends\\imgui_impl_opengl3_loader.h",
    "imgui\\backends\\imgui_impl_osx.h",
    "imgui\\backends\\imgui_impl_osx.mm",
    "imgui\\backends\\imgui_impl_sdl2.cpp",
    "imgui\\backends\\imgui_impl_sdl2.h",
    "imgui\\backends\\imgui_impl_sdl3.cpp",
    "imgui\\backends\\imgui_impl_sdl3.h",
    "imgui\\backends\\imgui_impl_sdlrenderer2.cpp",
    "imgui\\backends\\imgui_impl_sdlrenderer2.h",
    "imgui\\backends\\imgui_impl_sdlrenderer3.cpp",
    "imgui\\backends\\imgui_impl_sdlrenderer3.h",
    "imgui\\backends\\imgui_impl_vulkan.cpp",
    "imgui\\backends\\imgui_impl_vulkan.h",
    "imgui\\backends\\imgui_impl_wgpu.cpp",
    "imgui\\backends\\imgui_impl_wgpu.h",
    "!imgui\\backends\\imgui_impl_win32.cpp",    -- Keep
    "!imgui\\backends\\imgui_impl_win32.h",      -- Keep
    "imgui\\backends\\vulkan/*",

    "imgui\\examples/**",
    "imgui\\misc\\freetype/**",
    "imgui\\misc\\fonts/**.cpp"
   }

   links
   {
      "Core",
      "d3d11"
   }

   

   -- Create virtual paths for modules
   vpaths {
    ["Visualiser/ImGui"] = { "imgui/**.cpp", "imgui/**.h", "imgui/**.hpp" },
    ["Visualiser/misc"] = {"misc/Styles/**.cpp", "misc/Styles/**.h"},
    ["Visualiser/Windows"] = {"misc/Windows/**.cpp", "misc/Windows/**.h" }
    }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"