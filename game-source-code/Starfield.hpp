/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
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
#include "SFML/Window.hpp"
#include <vector>
#include <iterator>
#include "common.hpp"

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
              common::Resolution resolution,
              const int max_depth,
              const int number_of_stars,
              float max_size = 6.0f);

    ////////////////////////////////////////////////////////////
    /// \brief Moves the star positions along -Z in the starField object,
    /// then draws a square at each position in the starField.
    ///
    /// The movement along Z is not physically accurate,
    /// but uses a fast approximation:
    /// (Δposition - max_depth) / max_depth
    ///
    /// \param speed The delta to move the stars
    /// \param window The sf:Window object to draw and render to
    ///
    /// \see sf::Window
    ////////////////////////////////////////////////////////////
    void moveAndDrawStars(
                          sf::RenderWindow &renderWindow,
                          float speed = 0.0008);

    ////////////////////////////////////////////////////////////
    /// \brief Returns a reference to the StarField object
    /// (for iterating through the elements)
    ///
    ////////////////////////////////////////////////////////////
    std::vector<common::position> &getStarField();

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<common::position> _starField;
    sf::CircleShape _star_shape;
    //sf::RectangleShape _star_shape;
    const unsigned int _width;
    const unsigned int _height;
    const int _max_depth;
    const int _number_of_stars;
    const float _max_size;
    float _star_scale;
    /// \brief Controls amount of colorful stars
    ///
    /// _light_shift_amount = 0 : undefined behaviour
    /// _light_shift_amount = 1 : all stars are colorful
    /// _light_shift_amount > 1 : reduces no. of colorful stars
    const signed int _light_shift_amount = 4;
};

#endif //PROJECT_STARFIELD_HPP
