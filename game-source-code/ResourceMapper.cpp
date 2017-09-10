//
// Created by chris on 2017/09/10.
//

#include "ResourceMapper.hpp"
#include <iostream>

ResourceMapper::ResourceMapper() {
    _resourceMap = {
            {"Resolution",      {"1920","1080"}},
            {"WindowIcon",      {"resources/icon.png"}},
            {"Star",            {"resources/star.png"}},
            {"SplashScreen",    {"resources/splash.png"}},
            {"PlayerShip",      {"resources/player_model.png"}}

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