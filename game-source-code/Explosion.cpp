/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Explosion entity for destroyed screen objects
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#include "Explosion.hpp"

EntityExplosion::EntityExplosion(const sf::Vector2i resolution,
                     float distanceFromCentre,
                     float angle,
                     float scale,
                     const TextureHolder &textureHolder,
                     const SoundHolder &soundHolder,
                     const textures::ID id) : Entity{resolution,
                                                     distanceFromCentre,
                                                     angle,
                                                     scale,
                                                     textureHolder}
{
    _id = id;
    _lives = 1;
    _rectArea = {0, 0, 128, 128}; // Individual sprite tile
    _soundExplode.setBuffer(soundHolder.get(sounds::Explosion));
    _soundExplode.play();
    _spriteOffset = _rectArea.width; // Animated sprite tileset width
    _sprite.setTexture(textureHolder.get(_id));
    _sprite.setTextureRect(_rectArea);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);
    _sprite.setRotation(-_angle);
    _isMoving = true;
    setMove(_angle,0); // Spawn on object
    move();
    update();
}

void EntityExplosion::setMove(float angle, float distance)
{
    _isMoving = true;
    _futureAngleValue = angle;
    _futureMoveValue = distance;
}

void EntityExplosion::reset()
{
    _isMoving = false;
    _sprite.setPosition(_resolution.x*2,_resolution.y*2); // Move offscreen?
    _sprite.setScale(0,0);
}

void EntityExplosion::update()
{
    if (_isMoving)
    {
        _rectArea.left += _spriteOffset;
        if (_rectArea.left > (2018 - 128)) // Sprite tileset width - individual tile
        {
            die(); // only loop once
        }
        _sprite.setTextureRect(_rectArea);
    }
}

const float EntityExplosion::getRadius()
{
    auto mid = sf::Vector2<float>{_resolution.x/2.f,_resolution.y/2.f};
    auto pos = sf::Vector2<float>{_sprite.getPosition().x,_sprite.getPosition().y};
    sf::Vector2f length = mid-pos;
    return sqrt((length.x * length.x) + (length.y * length.y));
}

const float EntityExplosion::getDistanceFromCentre()
{
    return _distanceFromCentre;
}

const sf::Vector2f EntityExplosion::getPosition()
{
    return _sprite.getPosition();
}

sf::Sprite& EntityExplosion::getSprite()
{
    return _sprite;
}

const sf::Vector2f EntityExplosion::getScale()
{
    return _sprite.getScale();
}

const void EntityExplosion::die()
{
    _lives--;
    if (_lives==0)
    {
        reset();
    }
}

int EntityExplosion::getLives()
{
    return _lives;
}


void EntityExplosion::move()
{

    auto offset = 0.f;
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
    {
        _sprite.setColor(sf::Color(dimColor, dimColor, dimColor));
    }
}