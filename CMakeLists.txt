cmake_minimum_required(VERSION 3.5)
project(cg_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_libraries(${GLUT_LIBRARIES})


set(SOURCE_FILES main.cpp OpenGL.hpp colors.hpp RgbImage.hpp RgbImage.cpp materials.cpp materials.hpp textures.cpp textures.hpp billiardTable.cpp billiardTable.hpp primitives.cpp primitives.hpp structs.cpp structs.hpp roomWindow.cpp roomWindow.hpp spotLight.cpp spotLight.hpp)
add_executable(cg_project ${SOURCE_FILES})