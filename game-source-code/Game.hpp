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
#include <SFML/Graphics.hpp>
#include <map>
#include "common.hpp"
#include "ResourceMapper.hpp"
#include "PlayerShip.hpp"
#include "InputHandler.hpp"
#include "SplashScreen.hpp"
#include "Starfield.hpp"

class Game
{
public:
    static void Start();

private:
    static void InitializeGameLoop();
    static void showSplashScreen();

    enum GameState { Splash, Playing, Exiting };

    static ResourceMapper _resourceMapper;
    static InputHandler _inputHandler;
    static GameState _gameState;
    static sf::RenderWindow _mainWindow;
    static std::map<int, bool> _keysPressed;
    static common::Resolution _resolution;
};

#endif //PROJECT_GAME_HPP
