/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    PlayerShip.hpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/09
/// \brief   Basic Resolution class to hold the screen dimensions
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Resolution.hpp"

Resolution::Resolution(unsigned int x,
                       unsigned int y) : _x(x),
                                         _y(y)
{}

Res Resolution::getDimensions()
{
    return {_x,_y};
}

unsigned int Resolution::width()
{
    return _x;
}

unsigned int Resolution::height()
{
    return _y;
}
