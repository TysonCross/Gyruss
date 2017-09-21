/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    15/9/17
/// \brief   Projectile bullet Class
///
/// A bullet, can be an enemy or player projectile
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Bullet.hpp"

Bullet::Bullet(const sf::Vector2i resolution,
                           float distanceFromCentre,
                           float angle,
                           float scale,
                           const TextureHolder &textureHolder,
                           const textures::ID id) : Entity{resolution,
                                                           distanceFromCentre,
                                                           angle,
                                                           scale,
                                                           textureHolder}
{
    _id = id;
    _lives = 1;
    _rectArea = {0, 0, 70, 110}; // Individual sprite tile
    _spriteOffset = _rectArea.width; // Animated sprite tileset width
    _sprite.setTexture(textureHolder.get(_id));
    _sprite.setTextureRect(_rectArea);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);
    _sprite.setRotation(-_angle);
    _isMoving = true;
//    setMove((_distanceFromCentre - (_distanceFromCentre*0.5))); // Spawn at Ship Gun barrel
    setMove(0); // Spawn at Ship Gun barrel
    update();
}

void Bullet::setMove(float distance)
{
    _isMoving = true;
    _futureMoveValue = distance;
}

void Bullet::setMove(float angle, float distance)
{
    _isMoving = true;
//    _angle = angle;
    _futureAngleValue = angle;
    _futureMoveValue = distance;
}

void Bullet::reset()
{
    _isMoving = false;
    _sprite.setPosition(_resolution.x,_resolution.y); // Move offscreen?
    _sprite.setScale(0,0);
}

void Bullet::update()
{
    if (_isMoving)
    {
        _rectArea.left += _spriteOffset;
        if (_rectArea.left > (420 - 70)) // Sprite tileset width - individual tile
        {
            _rectArea.left = 0;
        }
        _sprite.setTextureRect(_rectArea);
        move();
    }
}

const float Bullet::getRadius()
{
    auto mid = sf::Vector2<float>{_resolution.x/2.f,_resolution.y/2.f};
    auto pos = sf::Vector2<float>{_sprite.getPosition().x,_sprite.getPosition().y};
    sf::Vector2f length = mid-pos;
    return sqrt((length.x * length.x) + (length.y * length.y));
}

const float Bullet::getDistanceFromCentre()
{
    return _distanceFromCentre - _sprite.getGlobalBounds().height/2;
}

const sf::Vector2f Bullet::getPosition()
{
    return _sprite.getPosition();
}

sf::Sprite& Bullet::getSprite()
{
    return _sprite;
}

const sf::Vector2f Bullet::getScale()
{
    return _sprite.getScale();
}

const void Bullet::die()
{
    _lives--;
    if (_lives==0)
    {
        reset();
    }
}

int Bullet::getLives()
{
    return _lives;
}


void Bullet::move()
{

    auto offset = 0.f;
    if(_distanceFromCentre==0)
        offset = _resolution.x*0.2;

    auto depthScale = ((_distanceFromCentre + offset)/(_resolution.y/2));
    _distanceFromCentre += _futureMoveValue * depthScale;
    auto x_pos = _distanceFromCentre * sin(common::degreeToRad(_angle));
    auto y_pos = _distanceFromCentre * cos(common::degreeToRad(_angle));
    auto scale = 1 + ((getRadius() - (_resolution.y / 2)) / (_resolution.y / 2));
    _sprite.setPosition(x_pos+(_resolution.x / 2),y_pos+(_resolution.y / 2));
    _sprite.setScale(scale * _scale,scale * _scale);

    // Dimming
    auto dimColor = (scale*200) + 55;
    if (getRadius() >= (_resolution.y/2))

    _sprite.setColor(sf::Color(dimColor,dimColor,dimColor));
}