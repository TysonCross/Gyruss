/////////////////////////////////////////////////////////////////////
/// \brief   Basic entity class for game objects
///
/// PlayerShip, Enemies, Bullets, Shields, and Meteoroids all inherit from this class
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
    /// \brief The Entity class constructor
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
    /// \see common
    /// \see ResourceHolder
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
                                                 _resolution{resolution},
                                                 _lives{0},
                                                 _isAlive{true},
                                                 _isShooting{false} {}

    ////////////////////////////////////////////////////////////
    /// \brief Pure virtual method definition for returning the
    /// remaining number of lives of the entity
    /// \returns An integer value of the number of remaining lives
    /// \see _lives
    ////////////////////////////////////////////////////////////
    virtual const int getLives() const=0;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean state of the entity (alive/dead)
    ///
    /// \return A boolean value of alive(1) or dead(0)
    ////////////////////////////////////////////////////////////
    virtual const bool isAlive() const=0;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the shooting status of the entity
    ///
    /// \return If true, then the enemy is shooting on this frame
    ////////////////////////////////////////////////////////////
    virtual const bool isShooting() const
    {return _isShooting;}

    ////////////////////////////////////////////////////////////
    /// \brief Sets the _isShooting state of the entity
    ////////////////////////////////////////////////////////////
    virtual void setShoot(){};

    ////////////////////////////////////////////////////////////
    /// \brief Resets the object timer, measuring when the entity last shot a bullet
    ////////////////////////////////////////////////////////////
    virtual void resetShootTimer(){};

    ////////////////////////////////////////////////////////////
    /// \brief Returns amount of time since the entity last shot a bullet
    ///
    /// \return A float value (in seconds) of the amount of elapsed time
    ////////////////////////////////////////////////////////////
    virtual const float getShootTimerElapsedTime() const
    { return _timerShoot.getElapsedTime().asSeconds();}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the amount of time that the entity has been alive for.
    ///
    /// \return A float value (in seconds) of the time the enemy object has been alive.
    ////////////////////////////////////////////////////////////
    virtual const float getAliveTimeElapsedTime() const
    {return _timerAlive.getElapsedTime().asSeconds();}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the entity type
    ///
    /// \return An enum value (defined in common.hpp) of the entity type
    /// \see common
    /// \see Entity
    ////////////////////////////////////////////////////////////
    virtual const entity::ID  getType() const=0;

    ////////////////////////////////////////////////////////////
    /// \brief Pure virtual method definition for performing an update on the entity object
    ////////////////////////////////////////////////////////////
    virtual void update()=0;

    ////////////////////////////////////////////////////////////
    /// \brief Pure virtual method definition for resetting the entity to a default state
    ////////////////////////////////////////////////////////////
    virtual void reset()=0;

    ////////////////////////////////////////////////////////////
    /// \brief Pure virtual method definition for decrementing an entity's lives count
    ////////////////////////////////////////////////////////////
    virtual void die()=0;

protected:
    ////////////////////////////////////////////////////////////
    /// \brief Resets the shooting status of the entity
    ///
    /// \return Resets the _isShooting member to false
    ////////////////////////////////////////////////////////////
    virtual void stopShoot(){};

    ////////////////////////////////////////////////////////////
    /// \brief The game resolution in {x,y}
    ////////////////////////////////////////////////////////////
    const Vector2i _resolution;

    ////////////////////////////////////////////////////////////
    /// \brief The number of lives remaining of an entity
    /// \see getLives()
    ////////////////////////////////////////////////////////////
    int _lives;

    ////////////////////////////////////////////////////////////
    /// \param Boolean storing state of playerShip: alive or dead
    ////////////////////////////////////////////////////////////
    bool _isAlive;

    ////////////////////////////////////////////////////////////
    /// \param Stores the state of the entity shooting or not
    ////////////////////////////////////////////////////////////
    bool _isShooting;

    ////////////////////////////////////////////////////////////
    /// \param A timer since last bullet shooting occurred
    /// \see getShootTimerElapsedTime
    ////////////////////////////////////////////////////////////
    Clock _timerShoot;

    ////////////////////////////////////////////////////////////
    /// \param A timer measuring how long the entity has been alive
    /// \see getAliveTimeElapsedTime
    ////////////////////////////////////////////////////////////
    Clock _timerAlive;

};

#endif //PROJECT_ENTITY_HPP
