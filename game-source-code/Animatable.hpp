/////////////////////////////////////////////////////////////////////
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
using sf::IntRect;

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
    /// \see [SFML/Texture](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Texture.php)
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

    ////////////////////////////////////////////////////////////
    /// \brief Sets the scale of the entity screen object
    ///
    /// \param scaleX The X scale of the enemy sprite
    /// \param scaleY The Y scale of the enemy sprite
    ////////////////////////////////////////////////////////////
    virtual void setScale(float scaleX, float scaleY){}

    ////////////////////////////////////////////////////////////
    /// \brief Sets the orientation of the entity screen object
    ///
    /// The previous and future positions are converted to vectors at the origin,
    /// and the final position is then subtracted from the initial position,
    /// to determine the new pointing vector. Then the sprite of the enemy is
    /// rotated to match this direction
    ////////////////////////////////////////////////////////////
    virtual void setOrientation(){}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the current rotation of the enemy sprite
    ///
    /// \return The angle of rotation of the sprite
    ////////////////////////////////////////////////////////////
    virtual const float getOrientationAngle() const
    { return _angleOrientation;}

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

    ////////////////////////////////////////////////////////////
    /// \param The animatable texture's active tile area
    ////////////////////////////////////////////////////////////
    IntRect _rectArea;

    ////////////////////////////////////////////////////////////
    /// \param The pixel offset of the _rectArea, moving the image from frame to frame
    ////////////////////////////////////////////////////////////
    int _spriteOffset;

    ////////////////////////////////////////////////////////////
    /// \param Stores the angle of orientation of the object
    ////////////////////////////////////////////////////////////
    float _angleOrientation;

};

#endif //PROJECT_ANIMATABLE_HPP
