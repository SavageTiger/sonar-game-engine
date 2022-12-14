cmake_minimum_required(VERSION 3.17)
project(threedee)

set(CMAKE_CXX_STANDARD 11)

add_executable(threedee main.cpp window.cpp window.h player.cpp player.h map.cpp map.h raycaster.cpp raycaster.h wall.cpp wall.h textures.cpp textures.h floor.cpp floor.h ceiling.h cieling.cpp resolution.h sprite.cpp entity.h)

set(OpenGlLinkers -lglut -lGLU -lGL -lSOIL)
target_link_libraries(threedee ${OpenGlLinkers})
