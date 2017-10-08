/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Controller and manager for game entity objects
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_ENTITYCONTROLLER_HPP
#define PROJECT_ENTITYCONTROLLER_HPP

#include <list>
#include "common.hpp"
#include "ResourceHolder.hpp"
#include "Entity.hpp"
#include "PlayerShip.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Explosion.hpp"
#include "Meteoroid.hpp"
#include "Score.hpp"
#include "PerlinNoise.hpp"

using entityList = std::list<std::unique_ptr<Entity>>;
using bulletList = std::list<std::unique_ptr<Bullet>>;
using enemyList = std::list<std::unique_ptr<Enemy>>;
using explosionList = std::list<std::unique_ptr<Explosion>>;
using meteoroidList = std::list<std::unique_ptr<Meteoroid>>;

class EntityController
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor for the EntityController class. Called directly
    /// from game object to handel the creation, destruction and drawing of all game objects.
    ///
    /// On every game frame, respective functions are called to evaluate game entity states, such
    /// as spawning new enemies, collisions and enemy bullet shooting
    ///
    /// \param resolution The Screen resolution of the game
    /// \param playerShip The playership, generated from the game.cpp. needed for collision detection
    /// \param textures used to create new entities that require this class for creation
    /// \param score object to track the current game score, enemies killed and player deaths. created in game.cpp
    /// \param speedModifier defines how fast the game runs at a particular time to speed up game as time progresses
    ///////////////////////////////////////////////////////////////
    EntityController(sf::Vector2i resolution,
                     PlayerShip &playerShip,
                     TextureHolder &textures,
                     Score &score,
                     float speedModifier);

    ////////////////////////////////////////////////////////////
    /// \brief Spawns an enemy of a defined id and variant in a spiral direction(movementState)
    /// function is called from spawnEntities
    ///
    /// This function includes: spiral inwards, spiral outwards and wandering movement
    ///
    /// \param id defines the kind of ship spawned
    /// \param shipVariant defines the look of the ship spawned
    /// \param movementDirection enum, showing clockwise or counterclockwise ship direction
    /// \param movementState spesifies what kind of spiral the ship is doing: inwards, outwards or wandering
    ///
    /// \see Enemy.hpp
    ////////////////////////////////////////////////////////////
    void spawnSpiral(entity::ID id,
                     textures::ID shipVariant,
                     MovementDirection movementDirection,
                     MovementState movementState);

    ////////////////////////////////////////////////////////////
    /// \brief Spawns a meteoroid
    /// function is called from spawnEntities
    ///
    /// \see Meteorid.hpp
    ////////////////////////////////////////////////////////////
    void spawnMeteoroid();

    ////////////////////////////////////////////////////////////
    /// \brief Spawns a Satellite, a type of Enemy.
    /// function is called from spawnEntities
    ///
    /// \see Enemy.hpp
    ////////////////////////////////////////////////////////////
    void spawnSatellites();

    ////////////////////////////////////////////////////////////
    /// \brief inititates the spawn event for enemies, satellites and meteroids
    ///
    /// Defines the spawn chances based on a combination of delay between spawns
    /// and random event chances. Has imposed maximum & minimum number of enemys
    /// that can be alive at one time
    ///
    /// \see Enemy.hpp
    /// \see spawnMeteoroid
    /// \see spawnSatellites
    /// \see spawnSpiral
    /// \see Enemy.hpp
    /// \see Meteorid.hpp
    ////////////////////////////////////////////////////////////
    void spawnEntities();

    ////////////////////////////////////////////////////////////
    /// \brief initiates a player shoot event based on current gun level
    /// and adds bullet to bullet vector
    ///
    /// \see PlayerShip.hpp
    ////////////////////////////////////////////////////////////
    void playerShoot();

    ////////////////////////////////////////////////////////////
    /// \brief initiates a player shoot event based on current gun level
    /// and adds bullet to bullet vector
    ///
    /// \see playerShoot
    ////////////////////////////////////////////////////////////
    void shoot();

    void setMove();
    void preformEnemyMove(std::unique_ptr<Enemy> &enemy,
                          MovementState currentEnemyMovementState,
                          float growShipScreenZone,
                          float currentEnemyRadius);


    void checkClipping();
    bool checkCollisions();
    bool collides(const sf::Sprite &sprite1,
                  const sf::Sprite &sprite2);
    void update();
    const void draw(sf::RenderWindow &renderWindow);
    
    const bool explosionOccurred();
    const bool shootingOccurred();

    void changeGlobalSpeed(float amount);
    void resetGlobalSpeed();

    const float getSpeed() const;
    void killAllEnemiesOfType(entity::ID type);

private:
    void checkEnemyToPlayerShipCollisions();
    void checkEnemyBulletsToPlayerShipCollisions();
    void checkPlayerBulletsToEnemyCollisions();
    void checkMeteoroidToPlayerShipCollisions();
    void checkPlayerBulletsToMeteoroidCollisions();
    void enemyKilled(entity::ID type);
    void upgradePlayerShip();

    PlayerShip& _playerShip;
    sf::Vector2i _resolution;
    TextureHolder& _textureHolder;
    bulletList _bulletsEnemy;
    bulletList _bulletsPlayer;
    enemyList _enemies;
    explosionList _explosions;
    meteoroidList _meteoroids;
    sf::Clock _timerSpawnFromPerimeter;
    sf::Clock _timerSpawnFromCentre;
    sf::Clock _timerSatellite;
    sf::Clock _timerMeteoroid;
    sf::Clock _totalTime;
    Score& _score;
    bool _explosionHasOccurred;
    bool _enemyShootEventHasOccurred;
    bool _playerHasBeenHit;
    float _speedModifier;
    float _defaultSpeed;
    int _satellitesAlive;
    float _bulletPlayerSpeed;
    float _bulletEnemySpeed;
    float _meteoroidSpeed;
    PerlinNoise _xNoise;
    PerlinNoise _yNoise;
};

#endif //PROJECT_ENTITYCONTROLLER_HPP
