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

PlayerShip::PlayerShip(
                        const ResourceMapper &resourceMapper,
                        common::Resolution resolution,
                        float distanceFromCentre,
                        float angle = 0,
                        float scale = 1) : _resolution(resolution)
{
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
    _angle = common::eulerFilter(_angle);
    //Rotate coordinate system by 90 degrees
    _sprite.setPosition(_distanceFromCentre * sin(common::degreeToRad(_angle)) + _resolution.x / 2,
                        _distanceFromCentre * cos(common::degreeToRad(_angle)) + _resolution.y / 2);
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
