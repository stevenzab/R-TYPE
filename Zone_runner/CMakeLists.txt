cmake_minimum_required(VERSION 3.17)

project(Zone_Runner)
# project(rtype_server)
# project(client)

find_package(raylib)
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

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

if(UNIX)
    set(CMAKE_CXX_FLAGS "-std=c++17 -W -Wall -Wextra -lpthread")
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

FILE(GLOB SRC_FILES
    src/Game.cpp
    src/main.cpp
    src/Menu.cpp
    src/Gameplay/Component.cpp
    src/Gameplay/Entity.cpp
    src/Gameplay/Configuration.cpp
    src/Gameplay/Ennemy.cpp
    src/Gameplay/Entity.cpp
    src/Gameplay/GameOver.cpp
    src/Gameplay/Player.cpp
    src/Gameplay/System.cpp
    src/Gameplay/plateform.cpp
    src/Init/JsonRead.cpp
    src/Init/Parralax.cpp
    src/Init/InitTexture.cpp
    src/Init/Button.cpp
    src/Init/Music.cpp
    src/Init/Window.cpp
    src/Init/Sound.cpp
)

add_executable(Zone_Runner ${SRC_FILES})


target_link_libraries(${PROJECT_NAME} CONAN_PKG::nlohmann_json)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::raylib)