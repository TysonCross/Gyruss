//--------------------------------------------------------------------------
// Student  1239448
// @file    InputHandler.cpp
// @author  Tyson Cross and Chris Maree
// @date    2017/09/09
// @brief   Description of file in project Project.
//
// Detailed description of file.
//
// Copyright (c) 2017 Tyson Cross and Chris Maree, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#include <iostream>
#include "InputHandler.hpp"
#include "Game.hpp"

void InputHandler::resolveKeyMapping(const key_map &keys_pressed, PlayerShip &playerShip)
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

    if (keys_pressed.count(sf::Keyboard::Space) > 0)
    {
        std::cout << "Shoot " << std::endl;
    }
}