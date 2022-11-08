workspace ("GDENG-2 Project")
    startproject "GDENG-2 Project"

    configurations {
        "Debug",
        "Release"
    }

    platforms {
    	"Win32",
    	"Win64"
    }

    flags {
        "MultiProcessorCompile"
    }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

--DependencyDir = "%{ProjectName}/Dependencies"
--SourceDir = "%{ProjectName}/Source"

DependenciesDir = {}

project ("GDENG-2 Project")
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    toolset "v143"

    files {
        "GDENG-2 Project/**.cpp",
        "GDENG-2 Project/**.h"
    }

    vpaths {
        ["Header Files"] = {
            "GDENG-2 Project/*.h",
            "GDENG-2 Project/*.hpp"
        },
        ["Source Files"] = {
            "GDENG-2 Project/*.cpp",
            "GDENG-2 Project/*.inl"
        }
    }

    includedirs {
        "GDENG-2 Project"
    }

    defines {
    }

    links {
        "d3d11.lib",
        "d3dcompiler.lib"
    }


    filter "platforms:Win32"
		system "Windows"
		architecture "x32"
        systemversion "latest"

    filter "platforms:Win64"
    	system "Windows"
    	architecture "x64"
        systemversion "latest"

    filter "configurations:Debug"
        defines "DEBUG" 
		runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "RELEASE" 
        runtime "Release"
        optimize "on"