/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    14/9/17
/// \brief   Enemy ship types
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_ENEMYSHIP_HPP
#define PROJECT_ENEMYSHIP_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <cmath>
#include "ResourceMapper.hpp"
#include "common.hpp"

class Enemy //: public Entity
{
public:
    enum Type
    {
        GreyShip = 0,
        PurpleShip = 1,
    };

    Enemy(const ResourceMapper &resourceMapper,
          common::Resolution resolution,
          float distanceFromCentre,
          float angle,
          float scale,
          Type type);

    void move(float angle, float distance);
    sf::Sprite &getSprite();

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Sprite _sprite;
    sf::Texture _texture;
    common::Resolution _resolution;
    float _distanceFromCentre;
    float _angle;
    float _scale;
    Type _type;
};

#endif //PROJECT_ENEMYSHIP_HPP