/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Explosion entity for destroyed screen objects
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_EXPLOSION_HPP
#define PROJECT_EXPLOSION_HPP

#include "SFML/Graphics.hpp"
#include "common.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"

class Explosion : public Entity
{
public:
    Explosion(const sf::Vector2i resolution,
              float distanceFromCentre,
              float angle,
              float scale,
              const entity::ID type,
              const TextureHolder &textureHolder,
              const textures::ID id);

    void setMove(float angle, float distance) override;
    void move() override;
    void reset() override;
    void update() override;
    const float getRadius() const override;
    const float getDistanceFromCentre() const override;
    const sf::Vector2f getPosition() const override;
    const sf::Sprite &getSprite() const override;
    const sf::Vector2f getScale() const override;
    const int getLives() const override;

    const void die() override;
private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::IntRect _rectArea;
    int _spriteOffset;
};

#endif //PROJECT_EXPLOSION_HPP
