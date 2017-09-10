//--------------------------------------------------------------------------
// Student  1239448
// @file    Game.hpp
// @author  Tyson Cross
// @date    2017/09/09
// @brief   Main Game controller.
//
// Handles the Game loop, and game states
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------

#ifndef PROJECT_GAME_HPP
#define PROJECT_GAME_HPP
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <map>

const int gameWidth = 1920;
const int gameHeight = 1080;
const float pi = 3.1415;

using key_map = std::map<int, bool>; // perhaps should be unordered_set?? The boolean value is redundant

class Game
{
public:
    static void Start();

private:
    static void InitializeGameLoop();
    static void ShowSplashScreen();

    enum GameState { Splash, Playing, Exiting };

    static GameState _gameState;
    static sf::RenderWindow _mainWindow;
    static key_map _keysPressed;
};

#endif //PROJECT_GAME_HPP
