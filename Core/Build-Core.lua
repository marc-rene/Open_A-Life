project "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"

    files { "Source/**.h", "Source/**.cpp", "Source/**.hpp" }

    includedirs
    {
        "Include",
        "Source",
        "$(SolutionDir)Core",
        "$(SolutionDir)Core\\Source",
        "$(SolutionDir)Core\\ThirdParty\\csv\\single_include",
        "$(SolutionDir)Core\\ThirdParty\\spdlog\\include"
    }

    -- Create virtual paths for modules
    vpaths {
        ["Core/Public/*"]                   = { "Source/Core/**.h",                 "Source/Core/**.hpp",   "Include/**.h" },  -- CORE
        ["Modules/Gossiper/Public/*"]       = { "Source/Modules/Gossiper/**.h",     "Source/Modules/Gossiper/**.hpp"    },  -- Gossiper module
        ["Modules/Packet Ninja/Public/*"]   = { "Source/Modules/Packet Ninja/**.h", "Source/Modules/Packet Ninja/**.hpp"},  -- Packet Ninja module
        ["Modules/Director/Public/*"]       = { "Source/Modules/Director/**.h",     "Source/Modules/Director/**.hpp"    },  -- Director module
        ["Modules/File Wizard/Public/*"]    = { "Source/Modules/File Wizard/**.h",  "Source/Modules/File Wizard/**.hpp" },  -- File Wizard module
        
        ["Core/Private/*"]                  = {"Source/Core/**.cpp",                "Source/Core/**.c", "Include/**.cpp" },
        ["Modules/Gossiper/Private/*"]      = {"Source/Modules/Gossiper/**.cpp",    "Source/Modules/Gossiper/**.c"      },
        ["Modules/Packet Ninja/Private/*"]  = {"Source/Modules/Packet Ninja/**.cpp","Source/Modules/Packet Ninja/**.c"  },
        ["Modules/Director/Private/*"]      = {"Source/Modules/Director/**.cpp",    "Source/Modules/Director/**.c"      },
        ["Modules/File Wizard/Private/*"]   = {"Source/Modules/File Wizard/**.cpp", "Source/Modules/File Wizard/**.c"   },

        ["Core/Tests/*"] = { "Tests/**.cpp", "Tests/**.h",   "Tests/**.hpp"  }   -- make sure we have some testing too
    }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

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