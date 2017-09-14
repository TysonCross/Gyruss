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
    //Need error check
    _sprite.setTexture(_texture);
    _sprite.setScale(_scale, _scale);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

    move(0,0); //Initialised position at centre of screen
}

void Enemy::move(float angle, float distance)
{
    _angle += angle;
    _angle = common::eulerFilter(_angle);
    _distanceFromCentre += distance;
    auto x_pos = _distanceFromCentre * cos(common::degreeToRad(_angle));
    auto y_pos = _distanceFromCentre * sin(common::degreeToRad(_angle));
    _sprite.setPosition(x_pos  + _resolution.x / 2, y_pos + _resolution.y / 2);
    _sprite.setRotation( _angle);
    auto ratio =  _sprite.getGlobalBounds().width/_sprite.getGlobalBounds().height;
    auto x_scale = ((_resolution.x/2)-x_pos)/(_resolution.x/2)*_scale;
    auto y_scale = ((_resolution.y/2)-y_pos)/(_resolution.y/2)*_scale;
    _sprite.setScale(x_scale,x_scale*ratio);
    std::cout << x_scale << "," << y_scale << std::endl; }

sf::Sprite &Enemy::getSprite()
{
    return _sprite;
}