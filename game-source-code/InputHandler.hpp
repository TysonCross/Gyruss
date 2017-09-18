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
#include "PlayerShip.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include <map>

using key_map = std::map<int, bool>;

class InputHandler
{
public:
    void pollInput(game::GameState &gameState,
                   PlayerShip &playerShip,
                   const sf::Event &event,
                   bool &previousButtonState);

    void update(PlayerShip& playerShip, float deltaTime);


private:
    bool _isMovingLeft;
    bool _isMovingRight;
    bool _isShooting;
    sf::RenderWindow _mainWindow;
    key_map _keysPressed;
};

#endif //PROJECT_INPUTHANDLER_HPP
