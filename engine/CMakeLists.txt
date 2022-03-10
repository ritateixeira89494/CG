cmake_minimum_required(VERSION 3.17)

project(engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

set(CMAKE_BINARY_DIR target)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

# Find all source files
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
# find_package(tinyxml2 REQUIRED)

include_directories(${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
link_libraries(${OpenGL_LIBRARY_DIRS} ${GLUT_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS} ${GLUT_DEFINITIONS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
