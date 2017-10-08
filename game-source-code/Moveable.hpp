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

class Moveable
{
public:
    Moveable(float distanceFromCentre,
             float angle,
             float scale) : _distanceFromCentre{distanceFromCentre},
                            _angle{angle},
                            _scale{scale} {}

    virtual void setMove(float){} // Some entities only need a change in angle, or distance)
    virtual void setMove(float, float){} // Other entities require change in position, change in radius and angle)
    virtual const float getRadius() const=0;
    virtual const float getDistanceFromCentre()const=0;
    virtual const Vector2f getScale()const=0;
    virtual const Vector2f getPosition()const=0;

protected:
    float _distanceFromCentre;
    float _futureAngleValue;
    float _futureMoveValue;
    float _angle;
    float _scale;
    bool _isMoving;
};


#endif //PROJECT_MOVEABLE_HPP
