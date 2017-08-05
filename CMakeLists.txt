cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)
project(OrigamiSpaceTime)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

set(SOURCE_FILES
        SFML-Engine/Entity.hpp
        main.cpp
        SFML-Engine/World.cpp
        SFML-Engine/World.hpp
        SFML-Engine/Input.cpp
        SFML-Engine/Input.hpp
        SFML-Engine/InputStruct.hpp
        SFML-Engine/GraphicsComponent.hpp
        SFML-Engine/InputComponent.hpp
        SFML-Engine/TextureManager.cpp
        SFML-Engine/TextureManager.hpp
        SFML-Engine/PhysicsComponent.hpp
        SFML-Engine/Component.hpp
        SFML-Engine/Component.cpp
        SFML-Engine/GraphicsComponent.cpp
        SFML-Engine/ComponentMessaging.hpp
        Game.cpp
        Game.hpp
        Bunny.cpp
        Bunny.hpp
        BunnyInputComponent.cpp
        BunnyInputComponent.hpp
        BunnyGraphicsComponent.cpp
        BunnyGraphicsComponent.hpp
        BunnyPhysicsComponent.cpp
        BunnyPhysicsComponent.hpp)

add_executable(OrigamiSpaceTime ${SOURCE_FILES})

#include_directories ("${PROJECT_SOURCE_DIR}/SFML-Engine")
#include_directories ("${PROJECT_INCLUDE_DIR}/SFML-Engine")
#add_subdirectory (SFML-Engine)

target_link_libraries(OrigamiSpaceTime -lsfml-graphics -lsfml-window -lsfml-system)