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

Bullet::Bullet(const TextureHolder &textureHolder,
             common::Resolution resolution,
             float distanceFromCentre,
             float angle,
             float scale = 1,
             textures::ID id = textures::BulletPlayer) : _resolution(resolution),
                                                        _id(id),
                                                        _distanceFromCentre(distanceFromCentre),
                                                        _angle(angle),
                                                        _scale(scale)
{
    _sprite.setTexture(textureHolder.get(_id));
    _sprite.setTextureRect(sf::IntRect(0, 0, 70, 110));
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);
    _sprite.setRotation(-_angle);
    move(_distanceFromCentre - (_distanceFromCentre*0.6)); //Spawn at PlayerShip Gun barrel
}

void Bullet::move(float distance) // ToDo : Sensible default value
{
    auto offset = 0.f;
    if(_distanceFromCentre==0)
    {
        offset = _resolution.x*0.2;
    }
    auto depthScale = ((_distanceFromCentre + offset)/(_resolution.x/2));
    _distanceFromCentre += distance * depthScale;
    auto x_pos = _distanceFromCentre * sin(common::degreeToRad(_angle));
    auto y_pos = _distanceFromCentre * cos(common::degreeToRad(_angle));
    auto scale = 1 + ((_distanceFromCentre - (_resolution.x / 2)) / (_resolution.x / 2));
    _sprite.setPosition(x_pos+(_resolution.x / 2),y_pos+(_resolution.y / 2));
    _sprite.setScale(scale * _scale,scale * _scale);

    // Dimming
    auto dimColor = (scale*200) + 100;
    _sprite.setColor(sf::Color(dimColor,dimColor,dimColor));

    // Orientation
    //ToDo: store old position, find new direction, dot product to orient ship
}

float Bullet::getDistanceFromCentre()
{
    return _distanceFromCentre;
}

sf::Sprite &Bullet::getSprite()
{
    return _sprite;
}