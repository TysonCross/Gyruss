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
          SoundHolder &soundHolder,
          common::Resolution resolution,
          float distanceFromCentre,
          float angle,
          float scale,
          textures::ID id);

    void move(float angle, float distance);
    float getDistanceFromCentre();
    sf::Sprite &getSprite();
    float getAngle();
    float getDirectionAngle();
    void reset();
    void shoot();

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Sound _soundShoot;
    common::Resolution _resolution;
    float _distanceFromCentre;
    float _angle;
    float _angleOrientation;
    float _scale;
    sf::Vector2<float> _prevPosition,
                        _newPosition,
                        _pointingPosition;
    textures::ID _id;
};

#endif //PROJECT_ENEMYSHIP_HPP