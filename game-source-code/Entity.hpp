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

using sf::Vector2f;
using sf::Vector2i;
using sf::Sprite;
using sf::IntRect;
using sf::Clock;

////////////////////////////////////////////////////////////
/// \brief Entity Class, inherited from Animatable and Moveable
///
/// An abstract base class for game objects
///
/// \see Moveable
/// \see Animatable
/// \see PlayerShip
/// \see Enemy
/// \see Meteoroid
/// \see Bullet
/// \see Explosion
/// \see Shield
////////////////////////////////////////////////////////////
class Entity : public Moveable, public Animatable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief The Entity class constructor.
    /// Calls the Moveable and Animatable constructors,
    /// and sets the resolution
    ///
    /// \param resolution The screen resolution of the game
    /// \param distanceFromCentre The radius from centre of an entity
    /// \param angle The angle in degrees from positive x-axis (screen centre as origin)
    /// \param scale The scale of the entity
    /// \param type An enum that identifies the entity type. Defined in common.hpp,
    /// passed to the Animatable base class
    /// \param textureHolder The resourceMapper object that
    /// contains the path to the texture(s) for the entity's sprite
    ///
    /// \see Moveable
    /// \see Animatable
    /// \see common.hpp
    /// \see ResourceHolder.hpp
    ////////////////////////////////////////////////////////////
    Entity(const Vector2i resolution,
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


    ////////////////////////////////////////////////////////////
    /// \brief Pure virtual method definition for returning the
    /// remaining number of lives of the entity
    /// \returns An integer value of the number of remaining lives
    /// \see _lives
    ////////////////////////////////////////////////////////////
    virtual const int getLives() const=0;

    ////////////////////////////////////////////////////////////
    /// \brief Pure virtual method definition for resetting the entity to a default state
    ////////////////////////////////////////////////////////////
    virtual void reset()=0;

    ////////////////////////////////////////////////////////////
    /// \brief Pure virtual method definition for performing an update on the entity object
    ////////////////////////////////////////////////////////////
    virtual void update()=0;

    ////////////////////////////////////////////////////////////
    /// \brief Pure virtual method definition for decrementing an entity's lives count
    ////////////////////////////////////////////////////////////
    virtual void die()=0;

    ////////////////////////////////////////////////////////////
    /// \brief Pure virtual method definition for performing a move
    ////////////////////////////////////////////////////////////
    virtual void move()=0;

protected:
    ////////////////////////////////////////////////////////////
    /// \brief The game resolution in {x,y}
    ////////////////////////////////////////////////////////////
    const Vector2i _resolution;

    ////////////////////////////////////////////////////////////
    /// \brief The number of lives remaining of an entity
    /// \see getLives()
    ////////////////////////////////////////////////////////////
    int _lives;

};

#endif //PROJECT_ENTITY_HPP
