workspace "MineClone"
    configurations { "Debug", "Release" }
    architecture "x86_64"

    location "MineClone"

    language "C++"
    startproject "MineClone"
    cppdialect "C++17"

    objdir "obj/%{cfg.buildcfg}/%{prj.name}"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

----------------- libs -----------------
group "vendor"
    ----------- glad ----------- 
    project "glad"
        kind "StaticLib"
        targetdir "lib/%{cfg.buildcfg}/%{prj.name}"
        includedirs { "vendor/glad/include" }

        files { "vendor/glad/include/**.h", "vendor/glad/src/**.c" }

    ----------- FastNoise ----------- 
    project "FastNoise"
        kind "StaticLib"
        targetdir "lib/%{cfg.buildcfg}/%{prj.name}"

        files { "vendor/FastNoise/**.h", "vendor/FastNoise/**.cpp" }

    ----------- Google Test ----------- 
    project "googletest"
        kind "StaticLib"
        targetdir "lib/%{cfg.buildcfg}/%{prj.name}"
        includedirs 
        { 
            "vendor/googletest/googletest",
            "vendor/googletest/googletest/include", 
            "googletest/googletest/include/internal"
        }

        files { "vendor/googletest/googletest/include/**.h", "vendor/googletest/googletest/src/**.cc" }

        excludes { "vendor/googletest/googletest/src/gtest-all.cc" }

----------------- Main project -----------------
group ""
project "MineClone"
    kind "ConsoleApp"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs { "MineClone/src", "vendor/glad/include", "vendor/glfw/include", "vendor/glm", "vendor/stb", "vendor/FastNoise" }
    debugdir "MineClone/assets"

    libdirs { "vendor/glfw/src/%{cfg.longname}" }
    links { "glad", "glfw3", "FastNoise" }

    files { "MineClone/src/**.hpp", "MineClone/src/**.cpp" }

project "tests"
    kind "ConsoleApp"
    targetdir "tests/%{cfg.buildcfg}"
    includedirs { "MineClone/src", "vendor/googletest/googletest/include", "vendor/glad/include", "vendor/glfw/include", "vendor/glm", "vendor/stb", "vendor/FastNoise" }
    
    libdirs { "vendor/glfw/src/%{cfg.longname}" }
    links { "MineClone", "googletest", "glad", "glfw3", "FastNoise" }

    files { "MineClone/tests/**.hpp", "MineClone/tests/**.cpp" }
