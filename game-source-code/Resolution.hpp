/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    PlayerShip.hpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/09
/// \brief   Basic Resolution class to hold the screen dimensions
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_RESOLUTION_HPP
#define PROJECT_RESOLUTION_HPP

struct Res
{
    unsigned int x;
    unsigned int y;
};

class Resolution
{
public:
    Resolution(unsigned int x, unsigned int y);
    Res getDimensions();
    unsigned int width();
    unsigned int height();

private:
    unsigned int _x;
    unsigned int _y;
};
#endif //PROJECT_RESOLUTION_HPP
