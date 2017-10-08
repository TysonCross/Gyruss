/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/10
/// \brief  Inline template class implementations for ResourceHolder
///
/// Maps game resources from a key to set of values
/// Used for determining texture paths, game resolution, etc.
/// Based on examples from SFML Game Development by Jan Haller
/// https://github.com/LaurentGomila/SFML-Game-Development-Book
/////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Loads the resource from a file on disk
///
/// \param id An identifying key to load the resource for (defined in common.hpp)
/// \param filename A string to the name of the file on disk to be loaded
////////////////////////////////////////////////////////////
template <typename ResourceType, typename IdentifierType>
void ResourceHolder<ResourceType, IdentifierType>::load(IdentifierType id,
                                                        const string &filename)
{
    std::unique_ptr<ResourceType> resource(new ResourceType());
    if (!resource->loadFromFile(filename))
    {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }
    auto inserted = _resourceMap.insert(std::make_pair(id, move(resource)));
    assert(inserted.second); //Only in Debug
}

////////////////////////////////////////////////////////////
/// \brief Transfers the unique pointer to the requesting object
///
/// \param id An identifying key to load the resource for (defined in common.hpp)
////////////////////////////////////////////////////////////
template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = _resourceMap.find(id);
    return *found->second;
}

////////////////////////////////////////////////////////////
/// \brief Transfers the unique pointer to the requesting object with a const overloaded method
///
/// \param id An identifying key to load the resource for (defined in common.hpp)
////////////////////////////////////////////////////////////
template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = _resourceMap.find(id);
    return *found->second;
}

