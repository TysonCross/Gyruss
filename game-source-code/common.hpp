//--------------------------------------------------------------------------
// Student  1239448
// @file    common.hpp
// @author  Tyson Cross and Chris Maree
// @date    2017/09/10
// @brief   Common functions, aliases and global constants
//
// Copyright (c) 2017 Tyson Cross and Chris Maree, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#ifndef PROJECT_COMMON_HPP
#define PROJECT_COMMON_HPP
#include <utility>

//GLOBAL VARIABLES
const float pi = 3.1415;
const float phi = 1.618;

//USEFUL FUNCTIONS
struct Resolution
{
    unsigned int x;
    unsigned int y;
};


//TEMP GLOBAL VARIABLES
const Resolution resolution = {1920,1080}; //BAD!!! Todo: Add resolution to resource mapper instead

#endif //PROJECT_COMMON_HPP
