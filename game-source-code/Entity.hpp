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
    Entity(const TextureHolder &textureHolder,
           common::Resolution resolution,
           float distanceFromCentre,
           float angle,
           float scale);

    ////////////////////////////////////////////////////////////
    /// \brief Moves the Entity around a circle or spiral
    ///
    /// \param angle The change in angle, with the origin at the centre
    /// of the screen
    /// \param distance How far along a ray, originating at the centre
    /// of the screen to move the entity.
    ////////////////////////////////////////////////////////////
    void move(float angle, float distance);

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \see sf:Sprite
    ////////////////////////////////////////////////////////////
    sf::Sprite &getSprite();

protected:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Sprite _sprite;
    sf::Texture _texture;
    common::Resolution _resolution;
    float _distanceFromCentre;
    float _angle;
    float _scale;
};



#endif //PROJECT_ENTITY_HPP
