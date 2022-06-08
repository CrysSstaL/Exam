cmake_minimum_required(VERSION 3.20)
project(LAB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
include_directories("/")
include_directories(ext/SFML/include)

add_definitions(-DSFML_STATIC)


add_executable(EXAM EXAM.cpp lab_8.h)


include_directories(${SFML_INCLUDE_DIRS})
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(EXAM sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
