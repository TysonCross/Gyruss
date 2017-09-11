/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    Starfield.hpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/11
/// \brief   Background Starfield effect
///
/// Creates a distribution of stars, and simulates moving
/// through this field, scaling and dimming them to fake a
/// a persepctive motion with parallax.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_STARFIELD_HPP
#define PROJECT_STARFIELD_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

struct Star
{
    float x;
    float y;
    float z;
};

class Starfield
{
public:
    Starfield();

private:

};

#endif //PROJECT_STARFIELD_HPP
