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

class PlayerShip : public Entity
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class
    ///
    /// \param textureHolder The resourceMapper object that
    /// contains the path to the texture(s) for the sprite
    /// \param The screen resolution (to determine the radius
    /// the playerShip circles around
    /// \param distanceFromCentre The fixed radius of the circle
    /// that the ship flies around
    /// \param angle The angle in degrees around the circle of movement
    /// \param scale The scale of the sprite
    ///
    ////////////////////////////////////////////////////////////
    PlayerShip(const sf::Vector2i resolution,
               float distanceFromCentre,
               float angle,
               float scale,
               const entity::ID type,
               const TextureHolder &textureHolder);

    void setMove(float angle) override;

    ////////////////////////////////////////////////////////////
    /// \brief Moves the player ship around a circle by this angle
    ////////////////////////////////////////////////////////////
    void move() override;

    void reset() override;

    void update() override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin
    ////////////////////////////////////////////////////////////
    const float getRadius() const override; // As below

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin
    ////////////////////////////////////////////////////////////
    const float getDistanceFromCentre() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \see sf:Sprite
    ////////////////////////////////////////////////////////////
    const sf::Sprite &getSprite() const override;

    const sf::Vector2f getPosition() const override;

    const sf::Vector2f getScale() const override;

    const int getLives() const override;

    const void die() override;

    const bool isMoving() const;

    const bool isShooting() const;

    const bool isInvulnerable() const;

    void setShoot();


    ////////////////////////////////////////////////////////////
    /// \brief Returns the angle
    ////////////////////////////////////////////////////////////
    float getAngle();

    float getFutureAngle();

private:

    ////////////////////////////////////////////////////////////
    /// \brief Shooting ma lazers
    ///
    /// Spawns a projectile
    ///
    ////////////////////////////////////////////////////////////
    void shoot();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::SoundBuffer _buffer;
    sf::Sound _soundMove;
    sf::IntRect _rectArea;
    int _spriteOffset;
    float _futureAngleValue;
    bool _isMoving;
    bool _isShooting;
    bool _isInvulnerable;
    sf::Clock _invulnerabilityTimer;
    float _invulnerabilityTimeAmount;
};

#endif //PROJECT_PLAYERSHIP_HPP
