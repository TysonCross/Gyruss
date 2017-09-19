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
#include "common.hpp"
#include "ResourceHolder.hpp"

class Enemy //: public Entity
{
public:

    Enemy(const TextureHolder &textureHolder,
          const SoundHolder &soundHolder,
          const common::Resolution resolution,
          float distanceFromCentre,
          float angle,
          float scale,
          textures::ID id);
    void setMove(float angle, float distance);
    void setShoot();
    bool isShooting();
    void reset();
    void update();
    float getAngle();
    float getDirectionAngle();
    float getDistanceFromCentre();
    float getRadius();
    sf::Sprite &getSprite();

private:
    void shoot();
    void move();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Sprite _sprite;
    sf::Sound _soundShoot;
    common::Resolution _resolution;
    float _distanceFromCentre;
    float _angle;
    float _angleOrientation;
    float _scale;
    float _futureAngleValue;
    float _futureMoveValue;
    bool _isMoving;
    bool _isShooting;
    sf::Vector2<float> _prevPosition,
                        _newPosition,
                        _pointingPosition;
    textures::ID _id;
};

#endif //PROJECT_ENEMYSHIP_HPP