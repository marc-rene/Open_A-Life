-- premake5.lua
workspace "Open A-Life"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Example"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "Core/Build-Core.lua"
group ""
   
include "Example/Build-App.lua"