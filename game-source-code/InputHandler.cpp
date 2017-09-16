/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   Read in the map of current keypresses
///
/// Reads in the key presses during the last polled game Loop,
/// and maps these keys to actions
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "InputHandler.hpp"

using key_map = std::map<int, bool>;

void InputHandler::resolveKeyMapping(const key_map &keys_pressed)
{

    if (keys_pressed.count(sf::Keyboard::Left) > 0)
    {
        _isMovingLeft = true;
    }
    else
    {
        _isMovingLeft = false;
    }

    if (keys_pressed.count(sf::Keyboard::Right) > 0)
    {
        _isMovingRight = true;
    }
    else
    {
        _isMovingRight = false;

    }

}

void InputHandler::update(PlayerShip &playerShip, float deltaTime)
{
    const auto moveAmount = 260.f;
    auto move = 0.f;

    if (_isMovingLeft)
    {
        move -= moveAmount;

    }
    if (_isMovingRight)
    {
        move += moveAmount;
    }

    playerShip.move(move * deltaTime);
}
