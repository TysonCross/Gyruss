//--------------------------------------------------------------------------
// Student  1239448
// @file    InputHandler.hpp
// @author  Tyson Cross and Chris Maree
// @date    2017/09/09
// @brief   Read in the map of current keypresses
//
// Reads in the key presses during the last polled game Loop,
// and maps this keys to actions.
//
// Copyright (c) 2017 Tyson Cross and Chris Maree, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#ifndef PROJECT_INPUTHANDLER_HPP
#define PROJECT_INPUTHANDLER_HPP
#include "Game.hpp"
#include "PlayerShip.hpp"
#include <map>

//Todo: abstract object passed to use the mapping key actions
//using keyMapping =  std::map<int,enum>; //Research tuples, dictionary, or enum?>

class InputHandler
{
public:
    void resolveKeyMapping(const key_map &keys_pressed,
                           PlayerShip &playerShip);
private:

};
#endif //PROJECT_INPUTHANDLER_HPP
