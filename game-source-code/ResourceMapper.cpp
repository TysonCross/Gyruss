//
// Created by chris on 2017/09/10.
//

#include "ResourceMapper.hpp"
#include <iostream>

ResourceMapper::ResourceMapper() {
    _resourceMap = {
            {"SplashBackground", {"resources/splash.png"}},
            {"ShipSprite",       {"resources/player_model.png"}}
    };
}

const std::map<std::string, std::vector<std::string>> ResourceMapper::getResourceMap() const
{
    return _resourceMap;
};

const std::string ResourceMapper::getResource(std::string resourceName) const
{
    return _resourceMap.at(resourceName).at(0);
}