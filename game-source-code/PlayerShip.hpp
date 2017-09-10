//--------------------------------------------------------------------------
// Student  1239448
// @file    PlayerShip.hpp
// @author  Tyson Cross and Chris Maree
// @date    2017/09/09
// @brief   Player ship
//
// Object for the player ship model
//
// Copyright (c) 2017 Tyson Cross and Chris Maree, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#ifndef PROJECT_PLAYERSHIP_HPP
#define PROJECT_PLAYERSHIP_HPP
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Game.hpp"
#include "common.hpp"
#include "ResourceMapper.hpp"

class TextureNotFound{};

class PlayerShip
{
public:

    PlayerShip(float distanceFromCentre,const ResourceMapper& resourceMapper, int angle, float scale);
    void move(int angle);

    sf::Sprite &getSprite();
    sf::Texture getTexture();

private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    float _distanceFromCentre;
    int _angle;
    float _scale;
};

#endif //PROJECT_PLAYERSHIP_HPP
