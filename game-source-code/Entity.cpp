#include "Entity.hpp"/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    Entity.cpp
/// \authors Tyson Cross and Chris Maree
/// \date    14/9/17
/// \brief   Description of file in project Project
///
/// Detailed description of file
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Entity.hpp"

Entity::Entity(const ResourceMapper &resourceMapper,
               common::Resolution resolution,
               float distanceFromCentre,
               float angle,
               float scale)
{

}

void Entity::move(float angle, float distance)
{

}


sf::Sprite &Entity::getSprite()
{
    return _sprite;
}



//sf::Sprite _sprite;
//sf::Texture _texture;
//common::Resolution _resolution
//float _distanceFromCentre;
//float _angle;
//float _scale;
