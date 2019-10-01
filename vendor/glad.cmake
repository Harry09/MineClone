file(GLOB glad_src
"glad/src/*.c"
"glad/include/*.h"
)

add_library(
    glad STATIC
    ${glad_src}
)

target_include_directories(glad PRIVATE "glad/src")
target_include_directories(glad PUBLIC "glad/include")
