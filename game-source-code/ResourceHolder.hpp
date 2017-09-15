/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/10
/// \brief   Loads and returns pointers to requested resources from file
///
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


template <typename Resource, typename Identifier>
class ResourceHolder
{
public:

    void load(Identifier id, const std::string& filename);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::map<Identifier, std::unique_ptr<Resource>>  _resourceMap;
};

// Template classes need to be defined inline
#include "ResourceHolder.inl"

#endif //PROJECT_RESOURCEMAPPER_H