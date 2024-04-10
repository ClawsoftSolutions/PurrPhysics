project(Test)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE TEST_SOURCES "src/*.cpp" "src/**/*.cpp")
add_executable(Test ${TEST_SOURCES})

target_include_directories(Test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(Test PUBLIC ${DEPS_INCLUDE_DIRS})

target_link_libraries(Test PRIVATE
    AtomixPhysics
)


target_compile_definitions(Test PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

target_compile_options(Test PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
)
