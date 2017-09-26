/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    14/9/17
/// \brief   Implementation of Enemy ship types
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Enemy.hpp"

Enemy::Enemy(const sf::Vector2i &resolution,
             float distanceFromCentre,
             float angle,
             float scale,
             const entity::ID type,
             const TextureHolder &textureHolder,
             const textures::ID id,
             MovementState movementState,
             MovementDirection movementDirection) : Entity{resolution,
                                                           distanceFromCentre,
                                                           angle,
                                                           scale,
                                                           type,
                                                           textureHolder}
{
    _id = id;
    _lives = 1;
    _sprite.setTexture(textureHolder.get(_id));
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);
    _isShooting = false;
    setMove(angle,distanceFromCentre,0,0); //Initialised position at starting point
    _movementState = movementState;
    _movementDirection = movementDirection;
    _xOffset = 0;
    _yOffset = 0;
}

void Enemy::setMove(float angle, float distance)
{
    _isMoving = true;
    _futureAngleValue = angle;
    _futureMoveValue = distance;
    _xOffset=0;
    _yOffset=0;
}

void Enemy::setMove(float angle, float distance, float xOffset, float yOffset)
{
    _isMoving = true;
    _futureAngleValue = angle;
    _futureMoveValue = distance;
    _xOffset=xOffset;
    _yOffset=yOffset;
}

void Enemy::setMovementState(MovementState movementState)
{
    _movementState = movementState;
}

void Enemy::reset()
{
    _angle = 0;
    _angleOrientation = 0;
    _distanceFromCentre = 0;
    _sprite.setScale(0,0);
    _sprite.setPosition(_resolution.x/2,_resolution.y/2);
    _isShooting = false;
    _yOffset = 0;
    _xOffset = 0;
    _movementState = MovementState::SpiralOut;
}

void Enemy::update()
{
    if (_isMoving)
    {
        move();
    }
    if (_isShooting)
    {
        shoot();
    }
}

const float Enemy::getRadius() const
{
    auto xPos = _sprite.getPosition().x - _resolution.x/2;
    auto yPos = _sprite.getPosition().y - _resolution.y/2;

    return sqrt((xPos*xPos) + (yPos*yPos));
}

const float Enemy::getDistanceFromCentre() const
{
    return _distanceFromCentre - _sprite.getGlobalBounds().height/2;
}

const float Enemy::getDistanceFromCentreWithOffset() const
{
    return (_distanceFromCentre+sqrt(_xOffset*_xOffset+_yOffset*_yOffset)) - _sprite.getGlobalBounds().height/2;
}

const float Enemy::getOffsetX() const
{
    return _xOffset;
}

const float Enemy::getOffsetY() const
{
    return _yOffset;
}

const MovementState Enemy::getMovementState() const
{
    return _movementState;
}

const int Enemy::getMovementDirectionSign() const
{
    // Swaps the direction of the angle increase
    switch (_movementDirection)
    {
        case (MovementDirection::CounterClockwise) :
            return -1;
        case (MovementDirection::Clockwise) :
            return 1;
    }
}

const sf::Vector2f Enemy::getPosition() const
{
    return _sprite.getPosition();
}

const sf::Sprite &Enemy::getSprite() const
{
    return _sprite;
}

const sf::Vector2f Enemy::getScale() const
{
    return _sprite.getScale();
}


void Enemy::die()
{
    _lives--;
    if (_lives==0)
    {
        reset();
    }
}

const int Enemy::getLives() const
{
    return _lives;
}

const entity::ID Enemy::getType() const
{
    return _type;
}

void Enemy::setShoot()
{
    _isShooting = true;
}

const bool Enemy::isShooting() const
{
    return _isShooting;
}

const float Enemy::getAngle() const
{
    return _angle;
}

const float Enemy::getDirectionAngle() const
{
    return _angleOrientation;
}

const float Enemy::getAngleWithOffset()
{
    auto x_pos = _sprite.getPosition().x - _resolution.x/2;
    auto y_pos = _sprite.getPosition().y - _resolution.y/2;
    auto radianAngle = atan2(x_pos,y_pos);
    return common::angleFilter(common::radToDegree(radianAngle));
}

void Enemy::shoot()
{
    _isShooting = false;
}

void Enemy::move()
{
    // Store old position
    _prevPosition = _sprite.getPosition();
    _prevPosition.x -= _resolution.x/2;
    _prevPosition.y -= _resolution.y/2;

    _angle += _futureAngleValue;
    _angle = common::angleFilter(_angle);
    auto offset = 0.f;
    if(_distanceFromCentre==0)
    {
        offset = _resolution.x*0.3;
    }
    auto depthScale = ((_distanceFromCentre + offset)/(_resolution.x/2));
    _distanceFromCentre += (_futureMoveValue) * depthScale;
    auto xPos = _distanceFromCentre * sin(common::degreeToRad(_angle))+_xOffset;
    auto yPos = _distanceFromCentre * cos(common::degreeToRad(_angle))+_yOffset;
    auto scale = 1 + ((getRadius() - (_resolution.x / 2)) / (_resolution.x / 2));

    _sprite.setPosition(xPos+(_resolution.x / 2),yPos+(_resolution.y / 2));
    _sprite.setScale(scale * _scale,scale * _scale);
    // Dimming
    auto dimColor = (scale*55) + 200;
    _sprite.setColor(sf::Color(dimColor,dimColor,dimColor));

    // Orientation
    _newPosition = _sprite.getPosition();
    _newPosition.x -= _resolution.x/2;
    _newPosition.y -= _resolution.y/2;
    _pointingPosition = _newPosition - _prevPosition;
    _angleOrientation = _futureAngleValue = atan2(_pointingPosition.x,_pointingPosition.y) - atan2(_prevPosition.x,_prevPosition.y); // ? Should be -?
    _angleOrientation = -1*common::radToDegree(_angleOrientation) - getAngleWithOffset();
    _sprite.setRotation(_angleOrientation);
}

const float Enemy::getShootTimerElapsedTime() const
{
    return _timerShoot.getElapsedTime().asSeconds();
}

void Enemy::resetShootTimer()
{
    _timerShoot.restart();
}