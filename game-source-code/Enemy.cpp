/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    14/9/17
/// \brief   Implementation of Enemy ship types
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Enemy.hpp"

EntityEnemy::EntityEnemy(const sf::Vector2i &resolution,
             float distanceFromCentre,
             float angle,
             float scale,
             const TextureHolder &textureHolder,
             const SoundHolder &soundHolder,
             textures::ID id) : Entity{resolution,
                                       distanceFromCentre,
                                       angle,
                                       scale,
                                       textureHolder}
{
    _id = id;
    _lives = 1;
    _sprite.setTexture(textureHolder.get(_id));
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);
    _soundShoot.setBuffer(soundHolder.get(sounds::EnemyShoot));
    _isShooting = false;
    setMove(0,0); //Initialised position at centre of screen
}

void EntityEnemy::setMove(float angle, float distance)
{
    _isMoving = true;
    _futureAngleValue = angle;
    _futureMoveValue = distance;
}

void EntityEnemy::reset()
{
    _angle = 0;
    _angleOrientation = 0;
    _distanceFromCentre = 0;
    _sprite.setScale(0,0);
    _sprite.setPosition(_resolution.x/2,_resolution.y/2);
    _isShooting = false;
}

void EntityEnemy::update()
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

const float EntityEnemy::getRadius()
{
    auto x_pos = _sprite.getPosition().x + _resolution.x/2;
    auto y_pos = _sprite.getPosition().y + _resolution.y/2;

    return sqrt((x_pos*x_pos) + (y_pos*y_pos));
}

const float EntityEnemy::getDistanceFromCentre()
{
    return _distanceFromCentre - _sprite.getGlobalBounds().height/2;
}

const sf::Vector2f EntityEnemy::getPosition()
{
    return _sprite.getPosition();
}

sf::Sprite &EntityEnemy::getSprite()
{
    return _sprite;
}

const sf::Vector2f EntityEnemy::getScale()
{
    return _sprite.getScale();
}


const void EntityEnemy::die()
{
    _lives--;
    if (_lives==0)
    {
        reset();
    }
}

int EntityEnemy::getLives()
{
    return _lives;
}

void EntityEnemy::setShoot()
{
    _isShooting = true;
}

bool EntityEnemy::isShooting()
{
    return _isShooting;
}

float EntityEnemy::getAngle()
{
    return _angle;
}

float EntityEnemy::getDirectionAngle()
{
    return _angleOrientation;
}

void EntityEnemy::shoot()
{
    _soundShoot.setPitch((_distanceFromCentre-_resolution.x/2)/(_resolution.x/2)); //((rand()%20+10)/2.0f));
    _soundShoot.play();
    _isShooting = false;
}

void EntityEnemy::move()
{
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
    _distanceFromCentre += _futureMoveValue * depthScale;
    auto x_pos = _distanceFromCentre * sin(common::degreeToRad(_angle));
    auto y_pos = _distanceFromCentre * cos(common::degreeToRad(_angle));
    auto scale = 1 + ((_distanceFromCentre - (_resolution.x / 2)) / (_resolution.x / 2));

    _sprite.setPosition(x_pos+(_resolution.x / 2),y_pos+(_resolution.y / 2));
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
    _angleOrientation = -1*common::radToDegree(_angleOrientation) - _angle;
    _sprite.setRotation(_angleOrientation);
}
