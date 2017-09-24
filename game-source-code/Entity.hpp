/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \file    Entity.hpp
/// \date    14/9/17
/// \brief   Basic entity class for game objects
///
/// Enemies, lasers, missiles, and asteroids will all inherit from this class
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_ENTITY_HPP
#define PROJECT_ENTITY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <cmath>
#include "common.hpp"
#include "ResourceHolder.hpp"

class Entity
{
public:
    Entity();
    Entity(const sf::Vector2i resolution,
           float distanceFromCentre,
           float angle,
           float scale,
           const TextureHolder &textureHolder) : _resolution{resolution},
                                                 _distanceFromCentre{distanceFromCentre},
                                                 _angle{angle},
                                                 _scale{scale}
    {}

    virtual void setMove(float){}
    virtual void setMove(float, float){}
    virtual void reset()=0;
    virtual void update()=0;
    virtual const float getRadius() const=0;
    virtual const float getDistanceFromCentre()const=0;
    virtual const sf::Vector2f getScale()const=0;
    virtual const sf::Vector2f getPosition()const=0;
    virtual const sf::Sprite &getSprite()const=0;
    virtual const int getLives() const=0;
    virtual const void die()=0;
    virtual void move()=0;

protected:
    const sf::Vector2i _resolution;
    sf::Sprite _sprite;
    float _distanceFromCentre;
    float _futureAngleValue;
    float _futureMoveValue;
    float _angle;
    float _scale;
    bool _isMoving;
    int _lives;
    textures::ID _id;
};


#endif //PROJECT_ENTITY_HPP
