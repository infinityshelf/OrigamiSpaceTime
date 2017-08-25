cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)
project(OrigamiSpaceTime)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Winit-self -Wextra -pedantic -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -flto -Wodr -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral")

set(SOURCE_FILES
        main.cpp
        Bunny.cpp
        Bunny.hpp
        BunnyInputComponent.cpp
        BunnyInputComponent.hpp
        BunnyGraphicsComponent.cpp
        BunnyGraphicsComponent.hpp
        BunnyPhysicsComponent.cpp
        BunnyPhysicsComponent.hpp
        World.cpp
        World.hpp
        BunnyComponent.cpp
        BunnyComponent.hpp
        BunnyManager.cpp
        BunnyManager.hpp)

add_executable(OrigamiSpaceTime ${SOURCE_FILES})
add_subdirectory(SFML-Engine)

target_link_libraries(OrigamiSpaceTime LINK_PUBLIC SFML-Engine -lsfml-graphics -lsfml-window -lsfml-system)