/////////////////////////////////////////////////////////////////////
/// \brief   Enemy ship types
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_ENEMYSHIP_HPP
#define PROJECT_ENEMYSHIP_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include "common.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"

using sf::Vector2f;
using sf::Vector2i;
using sf::Color;
using sf::Clock;
using sf::Sprite;

////////////////////////////////////////////////////////////
/// \brief An enum list of possible movement states for enemy movement
////////////////////////////////////////////////////////////
enum MovementState
{
    SpiralOut = 0,
    SpiralIn,
    Wandering,
    CircleOffsetLeft,
    CircleOffsetRight,
    SmallCircling,
};

////////////////////////////////////////////////////////////
/// \brief An enum list of possible movement directions for enemy movement
////////////////////////////////////////////////////////////
enum MovementDirection
{
    Clockwise = 0,
    CounterClockwise
};

////////////////////////////////////////////////////////////
/// \brief Abstract Base Class for enemy game objects
///
/// Inherits from Entity
///
/// \see Entity
////////////////////////////////////////////////////////////
class Enemy : public Entity
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor for an enemy object
    ///
    /// \param resolution The screen resolution (to determine the radius
    /// the playerShip circles around
    /// \param distanceFromCentre The fixed radius of the circle
    /// that the ship flies around
    /// \param angle The angle in degrees around the circle of movement
    /// \param scale The scale of the sprite
    /// \param type An enum that identifies the Enemy type. Defined in common.hpp,
    /// passed to the Animatable base class
    /// \param textureHolder The textureHolder object, passed by const ref.
    /// provides a unique_ptr to an sf::Texture for the sprite data member
    /// \param id The unique ID identifying the texture for the Enemy variant
    /// \param movementState Enum identifying the pattern of movement for the Enemy
    /// \param movementDirection Enum for the movement direction (clockwise or counterclockwise)
    ////////////////////////////////////////////////////////////
    Enemy(const sf::Vector2i &resolution,
          float distanceFromCentre,
          float angle,
          float scale,
          const entity::ID type,
          const TextureHolder &textureHolder,
          const textures::ID id,
          MovementState movementState,
          MovementDirection movementDirection);

    ////////////////////////////////////////////////////////////
    /// \brief Sets up the next frame's position for the object.
    ///
    /// The actual position of the Enemy is not altered until the move()
    /// method is called, which performs the actual translation
    ///
    /// \param angle The angle the enemy should move for the next frame (0-360,
    /// with 0 being the positive horizontal x axis, with the centre of the screen as the origin)
    /// \param distance How far the enemy should move for the next frame (in screen space)
    ////////////////////////////////////////////////////////////
    void setMove(float angle, float distance) override;

    ////////////////////////////////////////////////////////////
    /// \brief Sets the future movement, either by change in angle or change in distance
    ///
    /// \param value The delta change in angle or distance (will be added to
    /// the current angle/distance
    ///
    /// \see move
    ////////////////////////////////////////////////////////////
    void setMove(float value) override {};

    ////////////////////////////////////////////////////////////
    /// \brief Sets up the next frame's position for the object, with a different screen origin
    ///
    /// The actual position of the Enemy is not altered until the move()
    /// method is called, which performs the actual translation
    ///
    /// \param angle The angle the enemy should move for the next frame (0-360,
    /// with 0 being the positive horizontal x axis, with the specified centre argument as the origin)
    /// \param distance How far the enemy should move for the next frame (in screen space)
    /// \param centre The coordinate {x,y} to be considered as the origin for this move
    ////////////////////////////////////////////////////////////
    void setMove(float angle, float distance, sf::Vector2f centre);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the movement state of the enemy
    ///
    /// \param movementState The enum value of the movement state.
    ///
    /// \see MovementDirection
    ////////////////////////////////////////////////////////////
    void setMovementState(MovementState movementState);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the scale of the Enemy screen object
    ///
    /// \param scaleX The X scale of the enemy sprite
    /// \param scaleY The Y scale of the emeny sprite
    ////////////////////////////////////////////////////////////
    void setScale(float scaleX, float scaleY);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the orientation of the Enemy screen object
    ///
    /// The previous and future positions are converted to vectors at the origin,
    /// and the final position is then subtracted from the initial position,
    /// to determine the new pointing vector. Then the sprite of the enemy is
    /// rotated to match this direction
    ////////////////////////////////////////////////////////////
    void setOrientation();

    ////////////////////////////////////////////////////////////
    /// \brief Sets the _isShooting state of the enemy
    ////////////////////////////////////////////////////////////
    void setShoot();

    ////////////////////////////////////////////////////////////
    /// \brief Moves the enemy ship around screen space (performs the planned move)
    ////////////////////////////////////////////////////////////
    void move() override;

    ////////////////////////////////////////////////////////////
    /// \brief Resets the enemy (after an enemy is killed, or leaves the outer circle)
    ///
    /// The enemy position is reset back to the centre of the screen.
    ////////////////////////////////////////////////////////////
    void reset() override;

    ////////////////////////////////////////////////////////////
    /// \brief Checks and updates the movement, shooting and calls
    /// the actual movement translation
    ///
    /// \see move
    ////////////////////////////////////////////////////////////
    void update() override;

    ////////////////////////////////////////////////////////////
    /// \brief Decrements the enemy's lives
    ////////////////////////////////////////////////////////////
    void die() override;

    ////////////////////////////////////////////////////////////
    /// \brief Resets the object timer, measuring when the enemy last shot a bullet
    ////////////////////////////////////////////////////////////
    void resetShootTimer();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \return The sf::Sprite object representing the entity in the game
    /// (dimensions, position, texture)
    ///
    /// \see [SFML/Sprite](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Sprite.php)
    ////////////////////////////////////////////////////////////
    const Sprite &getSprite() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin (screen space)
    ///
    /// \return A float value, the distance from the origin (on camera plane)
    ////////////////////////////////////////////////////////////
    const float getRadius() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin (non-linear distance)
    ///
    /// \return A float value, the depth from the centre in z
    ////////////////////////////////////////////////////////////
    const float getDistanceFromCentre() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the current angle of the enemy from the origin(screen space)
    ///
    /// \return A float value, the angle around the screen centre origin
    ////////////////////////////////////////////////////////////
    const float getAngle() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the current rotation of the enemy sprite
    ///
    /// \return The angle of rotation of the sprite
    ////////////////////////////////////////////////////////////
    const float getOrientationAngle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the current rotation of the enemy sprite
    ///
    /// \return The angle of rotation of the sprite
    ////////////////////////////////////////////////////////////
    const Vector2f getPosition() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the width/height scale of the enemy on screen
    ///
    /// \return An sf:Vector2f (two float values) of the {x,y} scale of the enemy
    ////////////////////////////////////////////////////////////
    const Vector2f getScale() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the remaining number of lives of the enemy
    ///
    /// \return An integer value of the remaining enemy lives (usually 0 or 1)
    ////////////////////////////////////////////////////////////
    const int getLives() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the entity type of the enemy
    ///
    /// \return An enum value (defined in common.hpp) of the entity type
    /// \see common
    /// \see Entity
    ////////////////////////////////////////////////////////////
    const entity::ID getType() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean state of the entity (alive/dead)
    ///
    /// \return A boolean value of alive(1) or dead(0)
    ////////////////////////////////////////////////////////////
    const bool isAlive() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the x/y position of the _centre member of the enemy on screen
    ///
    /// \return An sf:Vector2f (two float values) of the {x,y} position
    /// considered the current origin of the enemy
    ////////////////////////////////////////////////////////////
    const Vector2f getCentre() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns current Movement state for the enemy
    ///
    /// \return An enum value of the current movement state
    ////////////////////////////////////////////////////////////
    const MovementState getMovementState() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the currently set movement direction for the enemy
    ///
    /// \return An enum value of the current movement direction,
    /// clockwise or counterclockwise
    ////////////////////////////////////////////////////////////
    const int getMovementDirectionSign() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns amount of time since the enemy last shot a bullet
    ///
    /// \return A float value (in seconds) of the amount of elapsed time
    ////////////////////////////////////////////////////////////
    const float getShootTimerElapsedTime() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the amount of time that the enemy has been alive for.
    ///
    /// \return A float value (in seconds) of the time the enemy object has been alive.
    ////////////////////////////////////////////////////////////
    const float getAliveTimeElapsedTime() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the shooting status of the enemy
    ///
    /// \return If true, then the enemy is shooting on this frame
    ////////////////////////////////////////////////////////////
    const bool isShooting() const;


