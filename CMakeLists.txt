cmake_minimum_required(VERSION 3.15)
project(MineClone)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vendor)

file(
    GLOB_RECURSE MineClone_src
    "${CMAKE_SOURCE_DIR}/Mineclone/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/Mineclone/src/*.hpp"
    )

add_executable(MineClone ${MineClone_src})

if (MSVC)
    set_property(TARGET MineClone PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/MineClone/assets")
endif()

find_library(GLFW_LIBRARY 
            NAMES glfw glfw3 
            HINTS "${CMAKE_SOURCE_DIR}/vendor/glfw"
            PATH_SUFFIXES src src/Debug src/Release
            )


target_link_libraries(MineClone PUBLIC glad FastNoise ${GLFW_LIBRARY})
target_include_directories(MineClone PUBLIC 
                            "${CMAKE_SOURCE_DIR}/MineClone/src"
                            "${CMAKE_SOURCE_DIR}/vendor/glm"
                            "${CMAKE_SOURCE_DIR}/vendor/stb"
                            "${CMAKE_SOURCE_DIR}/vendor/FastNoise"
                            "${CMAKE_SOURCE_DIR}/vendor/glfw/include"
                        )
