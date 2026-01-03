workspace "RayTracingOneWeek"
architecture "x64"
configurations {"Debug", "Release"}

startproject "RayTracingOneweek"

outputdir = "%{cfg.buidcfg}-%{cfg.system}-%{cfg.architecure}"

project "RayTracingOneWeek"
    location "RayTracingOneWeek"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("bin/" .. outputdir .."/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.hpp"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
    
    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"
