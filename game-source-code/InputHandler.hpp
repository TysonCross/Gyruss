//--------------------------------------------------------------------------
// Student  1239448
// @file    InputHandler.hpp
// @author  Tyson Cross
// @date    2017/09/09
// @brief   Read in the map of current keypresses
//
// Reads in the key presses during the last polled game Loop,
// and maps this keys to actions.
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#ifndef PROJECT_INPUTHANDLER_HPP
#define PROJECT_INPUTHANDLER_HPP
#include "Game.hpp"
#include <map>

//using keyMapping =  std::map<int,enum>; //Research tuples, dictionary, or enum?>

class InputHandler
{
public:
    void resolveKeyMapping(const key_map& keys_pressed); //Todo: add object passed to use the mapped key actions
private:
//    std::map keyMapping{}
};
#endif //PROJECT_INPUTHANDLER_HPP
