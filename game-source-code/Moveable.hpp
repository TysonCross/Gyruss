/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    7/10/17
/// \brief   Definition of the Moveable class
///
/// Class interface for movement, position and distance from centre, angle
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_MOVEABLE_HPP
#define PROJECT_MOVEABLE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System.hpp>

using sf::Vector2f;

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
    /// \brief Sets the future movement, either by change in angle or change in distance
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
    virtual void setMove(float value){}

    ////////////////////////////////////////////////////////////
    /// \brief Virtual method to set the future movement, by both angle and distance
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
    virtual void setMove(float angle, float distance){}

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

protected:
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
    /// \brief Data member storing the current scale (the same for both x and y)
    ////////////////////////////////////////////////////////////
    float _scale;

    ////////////////////////////////////////////////////////////
    /// \brief Data member storing the boolean state of whether the object is moving or not
    ////////////////////////////////////////////////////////////
    bool _isMoving;
};


#endif //PROJECT_MOVEABLE_HPP
