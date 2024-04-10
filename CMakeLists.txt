cmake_minimum_required(VERSION 3.10)
project(Physics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(DEPS_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/deps
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm
)

include_directories(${DEPS_INCLUDE_DIRS})

add_subdirectory(AtomixPhysics)
add_subdirectory(Test)
