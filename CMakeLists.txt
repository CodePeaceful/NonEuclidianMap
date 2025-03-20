cmake_minimum_required(VERSION 3.28)
project(NonEuclidianMap LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3)
FetchContent_MakeAvailable(json)

add_executable(MagicMap 
    src/main.cpp
    src/GameWindow.cpp
    src/Player.cpp
    src/Map.cpp)
target_compile_features(MagicMap PRIVATE cxx_std_23)

target_link_libraries(MagicMap PRIVATE 
    SFML::Graphics 
    nlohmann_json::nlohmann_json)