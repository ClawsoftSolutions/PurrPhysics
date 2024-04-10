project(AtomixPhysics)

file (GLOB_RECURSE PHYSICS_SOURCES "src/**.cpp")
add_library(AtomixPhysics STATIC ${PHYSICS_SOURCES})

target_include_directories(AtomixPhysics PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(AtomixPhysics PUBLIC
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)