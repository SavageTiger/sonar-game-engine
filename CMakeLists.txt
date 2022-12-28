cmake_minimum_required(VERSION 3.17)
project(threedee)

set(CMAKE_CXX_STANDARD 11)

add_executable(threedee main.cpp window.cpp window.h player.cpp player.h map.cpp map.h raycaster.cpp raycaster.h wall.cpp wall.h textures.cpp textures.h floor.cpp floor.h ceiling.h cieling.cpp resolution.h entity.cpp entity.h entities.cpp entities.h)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(threedee ${SDL2_LIBRARIES})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(threedee ${SDL2_IMAGE_LIBRARIES})

set(OpenGlLinkers -lglut -lGL -lSDL2 -lSDL2_IMAGE)

target_link_libraries(threedee ${OpenGlLinkers})
