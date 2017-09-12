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
    ////////////////////////////////////////////////////////////
    /// \brief A simple 3d co-ordinate container of three floats
    ///
    ////////////////////////////////////////////////////////////
    struct Star
    {
        float x;
        float y;
        float z;
    };

    ////////////////////////////////////////////////////////////
    /// \brief A simple 2d container of 2 ints
    ///
    ////////////////////////////////////////////////////////////
    struct Resolution
    {
        unsigned int x;
        unsigned int y;
    };
}

#endif //PROJECT_COMMON_HPP
