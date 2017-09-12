cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

set(SOURCE_FILES
        game-source-code/common.hpp
        game-source-code/Gyruss.cpp
        game-source-code/Game.hpp
        game-source-code/Game.cpp
        game-source-code/InputHandler.cpp
        game-source-code/InputHandler.hpp
        game-source-code/ResourceMapper.cpp
        game-source-code/ResourceMapper.hpp
        game-source-code/SplashScreen.hpp
        game-source-code/SplashScreen.cpp
        game-source-code/PlayerShip.cpp
        game-source-code/PlayerShip.hpp
        game-source-code/Starfield.cpp
        game-source-code/Starfield.hpp
        #[[game-source-code/Resolution.cpp
        game-source-code/Resolution.hpp]]
        #[[game-source-code/Entity.hpp
        game-source-code/Entity.cpp]])
set(EXECUTABLE_NAME "game_debug")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

set(SOURCE_FILES_RELEASE ${SOURCE_FILES})
set(EXECUTABLE_NAME_RELEASE "game")
set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/executables")
add_executable(${EXECUTABLE_NAME_RELEASE} ${SOURCE_FILES_RELEASE})
set_target_properties(${EXECUTABLE_NAME_RELEASE}
                        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(SOURCE_FILES_TEST
        test-source-code/doctest.h
        game-source-code/SplashScreen.hpp
        game-source-code/SplashScreen.cpp
        game-source-code/Game.hpp
        game-source-code/Game.cpp
        game-source-code/InputHandler.cpp
        game-source-code/InputHandler.hpp
        game-source-code/PlayerShip.cpp
        game-source-code/PlayerShip.hpp
        test-source-code/test_Game.cpp)
set(EXECUTABLE_NAME_TEST "tests")
add_executable(${EXECUTABLE_NAME_TEST} ${SOURCE_FILES_TEST})

# Detect and add SFML
if (WIN32)
    set(SFML_ROOT "C:/SFML-2.4.2")
endif (WIN32)
if (APPLE)
    set(SFML_ROOT "/usr/local/Cellar/sfml/2.4.2_1/share/SFML")
endif (APPLE)
set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules/" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window graphics audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
    target_link_libraries(${EXECUTABLE_NAME_RELEASE} ${SFML_LIBRARIES})
    target_link_libraries(${EXECUTABLE_NAME_TEST} ${SFML_LIBRARIES})
endif ()

# Game assets - Copy from /game_resources to the relevant 'resources' folder
set(RESOURCES_TO_COPY "game_resources")
set(RESOURCE_TARGET_FOLDER "resources")
set(RESOURCE_TARGET_FILE_LIST "*")
set(${DEPLOY_DIRECTORY} "executables")
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove
        $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/${RESOURCE_TARGET_FOLDER}/${RESOURCE_TARGET_FILE_LIST}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/${RESOURCES_TO_COPY} $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/${RESOURCE_TARGET_FOLDER})
add_custom_command(TARGET ${EXECUTABLE_NAME_RELEASE} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove
        $<TARGET_FILE_DIR:${EXECUTABLE_NAME_RELEASE}>/${RESOURCE_TARGET_FOLDER}/${RESOURCE_TARGET_FILE_LIST}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/${RESOURCES_TO_COPY} $<TARGET_FILE_DIR:${EXECUTABLE_NAME_RELEASE}>/${RESOURCE_TARGET_FOLDER})
