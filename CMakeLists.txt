cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 14)
project(OrigamiSpaceTime)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Program Files\ (x86)/SFML/lib/cmake/SFML")

include_directories("C:\\Program Files\ (x86)\\SFML\\include")
find_package(SFML 2.5 REQUIRED graphics window network audio system )

#add_definitions(-std=c++14 -Wall)# -Winit-self -Wextra -pedantic -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -Wodr -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral)

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

target_link_libraries(OrigamiSpaceTime SFML-Engine sfml-window sfml-graphics sfml-system)