/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    7/10/17
/// \brief   Display and animatable Class
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_ANIMATABLE_HPP
#define PROJECT_ANIMATABLE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include "ResourceHolder.hpp"

using sf::Sprite;

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
    /// \see Entity
    /// \see common
    /// \see ResourceHolder
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
    virtual const Sprite &getSprite()const=0;

protected:
    ////////////////////////////////////////////////////////////
    /// \param The sprite object for the Entity
    ////////////////////////////////////////////////////////////
    Sprite _sprite;

    ////////////////////////////////////////////////////////////
    /// \param The unique ID identifying the texture for the Entity
    ////////////////////////////////////////////////////////////
    textures::ID _id;

    ////////////////////////////////////////////////////////////
    /// \param The ID identifying the Entity type
    ////////////////////////////////////////////////////////////
    entity::ID _type;

    ////////////////////////////////////////////////////////////
    /// \param If the tile-set is designed to be less than the game frame-rate, it can be limited here
    ////////////////////////////////////////////////////////////
    int _animationFPSLimit;

};

#endif //PROJECT_ANIMATABLE_HPP
