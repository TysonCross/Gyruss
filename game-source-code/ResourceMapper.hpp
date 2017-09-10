/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    ResourceMapper.hpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/10
/// \brief   Relational, unstructured mapping from key to vector of values
///
/// Maps game resources from a key to set of values
/// Used for determining texture paths, game resolution, etc.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_RESOURCEMAPPER_H
#define PROJECT_RESOURCEMAPPER_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <map>

using resourceMap = std::map<std::string, std::vector<std::string> >;


class ResourceMapper
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constuctor
    ///
    /// Creates a speficic database of string keys, and a vector of string values
    ///
    ////////////////////////////////////////////////////////////
    ResourceMapper();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the resource map
    ///
    ////////////////////////////////////////////////////////////
    const resourceMap getResourceMap() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the vactor of values at a key entry
    ///
    /// \param resource The key for the mapping to return the values for
    ///
    ////////////////////////////////////////////////////////////
    const std::vector<std::string> getResourceValues(std::string resource) const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns the vactor of values at a key entry
    ///
    /// \param resource The key for the mapping to return for,
    /// This method returns only the first value in the vector
    ///
    ////////////////////////////////////////////////////////////
    const std::string getResource(std::string resource) const;

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    resourceMap _resourceMap;
};

#endif //PROJECT_RESOURCEMAPPER_H