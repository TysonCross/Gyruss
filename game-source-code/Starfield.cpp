/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/11
/// \brief   Implementation of the background star effect
///
/// Creates a distribution of stars, and simulates moving
/// through this field, scaling and dimming them to fake a
/// a perspective motion with parallax (An orthographic projection)
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Starfield.hpp"

StarField::StarField(
                     common::Resolution resolution,
                     const int max_depth,
                     const int number_of_stars,
                     float max_size) : _width(resolution.x),
                                       _height(resolution.y),
                                       _max_depth(max_depth),
                                       _number_of_stars(number_of_stars),
                                       _max_size(max_size)
{
    srand(127); // A nice prime
    _star_scale = 0.0f;
    _star_shape.setPointCount(8);
    _star_shape.setRadius(max_size);

    //Initialize star random placement
    for( auto i = 0; i < number_of_stars; i++)
    {
        common::position star_pos;
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
        //srand(i); // Colors streak instead of flicker
        // Move
        star_pos.z += speed;            //Move the stars along z, towards camera
        i++;                            // For counting which stars to make colorful

        // Rainbow candy
        auto r = rand() % 128 * 2;      // 0-255,  half range * 2 is brighter color
        auto g = rand() % 128 * 2;      // These random colors help simulate a
        auto b = rand() % 128 * 2;      // stylized Red/Blue shift

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

        // Scaling
        _star_shape.setRadius(_max_size * _star_scale);

        // Moving
        _star_shape.setPosition({-star_pos.x / star_pos.z + (_width / 2),
                                star_pos.y / star_pos.z + (_height / 2)});

        renderWindow.draw(_star_shape);
    }
}

std::vector<common::position>& StarField::getStarField()
{
    return _starField;
}
