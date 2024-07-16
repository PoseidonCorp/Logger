cmake_minimum_required(VERSION 3.20)

# Set the C++ compiler
project(Logger CXX)
project(Logger VERSION 0.0.1)
project(Logger DESCRIPTION "A lightweight C++20 asyncronous logger.")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(PUBLIC_HEADER_DIR "${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.hpp"
)

set(PUBLIC_HEADER_FILES
    "${PUBLIC_HEADER_DIR}/OwnLogger.hpp"
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${PUBLIC_HEADER_FILES})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

target_include_directories(${PROJECT_NAME} PUBLIC "${SRC_DIR}")
target_precompile_headers(${PROJECT_NAME} PRIVATE "${SRC_DIR}/common.hpp")

# public stuff
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADER_FILES}")
target_include_directories(${PROJECT_NAME} PUBLIC "${PUBLIC_HEADER_DIR}")