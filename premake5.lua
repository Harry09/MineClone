workspace "MineClone"
    configurations { "Debug", "Release" }
    architecture "x86_64"

    location "MineClone"

    language "C++"
    startproject "MineClone"
    cppdialect "C++17"

    objdir "obj/%{prj.name}/%{cfg.buildcfg}"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

----------------- libs -----------------
----------- glad ----------- 
project "glad"
    kind "StaticLib"
    targetdir "lib/%{cfg.buildcfg}"
    includedirs { "vendor/glad/include" }

    files { "vendor/glad/include/**.h", "vendor/glad/src/**.c" }

project "FastNoise"
    kind "StaticLib"
    targetdir "lib/%{cfg.buildcfg}"

    files { "vendor/FastNoise/**.h", "vendor/FastNoise/**.cpp" }

----------------- Main project -----------------
project "MineClone"
    kind "ConsoleApp"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs { "MineClone/src", "vendor/glad/include", "vendor/glfw3/include", "vendor/glm", "vendor/stb", "vendor/FastNoise" }
    debugdir "MineClone/assets"

    libdirs { "vendor/glfw3/src/%{cfg.longname}" }
    links { "glad", "glfw3", "FastNoise" }

    files { "MineClone/src/**.hpp", "MineClone/src/**.cpp" }
