/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   The main player ship
///
/// The player's ship flies around the centre of the screen in a circle of fixed
/// radius, shooting at enemies.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "PlayerShip.hpp"

EntityPlayerShip::EntityPlayerShip(const sf::Vector2i resolution,
                       float distanceFromCentre,
                       float angle,
                       float scale,
                       const TextureHolder &textureHolder,
                       const SoundHolder &soundHolder) : Entity{resolution,
                                                                distanceFromCentre,
                                                                angle,
                                                                scale,
                                                                textureHolder}
{
    _lives = 3;
    _soundShoot.setBuffer(soundHolder.get(sounds::PlayerShoot));
    _soundSpawn.setBuffer(soundHolder.get(sounds::SpawnSound));
    _soundMove.setBuffer(soundHolder.get(sounds::PlayerMove));
    _soundDeath.setBuffer(soundHolder.get(sounds::PlayerDeath));
    _soundMove.setLoop(1);
    _soundMove.play();
    _soundSpawn.play();

    _rectArea = {0, 0, 366, 382}; // Individual sprite tile
    _spriteOffset = _rectArea.width; // Animated sprite tileset width
    _sprite.setTexture(textureHolder.get(textures::PlayerShip));
    _sprite.setTextureRect(_rectArea);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);

    _isShooting = false;
    _isMoving = false;
    reset(); //Initialised position at bottom of play area, not screen origin top-left
}

void EntityPlayerShip::setMove(float angle)
{
    _isMoving = true;
    _futureAngleValue = angle;
}

void EntityPlayerShip::reset()
{
    _angle = 0;
    _futureAngleValue = 0;
    _isShooting = false;
    _isMoving = false;
//    move();
    setMove(0);
}

void EntityPlayerShip::update()
{
    if (_isMoving)
    {
        _rectArea.left += _spriteOffset;
        if (_rectArea.left > (3660 - 366)) // Sprite tileset width - individual tile
        {
            _rectArea.left = 0;
        }
        _sprite.setTextureRect(_rectArea);
        move();
    }
    if (_isShooting)
    {
        shoot();
    }
    _isMoving = false;
    _futureAngleValue = 0;
    _isShooting = false;
}

const float EntityPlayerShip::getRadius()
{
    return getDistanceFromCentre();
}

const float EntityPlayerShip::getDistanceFromCentre()
{
    return _distanceFromCentre - _sprite.getGlobalBounds().height/2;
}

const sf::Vector2f EntityPlayerShip::getPosition()
{
    return _sprite.getPosition();
}


sf::Sprite &EntityPlayerShip::getSprite()
{
    return _sprite;
}

const sf::Vector2f EntityPlayerShip::getScale()
{
    return _sprite.getScale();
}

const void EntityPlayerShip::die()
{
    _soundDeath.play();
    _lives--;
    reset();
}

int EntityPlayerShip::getLives()
{
    return _lives;
}

void EntityPlayerShip::setShoot()
{
    _isShooting = true;
}

bool EntityPlayerShip::isShooting()
{
    return _isShooting;
}

float EntityPlayerShip::getAngle()
{
    return _angle;
}

void EntityPlayerShip::move()
{
    _soundMove.setPitch(fabs(_futureAngleValue/4)); // Engine pitch rises when moving
    _soundMove.setPosition(_sprite.getPosition().x,_sprite.getPosition().y,-5);
    _angle += _futureAngleValue;
    _angle = common::angleFilter(_angle);
    //Rotate coordinate system by 90 degrees
    _sprite.setPosition(_distanceFromCentre * sin(common::degreeToRad(_angle)) + _resolution.x / 2,
                        _distanceFromCentre * cos(common::degreeToRad(_angle)) + _resolution.y / 2);
    _sprite.setRotation(-1 * _angle);
}

void EntityPlayerShip::shoot()
{
    //_soundShoot.setPitch(((rand()%3)/6.0f)+0.3);
    _soundShoot.play();
    _isShooting = false;
}
