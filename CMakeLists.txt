cmake_minimum_required(VERSION 3.17)

project(rtype_server)
project(rtype_client)

find_package(raylib)

find_package(asio QUIET)

find_package(nlohmann_json QUIET)

if(NOT raylib_FOUND)
    message(STATUS "raylib not found, downloading and building it now")
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        master
    )
    FetchContent_GetProperties(raylib)
    if(NOT raylib_POPULATED)
        FetchContent_Populate(raylib)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

if(NOT nlohmann_json_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.10.4
    )

    FetchContent_GetProperties(nlohmann_json)

    if(NOT nlohmann_json_POPULATED)
        FetchContent_Populate(nlohmann_json)
        add_subdirectory(${nlohmann_json_SOURCE_DIR} ${nlohmann_json_BINARY_DIR})
    endif()

    set(nlohmann_json_INCLUDE_DIRS ${nlohmann_json_SOURCE_DIR}/include)
endif()

if(NOT asio_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-18-2
    )
    FetchContent_GetProperties(asio)

    set(asio_INCLUDE_DIRS ${asio_SOURCE_DIR}/asio/include)
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

if(UNIX)
    set(CMAKE_CXX_FLAGS "-std=c++17 -W -Wall -Wextra -lpthread -g")
endif(UNIX)

if(win32)
    include(FetchContent)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
    FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
    FetchContent_MakeAvailable(raylib)
endif(win32)

include_directories(include)
include_directories(src)
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)
include_directories(${CONAN_INCLUDE_DIRS})

FILE(GLOB SRC_FILES_CLIENT

    # File with the game
    Game/src/Game.cpp

    #Init all the function related in extern librairy
    Game/src/Init/Sound.cpp
    Game/src/Init/Music.cpp
    Game/src/Init/Button.cpp
    Game/src/Init/Window.cpp
    Game/src/Init/JsonRead.cpp
    Game/src/Init/InitTexture.cpp
    Game/src/Init/TextField.cpp
    Game/src/Init/Parralax.cpp

    #Game engine
    Game/src/Gameplay/Component.cpp
    Game/src/Gameplay/Entity.cpp
    Game/src/Gameplay/GameOver.cpp
    Game/src/Gameplay/Player.cpp
    Game/src/Gameplay/System.cpp
    Game/src/Gameplay/Configuration.cpp
    Game/src/Gameplay/MovementSystem.cpp


    #Main of the project
    Game/src/main.cpp

    #Menu
    Game/src/Menu.cpp

    #Client for connect with the game
    Game/src/Client.cpp
)

FILE(GLOB SRC_FILES_SERVER
        Server/Server.cpp
        Server/main.cpp)

add_executable(rtype_client ${SRC_FILES_CLIENT})
add_executable(rtype_server ${SRC_FILES_SERVER})

target_link_libraries(${PROJECT_NAME} CONAN_PKG::asio)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::nlohmann_json)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::raylib)

# target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
