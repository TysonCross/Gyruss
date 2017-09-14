/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/11
/// \brief   Common functions, aliases and global constants
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "common.hpp"
#include <cmath>

namespace common
{
    float eulerFilter(float angle)
    {
        angle = fmod(angle, 360);
        if (angle < 0)
        {
            angle += 360;
        }
        return angle;
    }

    float degreeToRad(float degree)
    {
        return degree * (pi / 180);
    }
}
