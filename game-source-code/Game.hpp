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
#include "HUD.hpp"
#include "Shield.hpp"

class Game
{
public:
    Game();
    void Start();
    void Quit();

private:
    void initializeGameLoop();
    void showSplashScreen();
    void showGameOverScreen(bool gameOutcome);
    void loadResources();
    void recordHighScore();

    TextureHolder _textures;
    SoundController _soundController;
    FontHolder _fonts;
    InputHandler _inputHandler;
    game::GameState _gameState;
    sf::RenderWindow _mainWindow;
    sf::Vector2i _resolution;
    int _winCondition;
    Score _score;

};

#endif //PROJECT_GAME_HPP
