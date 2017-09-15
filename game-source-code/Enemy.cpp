/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    14/9/17
/// \brief   Implementation of Enemy ship types
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Enemy.hpp"
#include <iostream>


Enemy::Enemy(const ResourceMapper &resourceMapper,
             common::Resolution resolution,
             float distanceFromCentre = 0,
             float angle = 0,
             float scale = 1,
             Type type = GreyShip) :  _resolution(resolution),
                                      _type(type),
                                      _distanceFromCentre(distanceFromCentre),
                                      _angle(angle),
                                      _scale(scale)
{
    _texture.loadFromFile(resourceMapper.getResourceVector("EnemyShip").at(type));
    _texture.setSmooth(1);
    //Need error check/exception
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);

    move(0,0); //Initialised position at centre of screen
}

void Enemy::move(float angle, float distance)
{
    _angle += angle;
    _angle = common::angleFilter(_angle);
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
    auto dimColor = (scale*55) + 200;
    _sprite.setColor(sf::Color(dimColor,dimColor,dimColor));
    _sprite.setRotation(-1*_angle); // ToDo: store old position, find new direction, dot product to orient ship
//
}

sf::Sprite &Enemy::getSprite()
{
    return _sprite;
}