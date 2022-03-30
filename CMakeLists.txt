cmake_minimum_required(VERSION 3.15.0)
project(phantom-engine)
set(CMAKE_CXX_STANDARD 17)

set(OPTION_BUILD_EXAMPLES OFF)

add_subdirectory(phantom)
add_subdirectory("libraries")
add_subdirectory("editor")