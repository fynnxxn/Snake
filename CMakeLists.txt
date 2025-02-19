cmake_minimum_required(VERSION 3.30)
project(Snake_Game)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FETCHCONTENT_MAKEAVAILABLE(SFML)

add_executable(Snake main.cpp
        Game.cpp
        Snake.cpp
        Snake.h
        Game.h
        Food.cpp
        Food.h
)

#SFML mit dem Projekt linken
target_link_libraries(Snake PRIVATE sfml-graphics)
target_compile_features(Snake PRIVATE cxx_std_23)