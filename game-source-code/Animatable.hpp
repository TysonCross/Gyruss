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

////////////////////////////////////////////////////////////
/// \brief A component of the main Entity class for game objects
///
/// This class provides the basic interface for texturable objects,
/// identified by an ID type. A texture holder object provides a
/// mechanism for loading textures (tilesets in the case of animating sprites)
/// as a unique_ptr of type sf::Texture
////////////////////////////////////////////////////////////
class Animatable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor for Animatable class
    ///
    /// \param textureHolder The textureHolder object, passed by const ref.
    /// provides a unique_ptr to an sf::Texture for the sprite data member
    ///
    /// \param type An enum that identifies the Entity type. Defined in common.hpp
    ///
    /// \see Entity.hpp
    /// \see common.hpp
    /// \see ResourceHolder.hpp
    /// \see sf::Texture
    ////////////////////////////////////////////////////////////
    Animatable(const TextureHolder &textureHolder,
               const entity::ID type) : _type{type} {}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object.
    ///
    /// A pure virtual method for returning the sprite object.
    ///
    /// \return The method returns the private data member _sprite
    ////////////////////////////////////////////////////////////
    virtual const sf::Sprite &getSprite()const=0;

protected:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    /// \param The sprite object for the Entity
    sf::Sprite _sprite;
    /// \param The unique ID identifying the texture for the Entity
    textures::ID _id;
    /// \param The ID identofying the Entity yype
    entity::ID _type;
    /// \param If the tileset is designed to be less than the game framerate, it can be limited here
    int _animationFPSLimit;

};


#endif //PROJECT_ANIMATABLE_HPP
