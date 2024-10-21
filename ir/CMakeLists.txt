cmake_minimum_required(VERSION 3.20.0)
project(SimpleProject)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable(IRGen 
    app_ir_gen.cpp
    ../sim.c
)
set_source_files_properties(../sim.c PROPERTIES LANGUAGE CXX)

llvm_map_components_to_libnames(
    llvm_libs support core irreader executionengine aarch64codegen mcjit
)

target_link_libraries(IRGen ${llvm_libs})
target_link_libraries(IRGen ${SDL2_LIBRARIES})
