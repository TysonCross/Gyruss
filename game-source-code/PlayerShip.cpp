//--------------------------------------------------------------------------
// Student  1239448
// @file    PlayerShip.cpp
// @author  Tyson Cross
// @date    2017/09/09
// @brief   Description of file in project Project.
//
// Detailed description of file.
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#include "PlayerShip.hpp"

PlayerShip::PlayerShip(sf::Sprite &sprite,
                       sf::Texture &texture,
                       float distanceFromCentre,
                       int angle = 0,
                       float scale = 1) : _sprite(sprite),
                                          _texture(texture)
{
    _distanceFromCentre = distanceFromCentre;
    _angle = angle;
    _scale = scale;
    _texture.loadFromFile("resources/player_model.png");
    _sprite.setTexture(texture);
    sprite.setScale(_scale, _scale);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    //Initialised position at bottom of play area, not screen origin top-left
    move(0, gameWidth, gameHeight);
}

void PlayerShip::move(int angle, unsigned int width, unsigned int height)
{
    //Euler angle filter
    _angle += angle;
    _angle = _angle % 360;
    if (_angle < 0)
    {
        _angle += 360;
    }
    //Rotate coordinate system by 90 degrees
    _sprite.setPosition(_distanceFromCentre * sin(_angle * (pi / 180)) + width / 2,
                        _distanceFromCentre * cos(_angle * (pi / 180)) + height / 2);
    _sprite.setRotation(-1 * _angle);
}

sf::Sprite &PlayerShip::getSprite()
{
    return _sprite;
}

sf::Texture PlayerShip::getTexture()
{
    return _texture;
}
