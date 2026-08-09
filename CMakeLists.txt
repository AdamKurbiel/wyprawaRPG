cmake_minimum_required(VERSION 3.28)
project(wyprawaRPG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(wyprawaRPG
    src/main.cpp
    src/game.cpp
    src/Systems/ResourceManager.cpp
    src/Systems/GameMap.cpp
    src/UI/UiKeyboard.cpp
    src/Systems/rng.cpp
    src/Prefabs/characterCreation.cpp
    src/Prefabs/classSelect.cpp
)


target_compile_features(wyprawaRPG PRIVATE cxx_std_17)
target_link_libraries(wyprawaRPG PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT wyprawaRPG)