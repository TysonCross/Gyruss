/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    14/9/17
/// \brief   Implementation of Enemy ship types
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy(const TextureHolder &textureHolder,
             const SoundHolder &soundHolder,
             const common::Resolution resolution,
             float distanceFromCentre = 0,
             float angle = 0,
             float scale = 1,
             textures::ID id = textures::EnemyShipGrey ) :  _resolution(resolution),
                                                            _id(id),
                                                            _distanceFromCentre(distanceFromCentre),
                                                            _angle(angle),
                                                            _scale(scale)
{
    _sprite.setTexture(textureHolder.get(_id));
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);

    _soundShoot.setBuffer(soundHolder.get(sounds::EnemyShoot));

    move(0,0); //Initialised position at centre of screen
}

void Enemy::move(float angle,
                 float distance)
{
    _prevPosition = _sprite.getPosition();
    _prevPosition.x -= _resolution.x/2;
    _prevPosition.y -= _resolution.y/2;

    _angle += angle;
    _angle = common::angleFilter(_angle);
    auto offset = 0.f;
    if(_distanceFromCentre==0)
    {
        offset = _resolution.x*0.3;
    }
    auto depthScale = ((_distanceFromCentre + offset)/(_resolution.x/2));
    _distanceFromCentre += distance * depthScale;
    auto x_pos = _distanceFromCentre * sin(common::degreeToRad(_angle));
    auto y_pos = _distanceFromCentre * cos(common::degreeToRad(_angle));
    auto scale = 1 + ((_distanceFromCentre - (_resolution.x / 2)) / (_resolution.x / 2));

    _sprite.setPosition(x_pos+(_resolution.x / 2),y_pos+(_resolution.y / 2));
    _sprite.setScale(scale * _scale,scale * _scale);
    // Dimming
    auto dimColor = (scale*55) + 200;
    _sprite.setColor(sf::Color(dimColor,dimColor,dimColor));

    // Orientation
    _newPosition = _sprite.getPosition();
    _newPosition.x -= _resolution.x/2;
    _newPosition.y -= _resolution.y/2;
    _pointingPosition = _newPosition - _prevPosition;
    _angleOrientation = angle = atan2(_pointingPosition.x,_pointingPosition.y) - atan2(_prevPosition.x,_prevPosition.y);
    _angleOrientation = -1*common::radToDegree(_angleOrientation) - _angle;
    _sprite.setRotation(_angleOrientation);
}

float Enemy::getDistanceFromCentre()
{
    return _distanceFromCentre;
}

sf::Sprite &Enemy::getSprite()
{
    return _sprite;
}

float Enemy::getAngle()
{
    return _angle;
}

float Enemy::getDirectionAngle()
{
    return _angleOrientation;
}

void Enemy::reset()
{
    _angle = 0;
    _angleOrientation = 0;
    _distanceFromCentre = 0;
    _sprite.setScale(0,0);
    _sprite.setPosition(_resolution.x/2,_resolution.y/2);
}

void Enemy::shoot()
{
    _soundShoot.setPitch((_distanceFromCentre-_resolution.x/2)/(_resolution.x/2)); //((rand()%20+10)/2.0f));
    _soundShoot.play();
}