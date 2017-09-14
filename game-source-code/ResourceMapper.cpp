/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \file    ResourceMapper.cpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/10
/// \brief   Relational, unstructured mapping from key to vector of values
///
/// Maps game resources from a key to set of values
/// Used for determining texture paths, game resolution, etc.
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
///
/// \copyright Free Game Art Assets from http://kenney.nl
/// Royalty free Music by Music by Eric Matyas from http://soundimage.org

/////////////////////////////////////////////////////////////////////

#include "ResourceMapper.hpp"

ResourceMapper::ResourceMapper() {
    _resourceMap = {
            {"Resolution",      {"1920","1080"}},
            {"WindowIcon",      {"resources/icon.png"}},
            {"StartSound",      {"resources/startup.ogg"}},
            {"Music",           {"resources/game_music.ogg"}},
            {"Star",            {"resources/star.png"}},
            {"SplashScreen",    {"resources/splash.png"}},
            {"PlayerShip",      {"resources/player_model.png"}},
            {"PlayerShipSound", {"resources/shoot_laser.ogg"}},
            {"StartSound",      {"resources/shield_up.ogg"}},
            {"PlayerBullet",    {"resources/player_bullet.png"}},
            {"EnemyBullet",     {"resources/enemy_bullet.png"}}
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