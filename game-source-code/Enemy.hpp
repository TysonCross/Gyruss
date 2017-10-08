/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    14/9/17
/// \brief   Enemy ship types
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_ENEMYSHIP_HPP
#define PROJECT_ENEMYSHIP_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <cmath>
#include "common.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"

using sf::Vector2f;
using sf::Vector2i;
using sf::Color;
using sf::Clock;
using sf::Sprite;

enum MovementState
{
    SpiralOut=0,
    SpiralIn,
    Wandering,
    CircleOffsetLeft,
    CircleOffsetRight,
    SmallCircling,
};

enum MovementDirection
{
    Clockwise=0,
    CounterClockwise
};

class Enemy : public Entity
{
public:
    Enemy(const sf::Vector2i &resolution,
          float distanceFromCentre,
          float angle,
          float scale,
          const entity::ID type,
          const TextureHolder &textureHolder,
          const textures::ID id,
          MovementState movementState,
          MovementDirection movementDirection);

    void setMove(float angle, float distance) override;
    void setMove(float angle, float distance, sf::Vector2f centre);
    void setMovementState(MovementState movementState);
    void setScale(float scaleX,float scaleY);
    void setShoot();

    void move() override;
    void reset() override;
    void update() override;
    void die() override;
    void resetShootTimer();

    const Sprite&       getSprite() const override;
    const float         getRadius() const override;
    const float         getDistanceFromCentre() const override;
    const float         getDistanceFromCentreWithOffset() const;
    const float         getAngle() const;
    const float         getAngleWithOffset();
    const float         getOrientationAngle() const;
    const Vector2f      getPosition() const override;
    const Vector2f      getScale() const override;
    const Vector2f      getCentre() const;
    const MovementState getMovementState() const;
    const int           getMovementDirectionSign() const;
    const int           getLives() const override;
    const entity::ID    getType() const;
    const float         getShootTimerElapsedTime() const;
    const float         getAliveTimeElapsedTime() const;
    const bool          isShooting() const;


private:
    void stopShoot();

    float               _angleOrientation;
    bool                _isShooting;
    Vector2f            _prevPosition;
    Vector2f            _newPosition;
    Vector2f            _pointingPosition;
    Vector2f            _centre;
    Clock               _timerShoot;
    Clock               _timerAlive;
    MovementState       _movementState;
    MovementDirection   _movementDirection;
};

#endif //PROJECT_ENEMYSHIP_HPP