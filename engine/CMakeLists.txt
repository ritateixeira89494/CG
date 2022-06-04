cmake_minimum_required(VERSION 3.16)

project(Engine VERSION 1.0)

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
add_executable(${PROJECT_NAME} ${SOURCES})

# Find all libs
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(DevIL REQUIRED)

if (NOT GLEW_FOUND)
    message(ERROR " GLEW not found")
endif (NOT GLEW_FOUND)

if (NOT OpenGL_FOUND)
    message(ERROR " OpenGL not found")
endif (NOT OpenGL_FOUND)

if (NOT GLUT_FOUND)
    message(ERROR " Glut not found")
endif (NOT GLUT_FOUND)

# Link libs to our program
target_include_directories(Engine PUBLIC include)
include_directories(${OpenGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${IL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
