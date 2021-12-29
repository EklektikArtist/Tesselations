if( UNIX)
cmake_minimum_required(VERSION 3.10)

project(Tesselations)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmakelinux)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(MPI REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${MPI_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/neat/include/NEAT)

#set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
#set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})

add_executable(Tesselations code/main.cpp)
target_link_libraries(Tesselations ${SDL2_LIBRARIES} SDL2::Image ${MPI_LIBRARIES})
endif(UNIX)


if(WIN32)
cmake_minimum_required(VERSION 3.10)

project(Tesselations)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmakewindows")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(MPI REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
#include_directories(SYSTEM ${MPI_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/neat/include/NEAT)

file(GLOB SOURCES "code/*.cpp")

add_executable(Tesselations ${SOURCES})
target_link_libraries(Tesselations ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} MPI::MPI_CXX)
endif(WIN32)
