/////////////////////////////////////////////////////////////////////
/// \brief   Implementation of Enemy ship types
/////////////////////////////////////////////////////////////////////

#include "Enemy.hpp"

Enemy::Enemy(const Vector2i &resolution,
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
    _movementState = movementState;
    _movementDirection = movementDirection;
    _centre = {0,0};
    setMove(angle, distanceFromCentre, _centre); //Initialised position at starting point
}

void Enemy::setMove(float angle, float distance)
{
    _isMoving = true;
    _futureAngleValue = angle;
    _futureMoveValue = distance;
    _centre = {0,0};
}

void Enemy::setMove(float angle, float distance, Vector2f centre)
{
    _isMoving = true;
    _futureAngleValue = angle;
    _futureMoveValue = distance;
    _centre = centre;
}

void Enemy::setMovementState(MovementState movementState)
{
    _movementState = movementState;
}

void Enemy::reset()
{
    _angleOrientation = 0;
    _sprite.setScale(0, 0);
    _sprite.setPosition(_resolution.x / 2, _resolution.y / 2);
    _isShooting = false;
    _centre = {0, 0};
    // if the ship is a wanderer and hits the side of the screen, needs to respawn with its previous movement type
    if (_movementState == MovementState::Wandering)
    {
        _angle = rand() % 360;
        _distanceFromCentre = _resolution.y / 7;
        _movementState = MovementState::Wandering;
    }
    else
    {
        _angle = 0;
        _distanceFromCentre = 0;
        _movementState = MovementState::SpiralOut;
    }
}

void Enemy::update()
{
    if (_isMoving)
    {
        move();
    }
    if (_isShooting)
    {
        stopShoot();
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
    auto hypotenuse = sqrt((_centre.x * _centre.x) + (_centre.y * _centre.y));
    return (_distanceFromCentre + hypotenuse) - (_sprite.getGlobalBounds().height / 2);
}

const Vector2f Enemy::getCentre() const
{
    return _centre;
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
    return 1;
}

const Vector2f Enemy::getPosition() const
{
    return _sprite.getPosition();
}

const Sprite &Enemy::getSprite() const
{
    return _sprite;
}

const Vector2f Enemy::getScale() const
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

const bool Enemy::isAlive() const
{
    return _isAlive;
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
    auto x_pos = _sprite.getPosition().x - _resolution.x/2;
    auto y_pos = _sprite.getPosition().y - _resolution.y/2;
    auto radianAngle = atan2(x_pos,y_pos);
    return common::angleFilter(common::radToDegree(radianAngle));
}

const float Enemy::getOrientationAngle() const
{
    return _angleOrientation;
}

void Enemy::stopShoot()
{
    _isShooting = false;
}

void Enemy::setScale(float scaleX, float scaleY)
{
    _sprite.setScale(scaleX, scaleY);
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
        offset = float(_resolution.x*0.3);
    }
    auto depthScale = ((_distanceFromCentre + offset)/(_resolution.x/2));
    _distanceFromCentre += (_futureMoveValue) * depthScale;
    auto xPos = _distanceFromCentre * sin(common::degreeToRad(_angle))+_centre.x;
    auto yPos = _distanceFromCentre * cos(common::degreeToRad(_angle))+_centre.y;
    auto scale = 1 + ((getRadius() - (_resolution.x / 2)) / (_resolution.x / 2));

    _sprite.setPosition(xPos+(_resolution.x / 2),yPos+(_resolution.y / 2));
    _sprite.setScale(scale * _scale,scale * _scale);
    // Dimming
    auto dimColor = (scale*55) + 200;
    _sprite.setColor(Color(dimColor,dimColor,dimColor));

    setOrientation();
}

void Enemy::setOrientation()
{
    // Orientation
    _newPosition = _sprite.getPosition();
    _newPosition.x -= _resolution.x/2;
    _newPosition.y -= _resolution.y/2;
    _pointingPosition = _newPosition - _prevPosition;
    _angleOrientation = _futureAngleValue = atan2(_pointingPosition.x,_pointingPosition.y) - atan2(_prevPosition.x,_prevPosition.y);
    _angleOrientation = -1*common::radToDegree(_angleOrientation) - getAngle();
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

const float Enemy::getAliveTimeElapsedTime() const
{
    return _timerAlive.getElapsedTime().asSeconds();
}