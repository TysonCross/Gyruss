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

class EntityPlayerShip : public Entity
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
    EntityPlayerShip(const sf::Vector2i resolution,
               float distanceFromCentre,
               float angle,
               float scale,
               const TextureHolder &textureHolder,
               const SoundHolder &soundHolder);

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
    const float getRadius() override; // As below

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin
    ////////////////////////////////////////////////////////////
    const float getDistanceFromCentre() override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \see sf:Sprite
    ////////////////////////////////////////////////////////////
    sf::Sprite &getSprite() override;

    const sf::Vector2f getPosition() override;

    const sf::Vector2f getScale() override;

    const void die() override;

    int getLives() override;

    void setShoot();
    bool isShooting();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the angle
    ////////////////////////////////////////////////////////////
    float getAngle();

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
    sf::Sound _soundSpawn;
    sf::Sound _soundShoot;
    sf::Sound _soundMove;
    sf::Sound _soundDeath;
    sf::IntRect _rectArea;
    int _spriteOffset;
    float _futureAngleValue;
    bool _isMoving;
    bool _isShooting;
};

#endif //PROJECT_PLAYERSHIP_HPP
