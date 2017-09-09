//--------------------------------------------------------------------------
// Student  1239448
// @file    InputHandler.cpp
// @author  Tyson Cross
// @date    2017/09/09
// @brief   Description of file in project Project.
//
// Detailed description of file.
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#include <iostream>
#include "InputHandler.hpp"

void InputHandler::resolveKeyMapping(const key_map& keys_pressed)
{
    std::cout << " Keyed pressed: ";
    for (auto &key_value : keys_pressed)
    {
        std::cout << key_value.first << " ";
    }
    std::cout << std::endl;
}