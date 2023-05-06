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

set(LIBS glfw GL X11 pthread Xrandr Xi dl assimp)

add_library(GLAD "src/glad.c")
set(LIBS ${LIBS} GLAD)

include_directories(${CMAKE_SOURCE_DIR}/includes)
add_executable(gaze-maze 
    src/main.cpp 
    src/stb_image.cpp 
    src/stb_image.h 
    src/Game.h 
    src/Game.cpp 
    src/core/Camera.h
    src/core/Camera.cpp
    src/core/Player.h
    src/core/Player.cpp
    src/core/Maze.cpp
    src/core/Maze.h
    src/core/Skybox.h
    src/core/Skybox.cpp
    src/objects/Mesh.h
    src/objects/Mesh.cpp
    src/objects/Crosshair.h
    src/objects/Crosshair.cpp
    src/objects/based/Cube.h
    src/objects/based/Cube.cpp
    src/objects/based/Plane.h
    src/objects/based/Plane.cpp
    src/objects/Collisioner.h
    src/objects/Collisioner.cpp
    src/objects/model/Model.h
    src/objects/model/Model.cpp
    src/objects/model/ModelMesh.h
    src/objects/model/ModelMesh.cpp
    src/resources/ResourceManager.h 
    src/resources/ResourceManager.cpp
    src/resources/shaders/Shader.h 
    src/resources/shaders/Shader.cpp
    src/resources/textures/Texture.h 
    src/resources/textures/Texture.cpp
    src/utils/MazeLoader.h
    src/utils/MazeLoader.cpp
    src/utils/MazeGenerator.h
    src/utils/MazeGenerator.cpp
    src/utils/ColorPicker.h
    src/utils/ColorPicker.cpp
)
target_link_libraries(gaze-maze ${LIBS}) # -lglfw3 -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lpthread -lXi
