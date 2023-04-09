cmake_minimum_required(VERSION 3.24)
project(gaze-maze)

set(CMAKE_CXX_STANDARD 17)

link_directories(${CMAKE_CORE_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(OpenGL REQUIRED)

# find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

set(LIBS glfw GL X11 pthread Xrandr Xi dl)

add_library(GLAD "glad.c")
set(LIBS ${LIBS} GLAD)

include_directories(${CMAKE_SOURCE_DIR}/includes)
add_executable(gaze-maze main.cpp stb_image.cpp stb_image.h)
target_link_libraries(gaze-maze ${LIBS}) # -lglfw3 -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lpthread -lXi