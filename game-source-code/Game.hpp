/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    Game.hpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/09
/// \brief   Main Game controller
///
/// Handles the Game loop, and game states
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_GAME_HPP
#define PROJECT_GAME_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "common.hpp"
#include <map>

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
