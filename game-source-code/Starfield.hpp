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

////////////////////////////////////////////////////////////
/// \brief Simple struct of 3 floats, a co-ordinate system (x,y,z)
///
////////////////////////////////////////////////////////////
struct starPosition
{
    float x;
    float y;
    float z;
};

////////////////////////////////////////////////////////////
/// \brief Creates a starfield object, a vector of 3d points
/// The field is made up of many stars (a struct of three floats
/// The stars are psuedorandomly generated to fill the volume
/// enclosed by screen height * screen widgth * maximum depth
///
/// \param resourceMapper The resourceMapper object that
/// contains the path to the texture(s) for the sprite
/// \param number_of_stars The number of stars in the vector
/// \param max_depth distance from the "camera plane"
/// \param max_size The maximum scale of the rectangle of a star
///
////////////////////////////////////////////////////////////
class StarField
{
public:
    StarField(
              sf::RectangleShape &star_shape,
              const unsigned int x,
              const unsigned int y,
              const int max_depth,
              const int number_of_stars,
              float max_size = 8.0f);

    ////////////////////////////////////////////////////////////
    /// \brief Moves the star positions along -Z in the starField object
    /// Then draws a square at each position in the starField.
    /// \
    /// \param speed The delta to move the stars
    ///
    /// \param star Pointer to a RectangleShape to draw the stars
    ///
    ////////////////////////////////////////////////////////////
    void moveAndDrawStars(
                          sf::RectangleShape &star_shape,
                          sf::RenderWindow &renderWindow,
                          float speed = 0.001);

    std::vector<starPosition>& getStarField();

private:
    std::vector<starPosition> _starField;
    const unsigned int _width;
    const unsigned int _height;
    const int _max_depth;
    const int _number_of_stars;
    const float _max_size;
    float _star_scale;
    const signed int _light_shift_amount = 2;
    // _light_shift_amount: Controls amount of colorful stars
    // _light_shift_amount = 0 : undefined behaviour
    // _light_shift_amount = 1 : all stars are colorful
    // _light_shift_amount > 1 : reduces no. of colorful stars
};

#endif //PROJECT_STARFIELD_HPP
