/////////////////////////////////////////////////////////////////////
/// \brief   Definition of the Moveable class
///
/// Class interface for movement, position and distance from centre, angle
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_MOVEABLE_HPP
#define PROJECT_MOVEABLE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System.hpp>

using sf::Vector2f;
using sf::Clock;

////////////////////////////////////////////////////////////
/// \brief An enum list of possible movement states for entity movement
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
/// \brief An enum list of possible movement directions for entity movement
////////////////////////////////////////////////////////////
enum MovementDirection
{
    Clockwise = 0,
    CounterClockwise
};

////////////////////////////////////////////////////////////
/// \brief Moveable Class
///
/// An abstract base class for game objects that can move or be transformed spatially
///
/// \see Animatable
/// \see PlayerShip
/// \see Enemy
/// \see Meteoroid
/// \see Bullet
/// \see Explosion
/// \see Shield
////////////////////////////////////////////////////////////
class Moveable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief The Moveable class constructor
    ///
    /// \param distanceFromCentre The radius from centre of an entity
    /// \param angle The angle in degrees from positive x-axis (screen centre as origin)
    /// \param scale The scale of the entity
    ////////////////////////////////////////////////////////////
    Moveable(float distanceFromCentre,
             float angle,
             float scale) : _distanceFromCentre{distanceFromCentre},
                            _angle{angle},
                            _scale{scale} {}

    ////////////////////////////////////////////////////////////
    /// \brief Pure Virtual method to set the future movement, either by change in angle or change in distance
    ///
    /// Some entities only need a change in angle, or distance, not both.
    /// The actual position of the entity is not altered until the move()
    /// method is called, which performs the actual translation
    ///
    /// \param value The delta change in angle or distance (will be added to
    /// the current angle/distance
    ///
    /// \see move
    ////////////////////////////////////////////////////////////
    virtual void setMove(float value)=0;

    ////////////////////////////////////////////////////////////
    /// \brief Pure Virtual method to set the future movement, by both angle and distance
    ///
    /// Some entities only need a change in angle and distance to move.
    /// The actual position of the entity is not altered until the move()
    /// method is called, which performs the actual translation
    ///
    /// \param angle The delta change in angle (will be added to
    /// the current angle
    /// \param distance The delta change in distance (will be added to
    /// the current distance
    ///
    /// \see move
    ////////////////////////////////////////////////////////////
    virtual void setMove(float angle, float distance)=0;

    ////////////////////////////////////////////////////////////
    /// \brief Virtual method to set up the next frame's position for the object, with a different screen origin
    ///
    /// The actual position of the entity is not altered until the move()
    /// method is called, which performs the actual translation
    ///
    /// \param angle The angle the entity should move for the next frame (0-360,
    /// with 0 being the positive horizontal x axis, with the specified centre argument as the origin)
    /// \param distance How far the entity should move for the next frame (in screen space)
    /// \param centre The coordinate {x,y} to be considered as the origin for this move
    ////////////////////////////////////////////////////////////
    virtual void setMove(float angle, float distance, Vector2f centre) {}

    ////////////////////////////////////////////////////////////
    /// \brief Sets the movement state of the entity
    ///
    /// \param movementState The enum value of the movement state.
    ///
    /// \see MovementDirection
    ////////////////////////////////////////////////////////////
    virtual void setMovementState(MovementState movementState) {}

    ////////////////////////////////////////////////////////////
    /// \brief Pure virtual method definition for performing a move
    ////////////////////////////////////////////////////////////
    virtual void move()=0;

    ////////////////////////////////////////////////////////////
    /// \brief Returns current Movement state for the enemy
    ///
    /// \return An enum value of the current movement state
    ////////////////////////////////////////////////////////////
    virtual const MovementState getMovementState() const
    {return _movementState;}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the x/y position of the _centre member of the entity on screen
    ///
    /// \return An sf:Vector2f (two float values) of the {x,y} position
    /// considered the current origin of the entity
    ////////////////////////////////////////////////////////////
    virtual const Vector2f getCentre() const
    {return _centre;}

    ////////////////////////////////////////////////////////////
    /// \brief Virtual method to return the distance from origin (screen space)
    ///
    /// \return A float value, the distance from the origin (on camera plane)
    ////////////////////////////////////////////////////////////
    virtual const float getRadius() const=0;

    ////////////////////////////////////////////////////////////
    /// \brief Virtual method to return the distance from origin (non-linear distance)
    ///
    /// \return A float value, the depth from the centre in z
    ////////////////////////////////////////////////////////////
    virtual const float getDistanceFromCentre()const=0;

    ////////////////////////////////////////////////////////////
    /// \brief Virtual method to return the scale (in width/height) of the object
    ///
    /// \return A Vector2f - two (float) values {x,y} of the scale in width and height
    ////////////////////////////////////////////////////////////
    virtual const Vector2f getScale()const=0;

    ////////////////////////////////////////////////////////////
    /// \brief Virtual method to return the x,y position of the object on screen
    ///
    /// \return A Vector2f - two (float) values {x,y} of the screen space coordinates of the object
    ////////////////////////////////////////////////////////////
    virtual const Vector2f getPosition()const=0;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the current angle of the playerShip around the movement circle
    ///
    /// \return A float value, the angle around the perimeter circle
    ////////////////////////////////////////////////////////////
    virtual const float getAngle() const=0;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the currently set movement direction for the entity
    ///
    /// \return An enum value of the current movement direction,
    /// clockwise or counterclockwise
    ////////////////////////////////////////////////////////////
    virtual const int getMovementDirectionSign() const
    {     // Swaps the direction of the angle increase
        switch (_movementDirection)
        {
            case (MovementDirection::CounterClockwise) :
                return -1;
            case (MovementDirection::Clockwise) :
                return 1;
        }
        return 1;
    }

