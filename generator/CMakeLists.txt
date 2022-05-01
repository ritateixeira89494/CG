cmake_minimum_required(VERSION 3.16)

project(generator VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# Set output folders
set(CMAKE_BINARY_DIR target)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

# Create output folders
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Find all source files and add them to the executable
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE MAIN src/main.cpp)
list(REMOVE_ITEM SOURCES ${MAIN})
message(${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)

# Tests
add_executable(${PROJECT_NAME}_test_bezier ${SOURCES} test/src/main.cpp)
add_executable(${PROJECT_NAME}_test_matrix ${SOURCES} test/src/matrix.cpp)

#Link all libs
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME}_test_bezier PUBLIC include)
target_include_directories(${PROJECT_NAME}_test_matrix PUBLIC include)
