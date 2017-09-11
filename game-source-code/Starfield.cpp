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
//#include <iostream>
#include <cmath>

StarField::StarField(
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
    _star_scale = 0.0f;                 // spawn invisible
    _star_shape.setSize({_max_size,_max_size});

    //Initialize star random placement
    for( auto i = 0; i < number_of_stars; i++)
    {
        starPosition star_pos;
        star_pos.x = rand() % _width - (_width / 2.0f);
        star_pos.y = rand() % _height - (_height / 2.0f);
        star_pos.z = -1.0f * (rand() % max_depth) - max_depth;
        _starField.push_back(star_pos);
    }
}


void StarField::moveAndDrawStars(
                                 sf::RenderWindow &renderWindow,
                                 float speed)
{
    auto i = 0;
    for (auto &star_pos : _starField)
    {
        // Move
        star_pos.z += speed;            //Move the stars along z, towards camera
        i++;                            // For counting which stars to make colorful

        // Rainbow candy (stylized Red/Blue shift)
        auto r = rand() % 128 * 2;      // 0-255,  half range * 2 is brighter color
        auto g = rand() % 128 * 2;
        auto b = rand() % 128 * 2;

        // Boundaries of stars: between camera plane (0) and max_depth (-z)
        if (star_pos.z >= 0.0f)         // If star is at or behind camera
        {
            star_pos.z = -_max_depth;   // send it to the furthest distance

        }
        if (star_pos.z <= -_max_depth)  // star is beyond the furthest distance
        {
            _star_scale = 0;            // make it invisible
        }
        else                            // Otherwise, move the stars along Z, slower if further away
        {
            _star_scale = (star_pos.z + (_max_depth)) / (_max_depth);
        }
        if (i %_light_shift_amount)     // Dimming
        {
            _star_shape.setFillColor(sf::Color(255 * _star_scale, 255 * _star_scale, 255 * _star_scale));
        }
        else
        {
            _star_shape.setFillColor(sf::Color(r * _star_scale, g * _star_scale, b * _star_scale));
        }

//        std::cout << "A: star[" << i << "] : " << star_pos.x << " , " << star_pos.y <<  std::endl;

        // Scaling
        _star_shape.setSize(sf::Vector2f(_max_size * _star_scale, _max_size * _star_scale));

        // Moving
        _star_shape.setPosition({-star_pos.x / star_pos.z + (_width / 2),
                                star_pos.y / star_pos.z + (_height / 2)});

//        std::cout << "B: star[" << i << "] : " << star_pos.x << " , " << star_pos.y <<  std::endl;

        renderWindow.draw(_star_shape);
    }
}

std::vector<starPosition>& StarField::getStarField()
{
    return _starField;
}

//_starField;
//_light_shift_amount;




