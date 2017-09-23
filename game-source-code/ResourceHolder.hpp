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
    /// \param The key (ID) to load the resource for (defined in game.cpp)
    /// \param The file to load the resource from.
    ///
    /// \see Game.hpp
    ////////////////////////////////////////////////////////////
    void load(IdentifierType id, const std::string& filename);

    ////////////////////////////////////////////////////////////
    /// \brief Returns the resource object
    ///
    /// \param The key (ID) to load the resource for (defined in game.cpp)
    ////////////////////////////////////////////////////////////
    ResourceType& get(IdentifierType id);

    ////////////////////////////////////////////////////////////
    /// \brief Overloaded const method
    ///
    /// \param The key (ID) to load the resource for (defined in game.cpp)
    ////////////////////////////////////////////////////////////
    const ResourceType& get(IdentifierType id) const;

private:
    ////////////////////////////////////////////////////////////
    /// \brief internal method to insert the unique pointer into the private
    /// map member
    ///
    /// \param id The identifying key to load the resource for (defined in game.cpp)
    /// \param resource A unique pointer to the object containing the resource
    ///
    /// \see Game.hpp
    ////////////////////////////////////////////////////////////
    void insertResource(IdentifierType id, std::unique_ptr<ResourceType> resource);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::map<IdentifierType, std::unique_ptr<ResourceType>>  _resourceMap;
};

// Template classes need to be defined inline
#include "ResourceHolder.inl"

#endif //PROJECT_RESOURCEMAPPER_H