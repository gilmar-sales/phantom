include(CTest)
enable_testing()

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE PHANTOM_SRC
    "src/*.cpp"
    "src/*.h"
)

add_library(phantom 
    ${PHANTOM_SRC}
)

target_link_libraries(phantom
	glbinding::glbinding 
    glbinding::glbinding-aux
	glfw
    glm
    imgui
	fmt
    ct-ecs
)

target_include_directories(phantom INTERFACE
	PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_precompile_headers(phantom 
PUBLIC
    src/core/common.h
    src/core/log.h
	src/ph_pch.h
PRIVATE
    <glbinding/gl46/gl.h>
    <glbinding/gl46core/gl.h>
    <glbinding/gl46ext/gl.h>
    <glbinding/glbinding.h>
    <glm/glm.hpp>
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
