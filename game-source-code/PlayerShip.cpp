//--------------------------------------------------------------------------
// Student  1239448
// @file    PlayerShip.cpp
// @author  Tyson Cross and Chris Maree
// @date    2017/09/09
// @brief   Description of file in project Project.
//
// Detailed description of file.
//
// Copyright (c) 2017 Tyson Cross and Chris Maree, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#include "PlayerShip.hpp"
#include <iostream>

float degreeToRad(float degree)
{
    return degree * (pi / 180);
}

int eulerFilter(int angle)
{
    angle = angle % 360;
    if (angle < 0)
    {
        angle += 360;
    }
    return angle;
}

PlayerShip::PlayerShip(
                        const ResourceMapper &resourceMapper,
                        float distanceFromCentre,
                        int angle = 0,
                        float scale = 1)
{
    _distanceFromCentre = distanceFromCentre;
    _angle = angle;
    _scale = scale;

    _texture.loadFromFile(resourceMapper.getResource("PlayerShip"));
    _sprite.setTexture(_texture);
    _sprite.setScale(_scale, _scale);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);

    move(0); //Initialised position at bottom of play area, not screen origin top-left
}

void PlayerShip::move(int angle)
{
    _angle += angle;
    _angle = eulerFilter(_angle);
    //Rotate coordinate system by 90 degrees
    _sprite.setPosition(_distanceFromCentre * sin(degreeToRad(_angle)) + resolution.x / 2,
                        _distanceFromCentre * cos(degreeToRad(_angle)) + resolution.y / 2);
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
