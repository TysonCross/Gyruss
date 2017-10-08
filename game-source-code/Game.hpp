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
    ////////////////////////////////////////////////////////////
    /// \brief Constructor for the Main game class. This class manages
    /// all game loops and creation of all game events and objects.
    ///
    /// This class controls the games ability to move from one state(splashScreen, playing etc)
    /// to another. It also generates instances of all other controllers, like EntityController that
    /// controls all other game objects. Called and generated from main.cpp
    ///
    /// \see Game.hpp
    ////////////////////////////////////////////////////////////
    Game();

    ////////////////////////////////////////////////////////////
    /// \brief called when the game starts up to begin initialising all prerequisites
    /// transisions the game into the "stateGameLoop" state that manages and runs the main game loop.
    ///
    /// Primary things set at this point are: game resolution and creation of game window
    ////////////////////////////////////////////////////////////
    void Start();

    ////////////////////////////////////////////////////////////
    /// \brief used when the game ends to close the game window. Called when the game falls out
    /// of the startGameLoop state.
    ///
    /// \see Start
    ////////////////////////////////////////////////////////////
    void Quit();

private:
    ////////////////////////////////////////////////////////////
    /// \brief This is the main game loop that is used throughout game play.
    ///
    /// Loop begins by setting up all things needed going forward, such as clocks and predefined variables.
    /// It also is used in the creation of key objects, namely: PlayerShip, shield, entityController and HUD.
    /// This function holds the game in the mainGame loop during game play and deals with player death sound and draw events
    ///
    /// \see PlayerShip.hpp
    /// \see Shield.hpp
    /// \see EntityController.hpp
    /// \see HUD.hpp
    ////////////////////////////////////////////////////////////
    void startGameLoop();

    ////////////////////////////////////////////////////////////
    /// \brief when called, displays the game splashScreen. used when the game starts up or when the game ends
    ////////////////////////////////////////////////////////////
    void showSplashScreen();

    ////////////////////////////////////////////////////////////
    /// \brief shows the end game screen, whn the game ends. Based on if the player won or lost,
    /// a different screen is displayed.
    ///
    /// \param gameOutcome boolean to represent if the player won the current game
    ////////////////////////////////////////////////////////////
    void showGameOverScreen(bool gameOutcome);

    ////////////////////////////////////////////////////////////
    /// \brief Loads all required game resources when called. This Utilises the ResourceHolder object. Each resource
    /// is intern loaded into the resourceHolder, where a map of all entities is created. When resources are required, the
    /// resourceHolder returns a smart pointer to the resource
    ////////////////////////////////////////////////////////////
    void loadResources();

    ////////////////////////////////////////////////////////////
    /// \brief Compares current game highscore to highscore stored on disk. If current is higher, saves to a text file
    /// "highscore.txt" in the game root directory.
    ////////////////////////////////////////////////////////////
    void recordHighScore();

    ////////////////////////////////////////////////////////////
    /// \brief Instant of Texture holder to store all game textures
    ////////////////////////////////////////////////////////////
    TextureHolder _textures;

    ////////////////////////////////////////////////////////////
    /// \brief Instant of SoundController to load and play all game sounds
    ////////////////////////////////////////////////////////////
    SoundController _soundController;

    ////////////////////////////////////////////////////////////
    /// \brief Instant of FontHolder to store and access all external game fonts
    ////////////////////////////////////////////////////////////
    FontHolder _fonts;

    ////////////////////////////////////////////////////////////
    /// \brief Instant of InputHandler to manage and process all user inputs to interact with the game
    ////////////////////////////////////////////////////////////
    InputHandler _inputHandler;

    ////////////////////////////////////////////////////////////
    /// \brief Game state to store what state the game is currently in, such as splash, Exiting, GameOverLose, GameOverWin
    ////////////////////////////////////////////////////////////
    game::GameState _gameState;

    ////////////////////////////////////////////////////////////
    /// \brief Primary RenderWindow to store all rendered game content
    ////////////////////////////////////////////////////////////
    sf::RenderWindow _mainWindow;

    ////////////////////////////////////////////////////////////
    /// \brief a two dimensional vector to store the width and high of the game screen
    ////////////////////////////////////////////////////////////
    sf::Vector2i _resolution;

    ////////////////////////////////////////////////////////////
    /// \brief integer to store the number of enemies that must be killed to end the game
    ////////////////////////////////////////////////////////////
    int _winCondition;

    ////////////////////////////////////////////////////////////
    /// \brief score object to store the current game score, such as enemies killed and longest life
    ////////////////////////////////////////////////////////////
    Score _score;

};

#endif //PROJECT_GAME_HPP
