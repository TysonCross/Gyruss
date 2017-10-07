/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    7/10/17
/// \brief   Display and animatable Class
//////
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_ANIMATABLE_HPP
#define PROJECT_ANIMATABLE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include "ResourceHolder.hpp"

class Animatable
{
public:
    Animatable(const TextureHolder &textureHolder,
               const entity::ID type) : _type{type} {}

    virtual const sf::Sprite &getSprite()const=0;

protected:
    sf::Sprite _sprite;
    textures::ID _id;
    entity::ID _type;
    int _animationFPSLimit;

};


#endif //PROJECT_ANIMATABLE_HPP
