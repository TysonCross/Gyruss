/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    ResourceMapper.cpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/10
/// \brief   Relational, unstructured mapping from key to vector of values
///
/// Maps game resources from a key to set of values
/// Used for determining texture paths, game resolution, etc.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "ResourceMapper.hpp"
#include <iostream>

ResourceMapper::ResourceMapper() {
    _resourceMap = {
            {"Resolution",      {"1920","1080"}},
            {"WindowIcon",      {"resources/icon.png"}},
            {"Star",            {"resources/star.png"}},
            {"SplashScreen",    {"resources/splash.png"}},
            {"PlayerShip",      {"resources/player_model.png"}},
            {"PlayerShipSound", {"resources/shoot_laser.ogg"}},
            {"StartSound",      {"resources/shield_up.ogg"}}
    };
}

const resourceMap ResourceMapper::getResourceMap() const
{
    return _resourceMap;
}

const std::vector<std::string> ResourceMapper::getResourceValues(std::string resourceName) const
{
    return _resourceMap.at(resourceName);
};

const std::string ResourceMapper::getResource(std::string resourceName) const
{
    return _resourceMap.at(resourceName).at(0);
}