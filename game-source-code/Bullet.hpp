/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    15/9/17
/// \brief   Projectiles/bullets for PlayerShip and EnemyShip
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_BULLET_HPP
#define PROJECT_BULLET_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <cmath>
#include "common.hpp"
#include "ResourceHolder.hpp"

class Bullet //: public Entity
{
public:

    Bullet(const TextureHolder &textureHolder,
           const SoundHolder &soundHolder,
           const common::Resolution resolution,
           float distanceFromCentre,
           float angle,
           float scale,
           textures::ID type);

    void move(float distance);
    void reset();
    void update();
    float getDistanceFromCentre();
    sf::Sprite &getSprite();

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Sprite _sprite;
    common::Resolution _resolution;
    float _distanceFromCentre;
    float _angle;
    float _scale;
    float _futureAngleValue;
    float _futureMoveValue;
    bool _isMoving;
    bool _isShooting;
    textures::ID _id;
};

#endif //PROJECT_BULLET_HPP
