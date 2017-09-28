/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    27/9/17
/// \brief   Description of file in project Project
///
/// Detailed description of file
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////




#ifndef PROJECT_SHIELD_HPP
#define PROJECT_SHIELD_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "common.hpp"
#include "ResourceHolder.hpp"
#include "PlayerShip.hpp"

class Shield
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class
    ///
    /// \param The screen resolution (to determine the radius
    /// the Shield circles around
    /// \param distanceFromCentre The fixed radius of the circle
    /// that the ship flies around
    /// \param angle The angle in degrees around the circle of movement
    /// \param scale The scale of the sprite
    /// \param type The entity::ID of the object
    /// \param textureHolder The resourceMapper object that
    /// contains the path to the texture(s) for the sprite
    /// \param playerShip The playerShip that the shield will be positioned on.
    ///
    ////////////////////////////////////////////////////////////
    Shield(const sf::Vector2i resolution,
           float distanceFromCentre,
           float angle,
           float scale,
           const entity::ID type,
           const TextureHolder &textureHolder,
           PlayerShip &playerShip);

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \see sf:Sprite
    ////////////////////////////////////////////////////////////
    const sf::Sprite &getSprite() const;
    void reset();
    void move();
    void update();

private:
    const sf::Vector2i _resolution;
    sf::Sprite _sprite;
    float _distanceFromCentre;
    float _angle;
    float _scale;
    textures::ID _id;
    entity::ID _type;
    PlayerShip &_playerShip;
    int _animationFPSLimit;
    sf::IntRect _rectArea;
    int _spriteOffset;
};


#endif //PROJECT_SHIELD_HPP
