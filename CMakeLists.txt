cmake_minimum_required(VERSION 3.8)
#set(CMAKE_CXX_STANDARD 11)
project(OrigamiSpaceTime)

add_definitions(-std=c++14 -Wall -Winit-self -Wextra -pedantic -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -Wodr -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral)

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
        BunnyManager.hpp
        Level.hpp
        Level.cpp
        Door.hpp
        Door.cpp
        DoorPhysicsComponent.hpp
        DoorPhysicsComponent.cpp
        DoorGraphicsComponent.hpp
        DoorGraphicsComponent.cpp)

add_executable(OrigamiSpaceTime ${SOURCE_FILES})
add_subdirectory(SFML-Engine)

target_link_libraries(OrigamiSpaceTime LINK_PUBLIC SFML-Engine -lsfml-graphics -lsfml-window -lsfml-system)