workspace "MineClone"
    configurations { "Debug", "Release" }
    architecture "x86_64"

    location "MineClone"

    language "C++"
    startproject "MineClone"
    cppdialect "C++17"

    
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


----------------- Main project -----------------
project "MineClone"
    kind "ConsoleApp"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs { "vendor/glad/include", "vendor/glfw3/include", "vendor/glm" }

    libdirs { "vendor/glfw3/src/%{cfg.longname}" }
    links { "glad", "glfw3" }

    files { "MineClone/src/**.hpp", "MineClone/src/**.cpp" }
