/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    Starfield.hpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/11
/// \brief   Background Starfield effect
///
/// Definition for the starfield effect, a moving field of pixels
/// creating the illusion of flying down a tunnel in space.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_STARFIELD_HPP
#define PROJECT_STARFIELD_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <vector>
#include <iterator>
#include "ResourceMapper.hpp"

struct starPosition
{
    float x;
    float y;
    float z;
};

class StarField
{
public:
    StarField(sf::RectangleShape &star_shape,
              const unsigned int x,
              const unsigned int y,
              const int max_depth,
              const int number_of_stars,
              float max_size = 8.0f);

    void moveStars(sf::RectangleShape &star_shape,
                   sf::RenderWindow &renderWindow,
                   float speed = 0.081);

    std::vector<starPosition>& getStarField();

private:
    std::vector<starPosition> _starField;
    const unsigned int _width;
    const unsigned int _height;
    const int _max_depth;
    const int _number_of_stars;
    const float _max_size;
    float _star_scale;
    signed int _light_shift_amount;



};

#endif //PROJECT_STARFIELD_HPP
