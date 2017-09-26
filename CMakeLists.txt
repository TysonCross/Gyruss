cmake_minimum_required(VERSION 3.8)
project(Project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(SOURCE_FILES_BASE
        game-source-code/Game.hpp
        game-source-code/Game.cpp
        game-source-code/InputHandler.cpp
        game-source-code/InputHandler.hpp
        game-source-code/ResourceHolder.inl
        game-source-code/ResourceHolder.hpp
        game-source-code/Starfield.cpp
        game-source-code/Starfield.hpp
        game-source-code/Entity.hpp
        game-source-code/PlayerShip.cpp
        game-source-code/PlayerShip.hpp
        game-source-code/Enemy.cpp
        game-source-code/Enemy.hpp
        game-source-code/Bullet.cpp
        game-source-code/Bullet.hpp
        game-source-code/Explosion.cpp
        game-source-code/Explosion.hpp
        game-source-code/common.cpp
        game-source-code/common.hpp
        game-source-code/FPS.cpp
        game-source-code/FPS.hpp
        game-source-code/Screen.cpp
        game-source-code/Screen.hpp
        game-source-code/ScreenSplash.hpp
        game-source-code/ScreenSplash.cpp
        game-source-code/ScreenGameOver.cpp
        game-source-code/ScreenGameOver.hpp
        game-source-code/EntityController.cpp
        game-source-code/EntityController.hpp
        game-source-code/SoundController.cpp
        game-source-code/SoundController.hpp
        game-source-code/HUD.cpp
        game-source-code/HUD.hpp
        game-source-code/Score.cpp
        game-source-code/Score.hpp
        game-source-code/Meteoroid.cpp
        game-source-code/Meteoroid.hpp)

set(SOURCE_FILES_TEST
        ${SOURCE_FILES_BASE}
        test-source-code/doctest.h)

set(SOURCE_FILES
        ${SOURCE_FILES_BASE}
        game-source-code/Main.cpp)

set(EXECUTABLE_TEST_INTERACTIVE "tests_interactive")
add_executable(${EXECUTABLE_TEST_INTERACTIVE}
        ${SOURCE_FILES_TEST}
        test-source-code/test_Interactive.cpp)

set(EXECUTABLE_TEST_UNIT "tests_unit")
add_executable(${EXECUTABLE_TEST_UNIT}
        ${SOURCE_FILES_TEST}
        test-source-code/test_Unit.cpp)

set(EXECUTABLE_TEST_UNIT_RELEASE "game_tests")
add_executable(${EXECUTABLE_TEST_UNIT_RELEASE}
        ${SOURCE_FILES_TEST}
        test-source-code/test_Unit.cpp)
set(CMAKE_BINARY_DIR_TEST "${PROJECT_SOURCE_DIR}/executables")
set_target_properties(${EXECUTABLE_TEST_UNIT_RELEASE}
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR_TEST}")

set(EXECUTABLE_TEST_INTERACTIVE_RELEASE "game_tests_gui")
add_executable(${EXECUTABLE_TEST_INTERACTIVE_RELEASE}
        ${SOURCE_FILES_TEST}
        test-source-code/test_Interactive.cpp)
set(CMAKE_BINARY_DIR_TEST "${PROJECT_SOURCE_DIR}/executables")
set_target_properties(${EXECUTABLE_TEST_INTERACTIVE_RELEASE}
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR_TEST}")

set(EXECUTABLE_DEBUG "debug")
add_executable(${EXECUTABLE_DEBUG} ${SOURCE_FILES})

set(EXECUTABLE_RELEASE "game")
add_executable(${EXECUTABLE_RELEASE} ${SOURCE_FILES})
set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/executables")
set_target_properties(${EXECUTABLE_RELEASE}
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Detect and add SFML
if (WIN32)
    set(SFML_ROOT "C:/SFML-2.4.2")
endif (WIN32)
if (APPLE)
    set(SFML_ROOT "/usr/local/Cellar/sfml/2.4.2_1/share/SFML")
    target_compile_definitions(${EXECUTABLE_DEBUG} PUBLIC DEBUG_ONLY)
endif (APPLE)

set(CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules/" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window graphics audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_RELEASE} ${SFML_LIBRARIES})
    target_link_libraries(${EXECUTABLE_DEBUG} ${SFML_LIBRARIES})
    target_link_libraries(${EXECUTABLE_TEST_UNIT_RELEASE} ${SFML_LIBRARIES})
    target_link_libraries(${EXECUTABLE_TEST_INTERACTIVE_RELEASE} ${SFML_LIBRARIES})
    target_link_libraries(${EXECUTABLE_TEST_UNIT} ${SFML_LIBRARIES})
    target_link_libraries(${EXECUTABLE_TEST_INTERACTIVE} ${SFML_LIBRARIES})
endif ()