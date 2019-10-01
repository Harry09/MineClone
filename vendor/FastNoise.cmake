file(GLOB FastNoise_src
"FastNoise/*.cpp"
"FastNoise/*.h"
)

add_library(
    FastNoise STATIC
    ${FastNoise_src}
)

target_include_directories(FastNoise PRIVATE "FastNoise/")
