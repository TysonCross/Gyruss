/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Explosion entity for destroyed screen objects
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#include "Explosion.hpp"

Explosion::Explosion(const sf::Vector2i resolution,
                     float distanceFromCentre,
                     float angle,
                     float scale,
                     const entity::ID type,
                     const TextureHolder &textureHolder,
                     const textures::ID id) : Entity{resolution,
                                                     distanceFromCentre,
                                                     angle,
                                                     scale,
                                                     type,
                                                     textureHolder}
{
    _id = id;
    _lives = 1;
    _rectArea = {0, 0, 128, 128}; // Individual sprite tile
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

void Explosion::setMove(float angle, float distance)
{
    _isMoving = true;
    _futureAngleValue = angle;
    _futureMoveValue = distance;
}

void Explosion::reset()
{
    _isMoving = false;
    _sprite.setPosition(_resolution.x*2,_resolution.y*2); // Move offscreen?
    _sprite.setScale(0,0);
}

void Explosion::update()
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

const float Explosion::getRadius() const
{
    auto mid = sf::Vector2<float>{_resolution.x/2.f,_resolution.y/2.f};
    auto pos = sf::Vector2<float>{_sprite.getPosition().x,_sprite.getPosition().y};
    sf::Vector2f length = mid-pos;
    return sqrt((length.x * length.x) + (length.y * length.y));
}

const float Explosion::getDistanceFromCentre() const
{
    return _distanceFromCentre;
}

const sf::Vector2f Explosion::getPosition() const
{
    return _sprite.getPosition();
}

const sf::Sprite& Explosion::getSprite() const
{
    return _sprite;
}

const sf::Vector2f Explosion::getScale() const
{
    return _sprite.getScale();
}

const int Explosion::getLives() const
{
    return _lives;
}

void Explosion::die()
{
    _lives--;
    if (_lives==0)
    {
        reset();
    }
}

void Explosion::move()
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