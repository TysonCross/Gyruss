/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   Read in the map of current keypresses
///
/// Reads in the key presses during the last polled game Loop,
/// and maps these keys to actions.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_INPUTHANDLER_HPP
#define PROJECT_INPUTHANDLER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "EntityController.hpp"
#include <map>

using keyMap = std::map<int, bool>;

class InputHandler
{
public:
    InputHandler();

    void pollInput(game::GameState &gameState,
                   PlayerShip &playerShip,
                   const sf::Event &event);

    void update(PlayerShip &playerShip,
                const float deltaTime);

    void reset();

private:
    bool _isMovingLeft;
    bool _isMovingRight;
    bool _previousButtonState; // 1 is pressed, 0 is released
};

#endif //PROJECT_INPUTHANDLER_HPP
