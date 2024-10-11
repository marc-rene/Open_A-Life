project "Example"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp", "Source/**.hpp", "imgui/**.cpp", "imgui/**.h", "imgui/**.hpp" }

   includedirs
   {
        "Source",
        "imgui",
        "imgui\\backends",
        -- Include Core
        "../Core/Source",
        "$(SolutionDir)Core",
        "$(SolutionDir)Core\\Source",
        "$(SolutionDir)Core\\Source\\Core",
        "$(SolutionDir)Core\\ThirdParty\\csv\\single_include",
        "$(SolutionDir)Core\\ThirdParty\\spdlog\\include",
        "$(SolutionDir)Example\\imgui",
        "$(SolutionDir)Example\\imgui\\backends"
   }

   links
   {
      "Core"
      "d3d9"
   }

   -- Create virtual paths for modules
   vpaths {
    ["Visualiser/*"] = { "imgui/**.cpp", "imgui/**.h", "imgui/**.hpp" }
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