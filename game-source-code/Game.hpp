/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
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
#include <map>
#include <sstream> // Todo : Remove me!
#include <iostream> // Todo : Remove me!
#include <SFML/Graphics.hpp>
#include "common.hpp"
#include "ResourceHolder.hpp"
#include "PlayerShip.hpp"
#include "Bullet.hpp"
#include "InputHandler.hpp"
#include "SplashScreen.hpp"
#include "Starfield.hpp"
#include "Enemy.hpp"
#include "FPS.hpp"

class Game
{
public:
    static void Start();

private:
    static void InitializeGameLoop();
    static void showSplashScreen();

    enum GameState { Splash, Playing, Exiting };

    static ResourceHolder _resourceHolder;
    static InputHandler _inputHandler;
    static GameState _gameState;
    static sf::RenderWindow _mainWindow;
    static std::map<int, bool> _keysPressed;
    static common::Resolution _resolution;
};

#endif //PROJECT_GAME_HPP
