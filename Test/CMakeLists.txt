cmake_minimum_required(VERSION 3.10)

project(test)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

include_directories(deps/SDL2/include)

add_executable(test ${TEST_SOURCES})

target_link_libraries(test PRIVATE PurrPhysics SDL2-static)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/PurrPhysics/include)

set_target_properties(test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
