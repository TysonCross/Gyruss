/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    PlayerShip.cpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/09
/// \brief   Description of file in project Project.
///
/// Detailed description of file.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "PlayerShip.hpp"
#include <iostream>

////////////////////////////////////////////////////////////
/// \brief Converts an angle from degrees to radians
///
////////////////////////////////////////////////////////////
float degreeToRad(float degree)
{
    return degree * (pi / 180);
}

////////////////////////////////////////////////////////////
/// \brief Ensures that the angle is always between 0 and 360
///
////////////////////////////////////////////////////////////
int eulerFilter(int angle)
{
    angle = angle % 360;
    if (angle < 0)
    {
        angle += 360;
    }
    return angle;
}

////////////////////////////////////////////////////////////
/// \brief Returns the Sprite object of the Class
///
/// \param resourceMapper The resourceMapper object that
/// contains the path to the texture(s) for the sprite
/// \param distanceFromCentre The fixed radius of the circle
/// that the ship flys around
/// \param angle The angle in degrees around the circle of movement
/// \param scale The scale of the sprite
///
////////////////////////////////////////////////////////////
PlayerShip::PlayerShip(
                        const ResourceMapper &resourceMapper,
                        float distanceFromCentre,
                        int angle = 0,
                        float scale = 1)
{
    _distanceFromCentre = distanceFromCentre;
    _angle = angle;
    _scale = scale;

    _texture.loadFromFile(resourceMapper.getResource("PlayerShip"));
    _sprite.setTexture(_texture);
    _sprite.setScale(_scale, _scale);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

    move(0); //Initialised position at bottom of play area, not screen origin top-left
}

////////////////////////////////////////////////////////////
/// \brief Moves the player ship around a circle by angle
////////////////////////////////////////////////////////////
void PlayerShip::move(int angle)
{
    _angle += angle;
    _angle = eulerFilter(_angle);
    //Rotate coordinate system by 90 degrees
    _sprite.setPosition(_distanceFromCentre * sin(degreeToRad(_angle)) + resolution.x / 2,
                        _distanceFromCentre * cos(degreeToRad(_angle)) + resolution.y / 2);
    _sprite.setRotation(-1 * _angle);
}

////////////////////////////////////////////////////////////
/// \brief Returns the Sprite object of the Class by ref
////////////////////////////////////////////////////////////
sf::Sprite &PlayerShip::getSprite()
{
    return _sprite;
}

////////////////////////////////////////////////////////////
/// \brief Returns the Tectuxe object of the Class by ref
////////////////////////////////////////////////////////////
sf::Texture &PlayerShip::getTexture()
{
    return _texture;
}
