/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    Starfield.cpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/11
/// \brief   Implementation of the background star effect
///
/// Creates a distribution of stars, and simulates moving
/// through this field, scaling and dimming them to fake a
/// a perspective motion with parallax.
///
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Starfield.hpp"
#include <iostream>
#include <cmath>

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
StarField::StarField(sf::RectangleShape &star_shape,
                     const unsigned int x,
                     const unsigned int y,
                     const int max_depth,
                     const int number_of_stars,
                     float max_size) : _width(x),
                                       _height(y),
                                       _max_depth(max_depth),
                                       _number_of_stars(number_of_stars),
                                       _max_size(max_size)
{
    const auto _light_shift_amount = 4; // Controls amount of sparkly/rainbow stars
                                        // _light_shift_amount = 0 : undefined behaviour
                                        // _light_shift_amount = 1 : all stars are rainbow
                                        // _light_shift_amount > 1 : reduces the no. of rainbow stars

    _star_scale = 0.0f;                 // spawn invisible
    star_shape.setSize({_star_scale,_star_scale});

    //Initialize star random placement
    for( auto i = 0; i < number_of_stars; i++)
    {
        starPosition star_pos;
        star_pos.x = rand() % _width - (_width / 2.0f);
        star_pos.y = rand() % _height - (_height / 2.0f);
        star_pos.z = -1.0f * (rand() % max_depth) - max_depth;
        _starField.push_back(star_pos);

        std::cout << "Initial Position of star[" << i << "] : (" << star_pos.x << ", " << star_pos.y << ", " << star_pos.z << ")" << std::endl;
    }
}

////////////////////////////////////////////////////////////
/// \brief Moves rhe stars in the starField object
///
/// \param speed The delta to move the stars
///
/// \param star Pointer to a RectangleShape to draw the stars
///
////////////////////////////////////////////////////////////
void StarField::moveStars(sf::RectangleShape &star_shape,
                          float speed)
{
//    srand(127);

//    for (auto &star : _starField)
        auto star = _starField.at(0);
    for (int i = 0; i < _starField.size(); ++i)
    {
        star = _starField.at(i);
        // Move
        star.z += speed;

//        // Rainbow candy (stylized Red/Blue shift)
//        // 0-255,  half range * 2 is brighter color
//        auto r = rand() % 128 * 2;
//        auto g = rand() % 128 * 2;
//        auto b = rand() % 128 * 2;

        // Boundaries of stars: between camera plane (0) and max_depth (-z)
        if (star.z >= 0.0f)         // If star is at or behind camera
        {
            star.z = -_max_depth;   // send it to the furthest distance

        }
        if (star.z <= -_max_depth)  // star is beyond the furthest distance
        {
            _star_scale = 0;        // so make it invisible
        }
        else                        //Otherwise, move the stars along Z, slower the further away
        {
            _star_scale = (star.z + (_max_depth)) / (_max_depth);
        }

//        if (i %_light_shift_amount) // Dimming
//        {
//            star_shape.setFillColor(sf::Color(255 * _star_scale, 255 * _star_scale, 255 * _star_scale));
//        }
//        else
//        {
//            star_shape.setFillColor(sf::Color(r * _star_scale, g * _star_scale, b * _star_scale));
//        }

        //if (i==0) std::cout << "1st Position of star[" << i << "] : (" << star.x << ", " << star.y << ", " << star.z << ")" << std::endl;

//        // Scaling
//        star_shape.setSize(sf::Vector2f(_max_size * _star_scale, _max_size * _star_scale));

        // Moving
        star_shape.setPosition(sf::Vector2f(-star.x / star.z + (_width / 2),
                                            star.y / star.z + (_height / 2)));

        //if (i==0) std::cout << "2nd Position of star[" << i << "] : (" << star.x << ", " << star.y << ", " << star.z << ")" << std::endl;

    }
}

std::vector<starPosition>& StarField::getStarField()
{
    return _starField;
}

//_starField;
//_light_shift_amount;




