/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    14/9/17
/// \brief   Basic entity class for game objects
///
/// PlayerShip, Enemies, Bullets, Shields, and Meteoroids all inherit from this class
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_ENTITY_HPP
#define PROJECT_ENTITY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include "common.hpp"
#include "Moveable.hpp"
#include "Animatable.hpp"

class Entity : public Moveable, public Animatable
{
public:
    Entity(const sf::Vector2i resolution,
           float distanceFromCentre,
           float angle,
           float scale,
           const entity::ID type,
           const TextureHolder &textureHolder) : Moveable{distanceFromCentre,
                                                          angle,
                                                          scale},
                                                 Animatable{textureHolder,
                                                            type},
                                                 _resolution{resolution} {}

    virtual const int getLives() const=0;
    virtual void reset()=0;
    virtual void update()=0;
    virtual void die()=0;
    virtual void move()=0;

protected:
    const sf::Vector2i _resolution;
    int _lives;

};


#endif //PROJECT_ENTITY_HPP
