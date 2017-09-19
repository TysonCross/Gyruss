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

PlayerShip::PlayerShip(const TextureHolder &textureHolder,
                       const SoundHolder &soundHolder,
                       const common::Resolution resolution,
                       float distanceFromCentre,
                       float angle = 0,
                       float scale = 1) : _distanceFromCentre(distanceFromCentre),
                                          _angle(angle),
                                          _scale(scale),
                                          _resolution(resolution),
                                          _isShooting(false),
                                          _isMoving(false)
{
    _soundShoot.setBuffer(soundHolder.get(sounds::PlayerShoot));
    _soundSpawn.setBuffer(soundHolder.get(sounds::SpawnSound));
    _soundMove.setBuffer(soundHolder.get(sounds::PlayerMove));
    _soundMove.setLoop(1);
    _soundMove.play();
    _soundSpawn.play();

    _rectArea = {0, 0, 366, 382}; // Individual sprite tile
    _spriteOffset = _rectArea.width; // Animated sprite tileset width
    _sprite.setTexture(textureHolder.get(textures::PlayerShip));
    _sprite.setTextureRect(_rectArea);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);

    reset(); //Initialised position at bottom of play area, not screen origin top-left
}

void PlayerShip::setMove(float angle)
{
    _isMoving = true;
    _futureAngleValue = angle;
}

void PlayerShip::setShoot()
{
    _isShooting = true;
}

bool PlayerShip::isShooting()
{
    return _isShooting;
}

void PlayerShip::reset()
{
    _angle = 0;
    _futureAngleValue = 0;
    _isShooting = false;
    _isMoving = false;
    move();
}

void PlayerShip::update()
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

sf::Sprite &PlayerShip::getSprite()
{
    return _sprite;
}


float PlayerShip::getDistanceFromCentre()
{
    return _distanceFromCentre - _sprite.getOrigin().y;
}

float PlayerShip::getAngle()
{
    return _angle;
}

void PlayerShip::move()
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

void PlayerShip::shoot()
{
    //_soundShoot.setPitch(((rand()%3)/6.0f)+0.3);
    _soundShoot.play();
    _isShooting = false;
}
