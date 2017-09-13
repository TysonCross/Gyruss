/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   The main player ship
///
/// The player's ship flies around the centre of the screen in a circle of fixed
/// radius, shooting at enemies.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "PlayerShip.hpp"
#include "common.hpp"

const float pi = 3.1415;

////////////////////////////////////////////////////////////
/// \brief Ensures that the angle is always between 0 and 360
///
////////////////////////////////////////////////////////////
float eulerFilter(float angle)
{
    angle = fmod(angle,360);
    if (angle < 0)
    {
        angle += 360;
    }
    return angle;
}

////////////////////////////////////////////////////////////
/// \brief Converts an angle from degrees to radians
///
////////////////////////////////////////////////////////////
float degreeToRad(float degree)
{
    return degree * (pi / 180);
}

PlayerShip::PlayerShip(
                        const ResourceMapper &resourceMapper,
                        common::Resolution resolution,
                        float distanceFromCentre,
                        float angle = 0,
                        float scale = 1) : _width(resolution.x),
                                           _height(resolution.y)
{
    //_width = std::stoi(resourceMapper.getResourceValues("Resolution").at(0));
    //_height = std::stoi(resourceMapper.getResourceValues("Resolution").at(1));

    _distanceFromCentre = distanceFromCentre;
    _angle = angle;
    _scale = scale;

    if(!_buffer.loadFromFile(resourceMapper.getResource("PlayerShipSound")))
    {
        return; //execution error; resource missing
    }
    _shootSound.setBuffer(_buffer);

    if(!_texture.loadFromFile(resourceMapper.getResource("PlayerShip")))
    {
        return; //execution error; resource missing
    }
    _sprite.setTexture(_texture);
    _sprite.setScale(_scale, _scale);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

    move(0); //Initialised position at bottom of play area, not screen origin top-left
}

void PlayerShip::move(float angle)
{
    _angle += angle;
    _angle = eulerFilter(_angle);
    //Rotate coordinate system by 90 degrees
    _sprite.setPosition(_distanceFromCentre * sin(degreeToRad(_angle)) + _width / 2,
                        _distanceFromCentre * cos(degreeToRad(_angle)) + _height / 2);
    _sprite.setRotation(-1 * _angle);
}

void PlayerShip::shoot()
{
    _shootSound.stop();
    _shootSound.play();
}

sf::Sprite &PlayerShip::getSprite()
{
    return _sprite;
}

sf::Texture &PlayerShip::getTexture()
{
    return _texture;
}
