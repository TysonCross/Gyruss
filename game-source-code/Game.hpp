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
#include "PlayerShip.hpp"
#include "Bullet.hpp"
#include "ResourceHolder.hpp"
#include "InputHandler.hpp"
#include "SplashScreen.hpp"
#include "Starfield.hpp"
#include "Enemy.hpp"
#include "FPS.hpp"

class Game
{
public:
    void Start();
    void Quit();

private:
    void initializeGameLoop();
    void showSplashScreen();
    void loadResources();
    //temp method and arguements
    // ToDo: InputHandler should generate gameEvents
    void pollInput(PlayerShip& playerShip,
                   std::vector<Bullet>& bulletVector,
                   sf::Event &event,
                   bool &prevButtonState);

    enum GameState { Splash, Playing, Exiting };

    TextureHolder _textures;
    SoundHolder _sounds;
    FontHolder _fonts;
    InputHandler _inputHandler;
    GameState _gameState;
    sf::RenderWindow _mainWindow;
    std::map<int, bool> _keysPressed;
    common::Resolution _resolution;
};

#endif //PROJECT_GAME_HPP
