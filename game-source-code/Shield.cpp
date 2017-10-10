/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    27/9/17
/// \brief   Shield object implementation
///
/// Used to indicate visually a state of invulnerability
/////////////////////////////////////////////////////////////////////

#include "Shield.hpp"

Shield::Shield(const Vector2i resolution,
               float distanceFromCentre,
               float angle,
               float scale,
               const TextureHolder &textureHolder,
               PlayerShip &playerShip) : _resolution{resolution},
                                         _distanceFromCentre{distanceFromCentre},
                                         _angle{angle},
                                         _scale{scale},
                                         _playerShip{playerShip}
{
    _animationFPSLimit = 0;
    _rectArea = {0, 0, 256, 256}; // Individual sprite tile
    _spriteOffset = _rectArea.width; // Animated sprite tile-set width
    _sprite.setTexture(textureHolder.get(textures::Shield));
    _sprite.setTextureRect(_rectArea);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    _sprite.setScale(_scale, _scale);
    reset(); //Initialised position invisible, offscreen
}

void Shield::reset()
{
    _sprite.setScale(0,0);
    _sprite.setPosition(_resolution.x*2,_resolution.y*2);
    _rectArea.left = 0;
}

void Shield::move()
{
    _sprite.setPosition(_playerShip.getSprite().getPosition());
    _sprite.setScale(_playerShip.getSprite().getScale().x * 2.2, _playerShip.getSprite().getScale().y * 2.2);
    _sprite.setRotation(_playerShip.getSprite().getRotation());
}

const Sprite &Shield::getSprite() const
{
    return _sprite;
}

void Shield::update()
{
    if (_playerShip.isInvulnerable())
    {
        auto numberFrames = 20;
        if (_animationFPSLimit >= 3)
        {
            _animationFPSLimit = 0;
            _rectArea.left += _spriteOffset;
            if (_rectArea.left > (_spriteOffset * (numberFrames - 1))) // Sprite tile-set width - individual tile
            {
                _rectArea.left = 0;
            }
            _sprite.setTextureRect(_rectArea);
        } else
        {
            _animationFPSLimit++;
        }
        move();
    } else
        reset();
}