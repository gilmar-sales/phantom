cmake_minimum_required(VERSION 3.0.0)
project(editor VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE EDITOR_SRC
    "src/*.cpp"
    "src/*.h"
)

add_executable(editor 
    ${EDITOR_SRC}
)

target_link_libraries(editor
    phantom
)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR}/editor)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
