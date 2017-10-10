/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   Read in the map of current keypresses
///
/// Reads in the key presses during the last polled game Loop,
/// and maps these keys to actions
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_INPUTHANDLER_HPP
#define PROJECT_INPUTHANDLER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "EntityController.hpp"
#include <map>

using keyMap = std::map<int, bool>;
using sf::Event;
using sf::Keyboard;

////////////////////////////////////////////////////////////
/// \brief The InputHandler class
///
/// Handles player input to control the playerShip (moving, shooting)
////////////////////////////////////////////////////////////
class InputHandler
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Initialises the default button state for the SpaceBar (to 0, i.e not pressed)
    ////////////////////////////////////////////////////////////
    InputHandler();

    ////////////////////////////////////////////////////////////
    /// \brief Polls the keyboard input events
    ///
    /// \param gameState Closing the window sets the gameState to Exiting, so the game will close.
    /// \param playerShip The playerShip is strongly coupled to inputHandler, as the objects are interdependent
    /// \param event The sf::Event Object is passed by ref from Game, to capture keyboard input during the polling period
    /// \see PlayerShip.hpp
    /// \see sf::Event
    /// \see Game.hpp
    ////////////////////////////////////////////////////////////
    void pollInput(game::GameState &gameState,
                   PlayerShip &playerShip,
                   const Event &event);

    ////////////////////////////////////////////////////////////
    /// \brief Sets up any player movement on the playerShip setMove() command,
    /// depending on the input during the polling
    ///
    /// \param playerShip The playerShip object to set a move up for (planned but not performed)
    /// \param deltaTime The amount of time that has passed since the previous update
    /// \see PlayerShip.hpp
    /// \see Game.hpp
    ////////////////////////////////////////////////////////////
    void setPlayerShipMove(PlayerShip &playerShip,
                           const float deltaTime);

    ////////////////////////////////////////////////////////////
    /// \brief Resets the inputHandler object
    ////////////////////////////////////////////////////////////
    void reset();

private:
    ////////////////////////////////////////////////////////////
    /// \param Stores the movement state of the player to the left
    ////////////////////////////////////////////////////////////
    bool _isMovingLeft;

    ////////////////////////////////////////////////////////////
    /// \param Stores the movement state of the player to the right
    ////////////////////////////////////////////////////////////
    bool _isMovingRight;

    ////////////////////////////////////////////////////////////
    /// \param Stores the previous state of the space-bar (the default shoot button)
    ///
    /// The player should not be able to hold the button down, and
    /// each pressing of the shoot button should result in a separate shoot event
    ////////////////////////////////////////////////////////////
    bool _previousButtonState; // 1 is pressed, 0 is released
};

#endif //PROJECT_INPUTHANDLER_HPP