protected:
    ////////////////////////////////////////////////////////////
    /// \param The origin for the object's move commands
    /// (default is centre of screen, {resolution.x/2,resolution.y/2}
    ////////////////////////////////////////////////////////////
    Vector2f _centre;

    ////////////////////////////////////////////////////////////
    /// \brief Data member storing the distance from origin (centre of screen)
    /// \see getDistanceFromCentre
    ////////////////////////////////////////////////////////////
    float _distanceFromCentre;

    ////////////////////////////////////////////////////////////
    /// \brief Data member storing the angle change on the next frame
    ////////////////////////////////////////////////////////////
    float _futureAngleValue;

    ////////////////////////////////////////////////////////////
    /// \brief Data member storing the distance change on the next frame
    ////////////////////////////////////////////////////////////
    float _futureMoveValue;

    ////////////////////////////////////////////////////////////
    /// \brief Data member storing the current angle
    ////////////////////////////////////////////////////////////
    float _angle;

    ////////////////////////////////////////////////////////////
    /// \param The last position of the entity on screen
    ////////////////////////////////////////////////////////////
    Vector2f _prevPosition;

    ////////////////////////////////////////////////////////////
    /// \param The (next frame) future position of the entity of screen
    ////////////////////////////////////////////////////////////
    Vector2f _newPosition;

    ////////////////////////////////////////////////////////////
    /// \param  The calculated new pointing position, (final - initial)
    ////////////////////////////////////////////////////////////
    Vector2f _pointingPosition;

    ////////////////////////////////////////////////////////////
    /// \brief Data member storing the current scale (the same for both x and y)
    ////////////////////////////////////////////////////////////
    float _scale;

    ////////////////////////////////////////////////////////////
    /// \brief Data member storing the boolean state of whether the object is moving or not
    ////////////////////////////////////////////////////////////
    bool _isMoving;

    ////////////////////////////////////////////////////////////
    /// \param Stores the movement state of the entity
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


#endif //PROJECT_MOVEABLE_HPP
