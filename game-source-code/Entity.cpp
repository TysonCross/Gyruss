#include "Entity.hpp"/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    Entity.cpp
/// \authors Tyson Cross and Chris Maree
/// \date    14/9/17
/// \brief   Impmentation of basic entity class for game objects
///
/// Enemies, lasers, missiles, and asteroids will all inherit from this class
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Entity.hpp"

Entity::Entity(const ResourceHolder &resourceMapper,
               common::Resolution resolution,
               float distanceFromCentre = 0,
               float angle = 0,
               float scale = 1) : _resolution(resolution) {}

void Entity::move(float angle,
                  float distance)
{
    _angle += angle;
    _angle = common::angleFilter(_angle);
    _distanceFromCentre += distance;
    _sprite.setPosition(_distanceFromCentre * sin(common::degreeToRad(_angle)) + _resolution.x / 2,
                        _distanceFromCentre * cos(common::degreeToRad(_angle)) + _resolution.y / 2);
    _sprite.setRotation(-1 * _angle);
}

sf::Sprite &Entity::getSprite()
{
    return _sprite;
}
