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

//#include "ResourceHolder.hpp"

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
                                                        const std::string& filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
    {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }
    insertResource(id, std::move(resource));
//    auto inserted = _resourceMap.insert(std::make_pair(id, std::move(resource)));
//    assert(inserted.second); //Only in Debug
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = _resourceMap.find(id);
    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = _resourceMap.find(id);
    return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
    // Insert and check success
    auto inserted = _resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

//    _resourceMap = {
//            {"Resolution",      {"1920","1080"}},
//            {"WindowIcon",      {"resources/icon.png"}},
//            {"StartSound",      {"resources/startup.ogg"}},
//            {"Music",           {"resources/game_music.ogg"}},
//            {"SplashScreen",    {"resources/splash.png"}},
//            {"PlayerShip",      {"resources/player_model.png"}},
//            {"PlayerShipSound", {"resources/ship_spawn.ogg","resources/shoot_laser.ogg"}},
//            {"EnemyShip",       {"resources/enemyship_grey.png","resources/enemyship_purple.png"}},
//            {"Bullet",          {"resources/bullet_player.png","resources/bullet_enemy.png"}}
//    };