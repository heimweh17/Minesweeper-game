cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(HelloSFML)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR C:/Users/haozh/Downloads/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML)

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(HelloSFML main.cpp
        WelcomeWindow.h
        WelcomeWindow.cpp
        GameWindow.h
        GameWindow.cpp
        Tile.h
        Tile.cpp
        TextureManager.h
        TextureManager.cpp
        Board.h
        Board.cpp
)
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio)