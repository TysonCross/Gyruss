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
#ifdef DEBUG
#include <sstream>
#include <iostream>
#endif // DEBUG
#include <SFML/Graphics.hpp>
#include "common.hpp"
#include "Entity.hpp"
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
    bool collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2);

    TextureHolder _textures;
    SoundHolder _sounds;
    FontHolder _fonts;
    InputHandler _inputHandler;
    game::GameState _gameState;
    sf::RenderWindow _mainWindow;
    sf::Vector2i _resolution;
};

#endif //PROJECT_GAME_HPP
