/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    15/9/17
/// \brief   Projectile bullet Class
///
/// A bullet, can be an enemy or player projectile
/////////////////////////////////////////////////////////////////////

#include "Bullet.hpp"

Bullet::Bullet(const Vector2i resolution,
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
    _rectArea = {0, 0, 70, 110}; // Individual sprite tile
    _spriteOffset = _rectArea.width; // Animated sprite tileset width
    _sprite.setTexture(textureHolder.get(_id));
    _sprite.setTextureRect(_rectArea);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);
    _sprite.setRotation(-_angle);
    _isMoving = true;
    setMove(0); // Spawn at Ship Gun barrel
    update();
}

void Bullet::setMove(float distance)
{
    _isMoving = true;
    _futureMoveValue = distance;
}

void Bullet::reset()
{
    _isMoving = false;
    _sprite.setPosition(_resolution.x*2,_resolution.y*2); // Move off-screen
    _sprite.setScale(0,0);
}

void Bullet::update()
{
    if (_isMoving)
    {
        if (_animationFPSLimit >= 2)
        {
            _animationFPSLimit = 0;
            _rectArea.left += _spriteOffset;
            if (_rectArea.left > (420 - 70)) // Sprite tile-set width - individual tile
            {
                _rectArea.left = 0;
            }
            _sprite.setTextureRect(_rectArea);
        } else
        {
            _animationFPSLimit++;
        }
        move();
    }
}

const float Bullet::getRadius() const
{
    auto mid = Vector2f{_resolution.x/2.f,_resolution.y/2.f};
    auto pos = Vector2f{_sprite.getPosition().x,_sprite.getPosition().y};
    Vector2f length = mid-pos;
    return sqrt((length.x * length.x) + (length.y * length.y));
}

const float Bullet::getDistanceFromCentre() const
{
    return _distanceFromCentre - _sprite.getGlobalBounds().height/2;
}

const Vector2f Bullet::getPosition() const
{
    return _sprite.getPosition();
}

const Sprite& Bullet::getSprite() const
{
    return _sprite;
}

const Vector2f Bullet::getScale() const
{
    return _sprite.getScale();
}

const int Bullet::getLives() const
{
    return _lives;
}

void Bullet::die()
{
    _lives--;
    if (_lives==0)
    {
        reset();
    }
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

    _sprite.setColor(Color(dimColor,dimColor,dimColor));
}

const float Bullet::getAngle() const
{
    return _angle;
}