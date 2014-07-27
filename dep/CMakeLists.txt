include_directories(include include/intlib)
include_directories(include include/json)

file(GLOB enet_src src/enet/*.c)
file(GLOB intlib_src src/intlib/*.cpp)
file(GLOB libjson_src src/libjson/*.cpp)

add_library(enet ${enet_src})
add_library(intlib ${intlib_src})
add_library(libjson ${libjson_src})