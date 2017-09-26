/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    26/9/17
/// \brief   Meteroid Entity (cannot be destroyed by bullets)
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_METEROID_HPP
#define PROJECT_METEROID_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <cmath>
#include "common.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"

class Meteoroid : public Entity
{
public:
    Meteoroid(const sf::Vector2i resolution,
           float distanceFromCentre,
           float angle,
           float scale,
           const entity::ID type,
           const TextureHolder &textureHolder,
           const textures::ID id);

    void setMove(float distance) override;
    void move() override;
    void reset() override;
    void update() override;
    const float getRadius() const override;
    const float getDistanceFromCentre() const override;
    const sf::Vector2f getPosition() const override;
    const sf::Sprite &getSprite() const override;
    const sf::Vector2f getScale() const override;
    const int getLives() const override;
    void die() override;

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::IntRect _rectArea;
    int _spriteOffset;
};

#endif //PROJECT_METEROID_HPP
