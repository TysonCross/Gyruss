/////////////////////////////////////////////////////////////////////
/// \brief   The main player ship
///
/// The player's ship flies around the centre of the screen in a circle of fixed
/// radius, shooting at enemies.
/////////////////////////////////////////////////////////////////////

#include "PlayerShip.hpp"

PlayerShip::PlayerShip(const Vector2i resolution,
                       float distanceFromCentre,
                       float angle,
                       float scale,
                       const entity::ID type,
                       const TextureHolder &textureHolder) : Entity{resolution,
                                                                    distanceFromCentre,
                                                                    angle,
                                                                    scale,
                                                                    type,
                                                                    textureHolder}
{
    _lives = 3;
    _isUpgraded = false;
    _isAlive = true;
    _invulnerabilityTimeAmount = 1.2f;
    _animationFPSLimit = 0;
    _rectArea = {0, 0, 366, 382}; // Individual sprite tile
    _spriteOffset = _rectArea.width; // Animated sprite tile-set width
    _sprite.setTexture(textureHolder.get(textures::PlayerShip));
    _sprite.setTextureRect(_rectArea);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);
    _isInvulnerable = true;
    _isShooting = false;
    _isMoving = false;
    reset(); //Initialised position at bottom of play area, not screen origin top-left
}

void PlayerShip::setMove(float angle)
{
    _isMoving = true;
    _futureAngleValue = angle;
}

void PlayerShip::reset()
{
    _angle = 0;
    _futureAngleValue = 0;
    _isShooting = false;
    _isMoving = false;
    _isUpgraded = false;
    _isInvulnerable = true;
    _invulnerabilityTimer.restart();
    setMove(0);
}

void PlayerShip::upgrade()
{
    _isUpgraded = true;
}

void PlayerShip::update()
{
    if (_isMoving)
    {
        if (_animationFPSLimit >= 2)
        {
            _animationFPSLimit = 0;
            _rectArea.left += _spriteOffset;
            if (_rectArea.left > (3660 - 366)) // Sprite tile-set width - individual tile
            {
                _rectArea.left = 0;
            }
            _sprite.setTextureRect(_rectArea);
        }
        else
        {
            _animationFPSLimit++;
        }
        move();
    }
    if (_isShooting)
    {
        endShoot();
    }
    if (_invulnerabilityTimer.getElapsedTime().asSeconds() > _invulnerabilityTimeAmount)
    {
        _isInvulnerable = false;
    }
    _isMoving = false;
    _futureAngleValue = 0;
    _isShooting = false;
}

const float PlayerShip::getRadius() const
{
    return getDistanceFromCentre();
}

const float PlayerShip::getDistanceFromCentre() const
{
    return _distanceFromCentre - _sprite.getGlobalBounds().height/2;
}

const Vector2f PlayerShip::getPosition() const
{
    return _sprite.getPosition();
}

const Sprite &PlayerShip::getSprite() const
{
    return _sprite;
}

const Vector2f PlayerShip::getScale() const
{
    return _sprite.getScale();
}

const int PlayerShip::getLives() const
{
    return _lives;
}

const entity::ID PlayerShip::getType() const
{
    return _type;
}

void PlayerShip::die()
{
    _lives--;
    _isAlive = false;
    reset();
}

void PlayerShip::setShoot()
{
    _isShooting = true;
}

const bool PlayerShip::isShooting() const
{
    return _isShooting;
}

const bool PlayerShip::isMoving() const
{
    return _isMoving;
}

const bool PlayerShip::isInvulnerable() const
{
    return _isInvulnerable;
}

const bool PlayerShip::isUpgraded() const
{
    return _isUpgraded;
}

const bool PlayerShip::isAlive() const
{
    return _isAlive;
}

const float PlayerShip::getAngle() const
{
    return _angle;
}

float PlayerShip::getFutureAngle()
{
    return _futureAngleValue;
}

void PlayerShip::move()
{
    _isAlive = true;

    _angle += _futureAngleValue;
    _angle = common::angleFilter(_angle);

    //Rotate coordinate system by 90 degrees
    _sprite.setPosition(_distanceFromCentre * sin(common::degreeToRad(_angle)) + _resolution.x / 2,
                        _distanceFromCentre * cos(common::degreeToRad(_angle)) + _resolution.y / 2);
    _sprite.setRotation(-1 * _angle);
}

void PlayerShip::endShoot()
{
    _isShooting = false;
}


void PlayerShip::makeInvulnerable(bool invulnerability)
{
    _isInvulnerable = invulnerability;
    if (invulnerability)
        _invulnerabilityTimeAmount = 99999.f;
    else
        _invulnerabilityTimeAmount = 1.2f;
}



