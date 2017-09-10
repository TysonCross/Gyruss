//--------------------------------------------------------------------------
// Student  1239448
// @file    PlayerShip.hpp
// @author  Tyson Cross
// @date    2017/09/09
// @brief   Player ship
//
// Object for the player ship model
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#ifndef PROJECT_PLAYERSHIP_HPP
#define PROJECT_PLAYERSHIP_HPP
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Game.hpp"

class PlayerShip
{
public:
    PlayerShip(sf::Sprite& sprite, sf::Texture& texture, float distanceFromCentre, int angle, float scale);
    void move(int angle, unsigned int _windowWidth, unsigned int _windowHeight);
    sf::Sprite& getSprite();
    sf::Texture getTexture();

private:
    sf::Sprite& _sprite;
    sf::Texture& _texture;
    float _distanceFromCentre;
    int _angle;
    float _scale;
};

#endif //PROJECT_PLAYERSHIP_HPP
