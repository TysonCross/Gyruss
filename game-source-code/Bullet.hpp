/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    15/9/17
/// \brief   Projectiles/bullets for PlayerShip and EnemyShip
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_BULLET_HPP
#define PROJECT_BULLET_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <cmath>
#include "common.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"

using sf::Vector2f;
using sf::Vector2i;
using sf::IntRect;
using sf::Sprite;
using sf::Color;

////////////////////////////////////////////////////////////
/// \brief Projectile class, for either Player or Enemy bullets.
///
/// Inherits from the Entity base class.
////////////////////////////////////////////////////////////
class Bullet : public Entity
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor for the Bullet Class. Calls the ABC constructors
    /// for the inheritance hierarchy, Entity, Moveable and Animatable.
    ///
    /// Bullets are spawned by shoot events, and then move at a
    /// fixed speed along radial lines towards or away from the centre of the screen.
    ///
    /// \param resolution The Screen resolution of the game
    /// \param distanceFromCentre The radius from centre at which the
    /// bullet should be created
    /// \param angle The argument (angle) at which the bullet should be
    /// placed upon creation
    /// \param scale The initial size of the bullet object (also influenced
    /// by the sprite texture,
    /// and scaled by distance from the origin in the move() command.
    /// \param type An enum that identifies the Entity type. Defined in common.hpp,
    /// passed to the Animatable base class
    /// \param textureHolder The textureHolder object, passed by const ref.
    /// provides a unique_ptr to an sf::Texture for the sprite data member
    /// \param id The unique ID identifying the texture for the Entity
    ///
    /// \see Entity.hpp
    /// \see common.hpp
    /// \see ResourceHolder.hpp
    /// ////////////////////////////////////////////////////////////
    Bullet(const Vector2i resolution,
           float distanceFromCentre,
           float angle,
           float scale,
           const entity::ID type,
           const TextureHolder &textureHolder,
           const textures::ID id);

    ////////////////////////////////////////////////////////////
    /// \brief Sets up the next frame's position for the object.
    ///
    /// The actual position of the bullet is not altered until the move()
    /// method is called, which performs the actual translation
    ///
    /// \param distance How far the bullet should move for the next frame
    /// (in screen space)
    ////////////////////////////////////////////////////////////
    void        setMove(float distance) override;

    ////////////////////////////////////////////////////////////
    /// \brief Performs the actual move, based on _futureMoveValue.
    ///////////////////////////////////////////////////////////////
    void move() override;

    ////////////////////////////////////////////////////////////
    /// \brief Resets the player ship (intended to be called after
    /// a player death event)
    ///
    /// The bullet position is reset back
    /// to the centre of the screen, on the movement circle.
    /// Invulnerability is turned on, and the invulnerability timer restarted,
    /// The various boolean states are reset to their default values.
    /// Any upgrades are lost, and these planned moves are immediately performed
    ////////////////////////////////////////////////////////////
    void reset() override;

    ////////////////////////////////////////////////////////////
    /// \brief Checks and updates the movement, shooting and calls
    /// the actual movement translation with move()
    ////////////////////////////////////////////////////////////
    void update() override;

    ////////////////////////////////////////////////////////////
    /// \brief Decrements the bullet lives
    ////////////////////////////////////////////////////////////
    void die() override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \return The sf::Sprite object representing the position,
    /// dimensions and texture of the bullet
    ///
    /// \see sf:Sprite
    ////////////////////////////////////////////////////////////
    const Sprite &getSprite() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin (screen space)
    ///
    /// \return A float value of the distance from centre of the screen
    ////////////////////////////////////////////////////////////
    const float getRadius() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin (non-linear distance)
    ///
    /// \return A float value, the depth from the centre in z
    ////////////////////////////////////////////////////////////
    const float getDistanceFromCentre() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the current angle of the bullet,
    /// measured from the origin( mid-point screen space)
    ///
    /// \return A float value, the angle around the screen centre origin
    ////////////////////////////////////////////////////////////
    const float getAngle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the x,y position of the bullet on screen
    ///
    /// \return An sf:Vector2f (two float values) of the {x,y} position of the bullet
    ////////////////////////////////////////////////////////////
    const Vector2f getPosition() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the scale (in width/height) of the bullet object
    ///
    /// \return An sf:Vector2f (two float values) of the {x,y} scale of the bullet
    ////////////////////////////////////////////////////////////
    const Vector2f getScale() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the remaining number of lives of the bullet
    ///
    /// \return An integer value of the remaining bullet lives (usually 0 or 1)
    ////////////////////////////////////////////////////////////
    const int getLives() const override;

private:
    ////////////////////////////////////////////////////////////
    /// \param The active area of the texture (in an animated tile-set,
    /// which will be a sub-rectangle of the total texture.
    ////////////////////////////////////////////////////////////
    IntRect _rectArea;

    ////////////////////////////////////////////////////////////
    /// \param The pixel offset of the _rectArea, moving the image
    /// from frame to frame.
    ////////////////////////////////////////////////////////////
    int _spriteOffset;
};

#endif //PROJECT_BULLET_HPP
