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
#include "Entity.hpp"
#include "ResourceHolder.hpp"

class Bullet : public Entity
{
public:
    Bullet(const sf::Vector2i resolution,
           float distanceFromCentre,
           float angle,
           float scale,
           const TextureHolder &textureHolder,
           const textures::ID id);

    void setMove(float distance) override;
    void reset() override;
    void update() override;
    const float getRadius() override;
    const float getDistanceFromCentre() override;
    sf::Sprite &getSprite() override;
    sf::Vector2f getScale() override;
    const void die() override;
    int getLives() override;

private:
    void move() override;
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::IntRect _rectArea;
    int _spriteOffset;
};

#endif //PROJECT_BULLET_HPP