private:
    ////////////////////////////////////////////////////////////
    /// \brief Resets the shooting status of the enemy
    ///
    /// \return Resets the _isShooting member to false
    ////////////////////////////////////////////////////////////
    void stopShoot();

    ////////////////////////////////////////////////////////////
    /// \param Stores the angle of rotation of the sprite object
    ////////////////////////////////////////////////////////////
    float _angleOrientation;

    ////////////////////////////////////////////////////////////
    /// \param Stores the state of the enemy shooting or not
    ////////////////////////////////////////////////////////////
    bool _isShooting;

    ////////////////////////////////////////////////////////////
    /// \param The last position of the enemy on screen
    ////////////////////////////////////////////////////////////
    Vector2f _prevPosition;

    ////////////////////////////////////////////////////////////
    /// \param The (next frame) future position of the enemy of screen
    ////////////////////////////////////////////////////////////
    Vector2f _newPosition;

    ////////////////////////////////////////////////////////////
    /// \param  The calulated new pointing position, (final - initial)
    ////////////////////////////////////////////////////////////
    Vector2f _pointingPosition;

    ////////////////////////////////////////////////////////////
    /// \param The origin for the object's move commands
    /// (default is centre of screen, {resolution.x/2,resolution.y/2}
    ////////////////////////////////////////////////////////////
    Vector2f _centre;

    ////////////////////////////////////////////////////////////
    /// \param A timer since last bullet shooting occurred
    /// \see getShootTimerElapsedTime
    ////////////////////////////////////////////////////////////
    Clock _timerShoot;

    ////////////////////////////////////////////////////////////
    /// \param A timer measuring how long the enemy has been alive
    /// \see getAliveTimeElapsedTime
    ////////////////////////////////////////////////////////////
    Clock _timerAlive;

    ////////////////////////////////////////////////////////////
    /// \param Stores the movement state of the enemy
    /// \see getMovementState
    /// \see setMovementState
    ////////////////////////////////////////////////////////////
    MovementState _movementState;

    ////////////////////////////////////////////////////////////
    /// \param Stores the movement direction (clockwise or counterclockwise)
    /// \see getMovementDirectionSign
    /// \see setMovementDirectionSign
    ////////////////////////////////////////////////////////////
    MovementDirection _movementDirection;
};

#endif //PROJECT_ENEMYSHIP_HPP