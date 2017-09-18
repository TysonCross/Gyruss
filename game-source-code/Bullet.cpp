/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    15/9/17
/// \brief   Projectile bullet Class
///
/// A bullet, can be an enemy or player projectile
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Bullet.hpp"
#include <iostream>

Bullet::Bullet(const TextureHolder &textureHolder,
               const SoundHolder &soundHolder,
               const common::Resolution resolution,
               float distanceFromCentre,
               float angle,
               float scale = 1,
               textures::ID id = textures::BulletPlayer) : _resolution(resolution),
                                                           _distanceFromCentre(distanceFromCentre),
                                                           _angle(angle),
                                                           _scale(scale),
                                                           _id(id)
{
    _rectArea = {0, 0, 70, 110}; // Individual sprite tile
    _spriteOffset = _rectArea.width; // Animated sprite tileset width
    _sprite.setTexture(textureHolder.get(_id));
    _sprite.setTextureRect(_rectArea);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);
    _sprite.setRotation(-_angle);
    _isMoving = true;
    setMove(_distanceFromCentre - (_distanceFromCentre*0.4)); // Spawn at Ship Gun barrel
    update();
}

void Bullet::setMove(float distance)
{
    _isMoving = true;
    _futureMoveValue = distance;
}

void Bullet::reset()
{
    _isMoving = false;
    _sprite.setPosition(_resolution.x*2,_resolution.y*2); // Move offscreen?
}

void Bullet::update()
{
    if (_isMoving)
    {
        _rectArea.left += _spriteOffset;
        if (_rectArea.left > (420 - 70)) // Sprite tileset width - individual tile
        {
            _rectArea.left = 0;
        }
        _sprite.setTextureRect(_rectArea);
        move();
    }
}

float Bullet::getDistanceFromCentre()
{
    return _distanceFromCentre;
}

sf::Sprite &Bullet::getSprite()
{
    return _sprite;
}

void Bullet::move()
{

    auto offset = 0.f;
    if(_distanceFromCentre==0)
        offset = _resolution.x*0.2;

    auto depthScale = ((_distanceFromCentre + offset)/(_resolution.x/2));
    _distanceFromCentre += _futureMoveValue * depthScale;
    auto x_pos = _distanceFromCentre * sin(common::degreeToRad(_angle));
    auto y_pos = _distanceFromCentre * cos(common::degreeToRad(_angle));
    auto scale = 1 + ((_distanceFromCentre - (_resolution.x / 2)) / (_resolution.x / 2));
    _sprite.setPosition(x_pos+(_resolution.x / 2),y_pos+(_resolution.y / 2));
    _sprite.setScale(scale * _scale,scale * _scale);

    // Dimming
    auto dimColor = (scale*200) + 100;
    _sprite.setColor(sf::Color(dimColor,dimColor,dimColor));
}