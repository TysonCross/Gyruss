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
#include "EntityController.hpp"
#include "ResourceHolder.hpp"
#include "SoundController.hpp"
#include "InputHandler.hpp"
#include "ScreenSplash.hpp"
#include "ScreenGameOver.hpp"
#include "Starfield.hpp"
#include "FPS.hpp"

class Game
{
public:
    void Start();
    void Quit();

private:
    void initializeGameLoop();
    void showSplashScreen();
    void showGameOverScreen();
    void loadResources();
    void pulseColor(sf::Sprite sprite,
                    sf::Color color,
                    int frequency,
                    sf::Clock& clock);

//    bool collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2);

    TextureHolder _textures;
    SoundController _soundController;
    FontHolder _fonts;
    sf::Music _music;
    InputHandler _inputHandler;
    game::GameState _gameState;
    sf::RenderWindow _mainWindow;
    sf::Vector2i _resolution;
    Score _score;
};

#endif //PROJECT_GAME_HPP
