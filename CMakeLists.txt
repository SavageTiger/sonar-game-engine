cmake_minimum_required(VERSION 3.16)
project(sonar)

set(CMAKE_CXX_STANDARD 11)

add_executable(sonar main.cpp Window.cpp Window.h Player.cpp Player.h Map.cpp Map.h Raycaster.cpp Raycaster.h Wall.cpp Wall.h Textures.cpp Textures.h Floor.cpp Floor.h Ceiling.h Ceiling.cpp Resolution.h Entity.cpp Entity.h Entities.cpp Entities.h MapTile.cpp MapTile.h)

if (NOT APPLE)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-mod/")
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(sonar ${SDL2_LIBRARIES})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(sonar ${SDL2_IMAGE_LIBRARIES})

if (APPLE)
    find_library(OPENGL_FRAMEWORK GLUT)
    find_library(OPENGL_FRAMEWORK OpenGL)

    target_link_libraries(sonar "-framework OpenGL -framework GLUT")
endif()

if (APPLE)
    set(OpenGlLinkers -lglut -lGL -lSDL2 -lSDL2_IMAGE)
else()
    set(OpenGlLinkers -lglut -lGL -lSDL2 -lGLU)
endif()


target_link_libraries(sonar ${OpenGlLinkers})
