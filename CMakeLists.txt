cmake_minimum_required(VERSION 3.24)
project(gaze-maze)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

link_directories(${CMAKE_CORE_DIR}/lib)
link_directories(${CMAKE_CORE_DIR}/bin/irrKlang/linux-gcc-64)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(OpenGL REQUIRED)

# find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

set(LIBS glfw GL X11 pthread Xrandr Xi dl assimp)

add_library(GLAD "src/glad.c")
set(IRRKLANG_LIBRARY ikpMP3.so)
add_library(Irrklang STATIC IMPORTED)
set_property(TARGET Irrklang PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/irrKlang/linux-gcc-64/libIrrKlang.so)
set(IRRKLANG_LIBRARY libIrrKlang.so)
# add_library(IkpMP3 STATIC IMPORTED)
# set_property(TARGET IkpMP3 PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/linux-gcc-64/ikpFlac.so)
# set(IRRKLANG_LIBRARY ikpFlac.so)
# add_library(IkpFlac STATIC IMPORTED)
# set_property(TARGET IkpFlac PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/linux-gcc-64/ikpMP3.so)

set(LIBS ${LIBS} GLAD Irrklang) #IkpMP3 IkpFlac)


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
    src/entities/ParticleGenerator.h
    src/entities/ParticleGenerator.cpp
    src/entities/Particle.h
    src/entities/Particle.cpp
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
    src/objects/model/Bone.h
    src/objects/model/BoneInfo.h
    src/objects/model/Animation.h
    src/objects/model/Animator.h
    src/objects/model/AssimpGLMHelpers.h
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
    src/entities/Entity.h
    src/entities/Entity.cpp
    src/entities/Enemy.h
    src/entities/Enemy.cpp
    src/utils/ColorPicker.h
    src/utils/ColorPicker.cpp
)

target_include_directories(gaze-maze PUBLIC ${CMAKE_SOURCE_DIR}/bin/irrKlang/linux-gcc-64)

target_link_libraries(gaze-maze 
    ${LIBS}
) # -lglfw3 -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lpthread -lXi
