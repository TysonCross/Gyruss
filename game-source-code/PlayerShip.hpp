/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   Player ship
///
/// Object for the player ship model
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_PLAYERSHIP_HPP
#define PROJECT_PLAYERSHIP_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "common.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"

using sf::Vector2f;
using sf::Vector2i;
using sf::Sprite;
using sf::IntRect;
using sf::Clock;

////////////////////////////////////////////////////////////
/// \brief playerShip Class, inherited from Entity
///
/// A playerShip is the player avatar, a spaceship which rotates
/// around the perimeter of a circle. A playerShip can shoot and move left or right.
/// The ship spawns at the bottom of the movement circle. The ship is moved by a change in angle,
/// and is translated by mod/arg form, with a fixed radius determined
/// as a percentage of the vertical screen resolution.
///
/// \see Entity
////////////////////////////////////////////////////////////
class PlayerShip : public Entity
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Creates a playerShip object
    ///
    /// \param resolution The screen resolution (to determine the radius
    /// the playerShip circles around
    /// \param distanceFromCentre The fixed radius of the circle
    /// that the ship flies around
    /// \param angle The angle in degrees around the circle of movement
    /// \param scale The scale of the playerShip
    /// \param type An enum that identifies the Entity type. Defined in common.hpp,
    /// passed to the Animatable base class
    /// \param textureHolder The resourceMapper object that
    /// contains the path to the texture(s) for the sprite
    ///
    /// \see Entity.hpp
    /// \see common.hpp
    /// \see ResourceHolder.hpp
    ////////////////////////////////////////////////////////////
    PlayerShip(const Vector2i resolution,
               float distanceFromCentre,
               float angle,
               float scale,
               const entity::ID type,
               const TextureHolder &textureHolder);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the future player movement, rotating the
    /// the player ship around a circle by this angle.
    ///
    /// The actual position of the playerShip is not altered until the move()
    /// method is called, which performs the actual translation
    ///
    /// \param angle The delta change in angle (will be added to
    /// the current angle.
    ///
    /// \see move()
    ////////////////////////////////////////////////////////////
    void setMove(float angle) override;

    ////////////////////////////////////////////////////////////
    /// \brief Sets the _isShooting state of the playerShip
    ////////////////////////////////////////////////////////////
    void setShoot();

    ////////////////////////////////////////////////////////////
    /// \brief Moves the player ship around a circle by this angle,
    /// based on the futureAngleValue and futureMoveValue
    ////////////////////////////////////////////////////////////
    void move() override;

    ////////////////////////////////////////////////////////////
    /// \brief Resets the player ship (intended to be called after
    /// a player death event)
    ///
    /// The playerShip position is reset back
    /// to the bottom of the screen, on the movement circle.
    /// Invulnerability is turned on, and the invulnerability timer restarted,
    /// The various boolean states are reset to their default values.
    /// Any upgrades are lost, and these planned moves are immediately performed
    ////////////////////////////////////////////////////////////
    void reset() override;

    ////////////////////////////////////////////////////////////
    /// \brief Checks and updates the movement, shooting and calls
    /// the actual movement translation
    ///
    /// \see move()
    ////////////////////////////////////////////////////////////
    void update() override;

    ////////////////////////////////////////////////////////////
    /// \brief Sets the boolean state of the playerShip upgrade status to true.
    ///
    /// If the player performs certain actions, an upgraded state will
    /// grant a different, more powerful method of shooting.
    ////////////////////////////////////////////////////////////
    void upgrade();

    ////////////////////////////////////////////////////////////
    /// \brief Decrements the player lives
    ////////////////////////////////////////////////////////////
    void die() override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \return The sf::Sprite object representing the entity in the game
    /// (dimensions, position, texture)
    ///
    /// \see sf:Sprite
    ////////////////////////////////////////////////////////////
    const Sprite &getSprite() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin (screen space)
    ///
    /// \return A float value, the distance from the origin (on camera plane)
    ////////////////////////////////////////////////////////////
    const float getRadius() const override; // As below

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin (non-linear distance)
    ///
    /// \return A float value, the depth from the centre in z
    ////////////////////////////////////////////////////////////
    const float getDistanceFromCentre() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the x,y position of the playership on screen
    ///
    /// \return A Vector2f - two (float) values {x,y} of the screen space coordinates of the object
    ////////////////////////////////////////////////////////////
    const Vector2f getPosition() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the scale (in width/height) of the playerShip object
    ///
    /// \return A Vector2f - two (float) values {x,y} of the scale in width and height
    ////////////////////////////////////////////////////////////
    const Vector2f getScale() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the remaining number of lives of the player
    ///
    /// \return The integer number of remaining lives
    ////////////////////////////////////////////////////////////
    const int getLives() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the current angle of the playerShip around the movement circle
    ///
    /// \return A float value, the angle around the perimeter circle
    ////////////////////////////////////////////////////////////
    float getAngle();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the future, intended angle of the playership around the movement circle,
    /// which will be updated after the "update" method has completed.
    ///
    /// \return A float value of the planned angle to move by, when move() is called
    ////////////////////////////////////////////////////////////
    float getFutureAngle();

    ////////////////////////////////////////////////////////////
    /// \brief Boolean state of the playerShip (alive/dead)
    ///
    /// \return A boolean value of alive(1) or dead(0)
    ////////////////////////////////////////////////////////////
    const bool isAlive() const;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean movement state of the playerShip
    ///
    /// \return The boolean value of moving(1) or stationary(0)
    ////////////////////////////////////////////////////////////
    const bool isMoving() const;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean shooting state of the playerShip
    ///
    /// \return The boolean value of shooting(1) or not shooting(0)
    ////////////////////////////////////////////////////////////
    const bool isShooting() const;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean state of the playerShip taking damage from collisions or not
    ///
    /// After respawning, the playerShip is briefly invulnerable, to avoid
    /// immediate "unfair" deaths from collisions.
    ///
    /// \return A boolean value of invulnerable(1) or normal(0)
    ////////////////////////////////////////////////////////////
    const bool isInvulnerable() const;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean state of the playerShip upgrade status
    ///
    /// If the player performs certain actions, an upgraded state will
    /// grant a different, more powerful method of shooting.
    ///
    /// \return A boolean value of upgraded state
    ////////////////////////////////////////////////////////////
    const bool isUpgraded() const;

    ////////////////////////////////////////////////////////////
    /// \brief Makes the playerShip unaffected by damage
    ///
    /// Developer (debug) mode only. Used with hot-keys in non-release mode
    /// for testing.
    ///
    /// \param godMode If true, then the player takes no damage from collisions
    ////////////////////////////////////////////////////////////
    void makeInvulnerable(bool godMode);

