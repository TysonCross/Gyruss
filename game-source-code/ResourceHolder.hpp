/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/10
/// \brief   Loads and returns pointers to requested resources from file
///
/// Maps game resources from a key to set of values
/// Used for determining texture paths, game resolution, etc.
/// Based on examples from SFML Game Development by Jan Haller
/// https://github.com/LaurentGomila/SFML-Game-Development-Book
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_RESOURCEMAPPER_H
#define PROJECT_RESOURCEMAPPER_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include "common.hpp"

using std::string;
using std::unique_ptr;
using std::move;

////////////////////////////////////////////////////////////
/// \brief The ResourceType class
///
/// A mechanism to load all game art resources (textures, sounds and fonts) from disk,
/// and to transfer the ownership of the unique_ptr to the object calling get()
/// Several specific types are declared in common.hpp, TextureHolder, FontHolder and SoundHolder
///
/// \see common
////////////////////////////////////////////////////////////
template <typename ResourceType, typename IdentifierType>
class ResourceHolder
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Loads a resource from file into memory, using a key/pair
    /// relationship to map onto a pointer to the object which holds the file information.
    ///
    /// The load() method loads the file into an object of specifed type,
    /// transferring ownership of the resource to the private map container member _resourceMap/
    ///
    /// \param id The key (ID) to load the resource for (defined in common)
    /// \param filename The file to load the resource from.
    ///
    /// \see Game
    ////////////////////////////////////////////////////////////
    void load(IdentifierType id, const string &filename);

    ////////////////////////////////////////////////////////////
    /// \brief Returns the resource object
    ///
    /// \param id The key (ID) to load the resource for (defined in common)
    /// \return An object of type resourceType (usually sf::Texture, sf::SoundBuffer or sf::Font
    ////////////////////////////////////////////////////////////
    ResourceType& get(IdentifierType id);

    ////////////////////////////////////////////////////////////
    /// \brief Overloaded const method
    ///
    /// \param id The key (ID) to load the resource for (defined in common)
    /// \return An object of type resourceType (usually sf::Texture, sf::SoundBuffer or sf::Font
    ////////////////////////////////////////////////////////////
    const ResourceType &get(IdentifierType id) const;

private:
    ////////////////////////////////////////////////////////////
    /// \brief internal method to insert the unique pointer into the private
    /// map member
    ///
    /// \param id The identifying key to load the resource for (defined in common)
    /// \param resource A unique pointer to the object containing the resource
    ///
    /// \see common
    ////////////////////////////////////////////////////////////
    void insertResource(IdentifierType id, std::unique_ptr<ResourceType> resource);

    ////////////////////////////////////////////////////////////
    /// \brief Mapping of the resource to a unique pointer
    ////////////////////////////////////////////////////////////
    std::map<IdentifierType, unique_ptr<ResourceType>>  _resourceMap;
};

// Template classes need to be defined inline
#include "ResourceHolder.inl"

#endif //PROJECT_RESOURCEMAPPER_H