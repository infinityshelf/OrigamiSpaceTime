cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)
project(OrigamiSpaceTime)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

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