private:
    ////////////////////////////////////////////////////////////
    /// \brief resets the _isShooting status to false.
    ////////////////////////////////////////////////////////////
    void endShoot();

    ////////////////////////////////////////////////////////////
    /// \param The animatable texture's active tile area
    ////////////////////////////////////////////////////////////
    IntRect _rectArea;

    ////////////////////////////////////////////////////////////
    /// \param The pixel offset of the _rectArea, moving the image from frame to frame
    ////////////////////////////////////////////////////////////
    int _spriteOffset;

    ////////////////////////////////////////////////////////////
    /// \param The future angle to move by
    ////////////////////////////////////////////////////////////
    float _futureAngleValue;

    ////////////////////////////////////////////////////////////
    /// \param Boolean storing state of playerShip: moving or stationary
    ////////////////////////////////////////////////////////////
    bool _isMoving;

    ////////////////////////////////////////////////////////////
    /// \param Boolean storing state of playerShip: moving or stationary
    ////////////////////////////////////////////////////////////
    bool _isShooting;

    ////////////////////////////////////////////////////////////
    /// \param Boolean storing state of playerShip: invulnerable or normal
    ////////////////////////////////////////////////////////////
    bool _isInvulnerable;

    ////////////////////////////////////////////////////////////
    /// \param Boolean storing state of playerShip: normal shoot or upgraded double shoot
    ////////////////////////////////////////////////////////////
    bool _isUpgraded;

    ////////////////////////////////////////////////////////////
    /// \param Boolean storing state of playerShip: alive or dead
    ////////////////////////////////////////////////////////////
    bool _isAlive;

    ////////////////////////////////////////////////////////////
    /// \param Timer for invulnerability
    ////////////////////////////////////////////////////////////
    Clock _invulnerabilityTimer;

    ////////////////////////////////////////////////////////////
    /// \param How long the player is invulnerable for after respawning (in seconds)
    ////////////////////////////////////////////////////////////
    float _invulnerabilityTimeAmount;
};

#endif //PROJECT_PLAYERSHIP_HPP
