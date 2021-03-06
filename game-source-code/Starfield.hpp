/////////////////////////////////////////////////////////////////////
/// \brief   Background Starfield effect
///
/// Definition for the starField effect, a moving field of pixels
/// creating the illusion of flying down a tunnel in space.
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_STARFIELD_HPP
#define PROJECT_STARFIELD_HPP

#include "SFML/Graphics.hpp"
#include <vector>
#include <iterator>
#include "common.hpp"

using sf::CircleShape;
using sf::Vector2i;

////////////////////////////////////////////////////////////
/// \brief Creates a starField object, a vector of 3d points
/// The field is made up of many stars (each star is a
/// common::position, a struct of three floats
/// The stars are psuedo-randomly generated to fill the volume
/// enclosed by screen height * screen width * maximum depth
////////////////////////////////////////////////////////////
class StarField
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief StarField constructor.
    ///
    /// \param resolution screen size used to calculate the dimensions of the screen
    /// \param max_depth distance from the "camera plane"
    /// \param number_of_stars The number of stars in the vector
    /// \param max_size The maximum scale of the rectangle of a star
    ////////////////////////////////////////////////////////////
    StarField(const Vector2i resolution,
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
    /// \param renderWindow The sf:Window object to draw and render to
    /// \param speed The delta to move the stars
    /// \param light_shift_amount Controls amount of colorful stars
    /// light_shift_amount = 0 : undefined behaviour
    /// light_shift_amount = 1 : all stars are colorful
    /// light_shift_amount > 1 : reduces no. of colorful stars
    ///
    /// \see [SFML/Window](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Window.php)
    ////////////////////////////////////////////////////////////
    void moveAndDrawStars(
                          sf::RenderWindow &renderWindow,
                          float speed = 0.0008,
                          int light_shift_amount = 3);

    ////////////////////////////////////////////////////////////
    /// \brief Returns a reference to the StarField object
    /// (for iterating through the elements)
    /// \return A vector of type position (the star objects)
    ////////////////////////////////////////////////////////////
    std::vector<common::position> &getStarField();

private:

    ////////////////////////////////////////////////////////////
    /// \brief Vector to store the starField point positions in space.
    /// This vector has all stars stored in it at any point in time
    ////////////////////////////////////////////////////////////
    std::vector<common::position> _starField;

    ////////////////////////////////////////////////////////////
    /// \brief Defines the shape of the star that flies out of the centre of the screen
    ////////////////////////////////////////////////////////////
    CircleShape _star_shape;

    ////////////////////////////////////////////////////////////
    /// \brief Width of the screen. extracted from the resolution at time of construction
    ////////////////////////////////////////////////////////////
    const unsigned int _width;

    ////////////////////////////////////////////////////////////
    /// \brief Height of the screen. extracted from the resolution at time of construction
    ////////////////////////////////////////////////////////////
    const unsigned int _height;

    ////////////////////////////////////////////////////////////
    /// \brief Defines the maximum depth(z index) that the star can be in
    ////////////////////////////////////////////////////////////
    const int _max_depth;

    ////////////////////////////////////////////////////////////
    /// \brief Limits the number of stars that can be in the space at any point in time
    ////////////////////////////////////////////////////////////
    const int _number_of_stars;

    ////////////////////////////////////////////////////////////
    /// \brief Used to define the star shape radius and scaling
    ////////////////////////////////////////////////////////////
    const float _max_size;

    ////////////////////////////////////////////////////////////
    /// \brief Used to define the star shape radius and scaling
    ////////////////////////////////////////////////////////////
    float _star_scale;
};

#endif //PROJECT_STARFIELD_HPP
