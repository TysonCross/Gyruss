/////////////////////////////////////////////////////////////////////
/// \brief   Common functions, aliases and global constants
/////////////////////////////////////////////////////////////////////

#include "common.hpp"

namespace common
{
    float angleFilter(float angle)
    {
        angle = float(fmod(angle, 360));
        if (angle < 0)
            angle += 360;
        return angle;
    }

    float degreeToRad(float degree)
    {
        return degree * (float(M_PI) / 180);
    }

    float radToDegree(float radian)
    {
        return radian * 180 / float(M_PI);
    }

    string padIntToString(unsigned int value, int paddingLength, char padChar)
    {
        string s = to_string(value);
        if (paddingLength>s.length())
        {
            s.insert(s.begin(), paddingLength - s.size(), padChar);
        }
        return s;
    }
}
