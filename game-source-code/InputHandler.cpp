/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    InputHandler.cpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/09
/// \brief   Read in the map of current keypresses
///
/// Reads in the key presses during the last polled game Loop,
/// and maps these keys to actions
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "InputHandler.hpp"

using key_map = std::map<int, bool>;

void InputHandler::resolveKeyMapping(const key_map &keys_pressed, PlayerShip& playerShip)
{
    const int MOVE_AMOUNT = 3;

    if (keys_pressed.count(sf::Keyboard::Left) > 0)
    {
        playerShip.move(-MOVE_AMOUNT);
    }

    if (keys_pressed.count(sf::Keyboard::Right) > 0)
    {
        playerShip.move(MOVE_AMOUNT);
    }

//    if (keys_pressed.count(sf::Keyboard::Space) > 0)
//    {
//        //playerShip.shoot();
//    }
}