cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)
project(OrigamiSpaceTime)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

set(SOURCE_FILES
        main.cpp
        Game.cpp
        Game.hpp
        Bunny.cpp
        Bunny.hpp
        BunnyInputComponent.cpp
        BunnyInputComponent.hpp
        BunnyGraphicsComponent.cpp
        BunnyGraphicsComponent.hpp
        BunnyPhysicsComponent.cpp
        BunnyPhysicsComponent.hpp
        OrigamiWorld.cpp
        OrigamiWorld.hpp)

add_executable(OrigamiSpaceTime ${SOURCE_FILES})
add_subdirectory(SFML-Engine)

target_link_libraries(OrigamiSpaceTime LINK_PUBLIC SFML-Engine -lsfml-graphics -lsfml-window -lsfml-system)