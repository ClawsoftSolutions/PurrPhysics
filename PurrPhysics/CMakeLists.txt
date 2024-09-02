cmake_minimum_required(VERSION 3.10)

project(PurrPhysics)

include_directories(include)
include_directories(deps/glm)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_library(PurrPhysics STATIC ${SOURCES} ${HEADERS})

target_link_libraries(PurrPhysics glm)
