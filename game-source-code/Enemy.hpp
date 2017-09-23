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
#include <SFML/Audio.hpp>
#include <cmath>
#include "common.hpp"
#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "SoundController.hpp"

class Enemy : public Entity
{
public:
    Enemy(const sf::Vector2i &resolution,
          float distanceFromCentre,
          float angle,
          float scale,
          const entity::ID type,
          const TextureHolder &textureHolder,
          textures::ID id);

    void setMove(float angle, float distance) override;
    void move() override;
    void reset() override;
    void update() override;
    const float getRadius() override;
    const float getDistanceFromCentre() override;
    const sf::Vector2f getPosition() override;
    const sf::Sprite &getSprite() override;
    const sf::Vector2f getScale() override;
    const void die() override;
    const int getLives() override;
    const entity::ID getType();

    void setShoot();
    bool isShooting();
    float getAngle();
    float getDirectionAngle();

private:
    void shoot();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    float _angleOrientation;
    bool _isShooting;
    sf::Vector2<float> _prevPosition,
                        _newPosition,
                        _pointingPosition;
};

#endif //PROJECT_ENEMYSHIP_HPP