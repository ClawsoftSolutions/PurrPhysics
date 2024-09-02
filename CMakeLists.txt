cmake_minimum_required(VERSION 3.10)
project(Physics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(deps/glm)

set(SDL_STATIC ON)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(deps/SDL2)

add_subdirectory(PurrPhysics)

add_subdirectory(test)
