/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    PlayerShip.hpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/09
/// \brief   Player ship
///
/// Object for the player ship model
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_PLAYERSHIP_HPP
#define PROJECT_PLAYERSHIP_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Game.hpp"
#include "common.hpp"
#include "ResourceMapper.hpp"

class PlayerShip
{
public:

    PlayerShip(const ResourceMapper &resourceMapper, float distanceFromCentre, int angle, float scale);
    void move(int angle);

    sf::Sprite &getSprite();
    sf::Texture &getTexture();

private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    float _distanceFromCentre;
    int _angle;
    float _scale;
};

#endif //PROJECT_PLAYERSHIP_HPP
