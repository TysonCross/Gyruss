/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/10
/// \brief   Common functions, aliases and global constants
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_COMMON_HPP
#define PROJECT_COMMON_HPP

//USEFUL FUNCTIONS and CONSTANTS
namespace common
{
    const float pi = 3.1415;

    /// \brief A simple 2d container of 2 ints
    struct Resolution
    {
        unsigned int x;
        unsigned int y;
    };

    /// \brief Simple struct of 3 floats, a co-ordinate system (x,y,z)
    struct position
    {
        float x;
        float y;
        float z;
    };

    /// \brief Ensures that the angle is always between 0 and 360
    float degreeToRad(float degree);

    /// \brief Converts an angle from degrees to radians
    float angleFilter(float angle);

}

#endif //PROJECT_COMMON_HPP
