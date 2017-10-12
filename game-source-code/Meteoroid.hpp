/////////////////////////////////////////////////////////////////////
/// \brief   Meteroid Entity (cannot be destroyed by bullets)
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_METEROID_HPP
#define PROJECT_METEROID_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
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
/// \brief Meteoroid class.
///
/// Inherits from the Entity base class.
////////////////////////////////////////////////////////////
class Meteoroid : public Entity
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor for the Meteoroid Class. Calls the ABC constructors
    /// for the inheritance hierarchy, Entity, Moveable and Animatable.
    ///
    /// Meteoroid are spawned by a separate timer (with some random threshold),
    /// and then move at a fixed speed along radial lines away from the centre
    /// of the screen. They cannot be destroyed or stopped, and destroy the playerShip
    /// in a collision
    ///
    /// \param resolution The Screen resolution of the game
    /// \param distanceFromCentre The radius from centre at which the
    /// meteoroid should be created
    /// \param angle The argument (angle) at which the meteoroid should be
    /// placed upon creation
    /// \param scale The initial size of the meteoroid object (also influenced
    /// by the sprite texture,
    /// and scaled by distance from the origin in the move() command.
    /// \param type An enum that identifies the Entity type. Defined in common.hpp,
    /// passed to the Animatable base class
    /// \param textureHolder The textureHolder object, passed by const ref.
    /// provides a unique_ptr to an sf::Texture for the sprite data member
    /// \param id The unique ID identifying the texture for the entity
    ///
    /// \see Entity.hpp
    /// \see common.hpp
    /// \see ResourceHolder.hpp
    /// ////////////////////////////////////////////////////////////
    Meteoroid(const Vector2i resolution,
              float distanceFromCentre,
              float angle,
              float scale,
              const entity::ID type,
              const TextureHolder &textureHolder,
              const textures::ID id);

    ////////////////////////////////////////////////////////////
    /// \brief Sets up the next frame's position for the object.
    ///
    /// The actual position of the meteoroid is not altered until the move()
    /// method is called, which performs the actual translation
    ///
    /// \param distance How far the meteoroid should move for the next frame
    /// (in screen space)
    ////////////////////////////////////////////////////////////
    void setMove(float distance) override;

    ////////////////////////////////////////////////////////////
    /// \brief Sets the future movement, by both angle and distance
    ///
    ///
    /// \param angle The delta change in angle (will be added to
    /// the current angle
    /// \param distance The delta change in distance (will be added to
    /// the current distance
    ///
    /// \see move
    ////////////////////////////////////////////////////////////
    void setMove(float angle, float distance) override {};

    ////////////////////////////////////////////////////////////
    /// \brief Performs the actual move, based on _futureMoveValue.
    ////////////////////////////////////////////////////////////
    void move() override;

    ////////////////////////////////////////////////////////////
    /// \brief Resets the meteoroid
    ////////////////////////////////////////////////////////////
    void reset() override;

    ////////////////////////////////////////////////////////////
    /// \brief Checks and updates the movement, shooting and calls
    /// the actual movement translation with move()
    ////////////////////////////////////////////////////////////
    void update() override;

    ////////////////////////////////////////////////////////////
    /// \brief Decrements the metroid's lives
    ////////////////////////////////////////////////////////////
    void die() override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \return The sf::Sprite object representing the position,
    /// dimensions and texture of the meteroid
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
    /// \brief Returns the current angle of the meteoroid
    ///
    /// \return A float value, the angle for mod/arg position
    ////////////////////////////////////////////////////////////
    const float getAngle() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the x,y position of the meteoroid on screen
    ///
    /// \return An sf:Vector2f (two float values) of the {x,y} position of the meteoroid
    ////////////////////////////////////////////////////////////
    const Vector2f getPosition() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the scale (in width/height) of the meteoroid object
    ///
    /// \return An sf:Vector2f (two float values) of the {x,y} scale of the meteoroid
    ////////////////////////////////////////////////////////////
    const Vector2f getScale() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the remaining number of lives of the meteoroid
    ///
    /// \return An integer value of the remaining meteoroid lives (usually 0 or 1)
    ////////////////////////////////////////////////////////////
    const int getLives() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean state of the entity (alive/dead)
    ///
    /// \return A boolean value of alive(1) or dead(0)
    ////////////////////////////////////////////////////////////
    const bool isAlive() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the entity type
    ///
    /// \return An enum value (defined in common.hpp) of the entity type
    /// \see common
    /// \see Entity
    ////////////////////////////////////////////////////////////
    virtual const entity::ID getType() const override;

private:
    ////////////////////////////////////////////////////////////
    /// \param Meteoroids spin as they move outwards.
    /// This data member stores the current rotation
    ////////////////////////////////////////////////////////////
    int _rotationOffset;
};

#endif //PROJECT_METEROID_HPP
