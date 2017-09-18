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
                       float scale = 1) : _resolution(resolution)
{
    _distanceFromCentre = distanceFromCentre;
    _angle = angle;
    _scale = scale;

    _soundShoot.setBuffer(soundHolder.get(sounds::PlayerShoot));
    _soundSpawn.setBuffer(soundHolder.get(sounds::SpawnSound));
    _soundMove.setBuffer(soundHolder.get(sounds::PlayerMove));
    _soundMove.setLoop(1);
    _soundMove.play();
    _soundSpawn.play();

    _sprite.setTexture(textureHolder.get(textures::PlayerShip));
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);

    move(0); //Initialised position at bottom of play area, not screen origin top-left
}

void PlayerShip::move(float angle)
{
    _soundMove.setPitch(fabs(angle/4)); // Engine pitch rises when moving
    _soundMove.setPosition(_sprite.getPosition().x,_sprite.getPosition().y,-5);
    _angle += angle;
    _angle = common::angleFilter(_angle);
    //Rotate coordinate system by 90 degrees
    _sprite.setPosition(_distanceFromCentre * sin(common::degreeToRad(_angle)) + _resolution.x / 2,
                        _distanceFromCentre * cos(common::degreeToRad(_angle)) + _resolution.y / 2);
    _sprite.setRotation(-1 * _angle);
}

float PlayerShip::getDistanceFromCentre()
{
    return _distanceFromCentre - _sprite.getOrigin().y;
}

float PlayerShip::getAngle()
{
    return _angle;
}

void PlayerShip::shoot()
{
    //_soundShoot.setPitch(((rand()%3)/6.0f)+0.3);
    _soundShoot.play();
}

sf::Sprite &PlayerShip::getSprite()
{
    return _sprite;
}
