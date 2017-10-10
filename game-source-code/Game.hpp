/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   Main Game controller
///
/// Handles the Game loop, and game states
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

using sf::Vector2i;
using sf::RenderWindow;
using sf::Clock;
using sf::Time;
using std::string;
using std::ifstream;
using std::ofstream;
using std::runtime_error;
using sf::Event;

////////////////////////////////////////////////////////////
/// \brief The main Game class
///
/// This class manages all game loops and creation of all game events and objects,
/// the game states, and basic game logic.
/// It also generates instances of all other controllers and handlers,
/// such as EntityController, InputHandler and the various types of ResourceHandler.
/// It is directly responsible for the playerShipObject.
////////////////////////////////////////////////////////////
class Game
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor for the main Game class.
    ///
    /// Sets the win condition, and the initial game state.
    ////////////////////////////////////////////////////////////
    Game();

    ////////////////////////////////////////////////////////////
    /// \brief Starts the game.
    ///
    /// Main game loop that runs while game is played. begins by
    /// setting up all vars and objects that need to be used.
    /// during game play, sits within a sub-game loop.
    /// The main window (sf::RenderWindow) is created.
    ///
    /// \see SFML/Window
    ////////////////////////////////////////////////////////////
    void Start();

    ////////////////////////////////////////////////////////////
    /// \brief Quits the game.
    ///
    /// The game ends when the window is closed, or the quit hotkey is used.
    /// \see Start
    ////////////////////////////////////////////////////////////
    void Quit();

private:
    ////////////////////////////////////////////////////////////
    /// \brief This is the main game loop that is used throughout game play.
    ///
    /// Loop begins by setting up all things needed going forward, such as clocks and predefined variables.
    /// It also is used in the creation of key objects, namely: PlayerShip, Shield, Score, EntityController and HUD.
    /// This function holds the game in the mainGame loop during game play and deals with player death sound and draw events.
    ///
    /// \see PlayerShip
    /// \see Shield
    /// \see Score
    /// \see EntityController
    /// \see HUD
    ////////////////////////////////////////////////////////////
    void startGameLoop();

    ////////////////////////////////////////////////////////////
    /// \brief Displays the game splashScreen. Used when before a game starts.
    ////////////////////////////////////////////////////////////
    void showSplashScreen();

    ////////////////////////////////////////////////////////////
    /// \brief Displays the end game screen.
    ///
    /// Based on if the player won or lost, a different screen is displayed.
    ///
    /// \param gameOutcome Boolean to represent if the player won the current game
    ////////////////////////////////////////////////////////////
    void showGameOverScreen(bool gameOutcome);

    ////////////////////////////////////////////////////////////
    /// \brief Pre-loads all required game resources.
    ///
    /// This loads all requires game assets, using ResourceHolder objects
    /// \see ResourceHolder
    /// \see ResourceHolder.inl
    ////////////////////////////////////////////////////////////
    void loadResources();

    ////////////////////////////////////////////////////////////
    /// \brief Compares current to previous  game highscores.
    ///
    /// Previous highscore is stored in a text file on disk.
    /// The higher value saved to "highscore.txt" in the game root directory.
    ////////////////////////////////////////////////////////////
    void recordHighScore();

    void playEventSounds(PlayerShip &playerShip, EntityController &entityController);

    void update(PlayerShip &playerShip, EntityController &entityController);

    ////////////////////////////////////////////////////////////
    /// \brief Used to draw all game elements by looping over all vectors of entites
    /// and drawing the underlying sprite. Called on every frame.
    ///
    /// /ToDo
    ////////////////////////////////////////////////////////////
    void render(StarField &starField, const PlayerShip &playerShip,
                EntityController &entityController, Shield &shield, HUD &hud);

    ////////////////////////////////////////////////////////////
    /// /ToDo
    ////////////////////////////////////////////////////////////
    void endGameCheck(const PlayerShip &playerShip);

    ////////////////////////////////////////////////////////////
    /// /ToDo
    ////////////////////////////////////////////////////////////
    void playerDeathEvents(PlayerShip &playerShip, EntityController &entityController);

    ////////////////////////////////////////////////////////////
    /// /ToDo
    ////////////////////////////////////////////////////////////
    void shakeWindow();

    ////////////////////////////////////////////////////////////
    /// /ToDo
    ////////////////////////////////////////////////////////////
    void debugKeys(const Event &event, PlayerShip &playerShip, EntityController &entityController);

    ////////////////////////////////////////////////////////////
    /// \brief A ResourceHolder of type Texture to store all game art assets
    /// \see sf::Texture
    ////////////////////////////////////////////////////////////
    TextureHolder _textures;

    ////////////////////////////////////////////////////////////
    /// \brief A ResourceHolder of type SoundBuffer to load and play all game sounds
    /// \see sf::Sound
    /// \see sf::SoundBuffer
    ////////////////////////////////////////////////////////////
    SoundController _soundController;

    ////////////////////////////////////////////////////////////
    /// \brief A ResourceHolder of type sf::Font to store and access typefaces
    /// \see sf::Font
    ////////////////////////////////////////////////////////////
    FontHolder _fonts;

    ////////////////////////////////////////////////////////////
    /// \brief Data member of type InputHandler to manage and process all user inputs to interact with the game
    ////////////////////////////////////////////////////////////
    InputHandler _inputHandler;

    ////////////////////////////////////////////////////////////
    /// \brief Game state to store what state the game is currently in.
    ///
    /// The availible states are Game::Splash, Game::Exiting, Game::GameOverLose, Game::GameOverWin
    ////////////////////////////////////////////////////////////
    game::GameState _gameState;

    ////////////////////////////////////////////////////////////
    /// \brief Primary RenderWindow for displaying the game
    ////////////////////////////////////////////////////////////
    RenderWindow _mainWindow;

    ////////////////////////////////////////////////////////////
    /// \brief A two dimensional vector to store the width and high of the game screen
    /// \see sf::Vector2i
    ////////////////////////////////////////////////////////////
    Vector2i _resolution;

    ////////////////////////////////////////////////////////////
    /// \brief integer to store the number of enemies that must be killed to end the game
    ////////////////////////////////////////////////////////////
    int _winCondition;

    ////////////////////////////////////////////////////////////
    /// \brief score object to store the current game score, such as enemies killed and longest life
    ////////////////////////////////////////////////////////////
    Score _score;

    ////////////////////////////////////////////////////////////
    /// /ToDo
    ////////////////////////////////////////////////////////////
    Vector2i _windowPosition;

    ////////////////////////////////////////////////////////////
    /// /ToDo
    ////////////////////////////////////////////////////////////
    int _shaking; // Controls the shaking of the main renderWindow when a player loses a life
};

#endif //PROJECT_GAME_HPP
