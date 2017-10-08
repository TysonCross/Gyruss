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
    EntityController(sf::Vector2i resolution,
                     PlayerShip &playerShip,
                     TextureHolder &textures,
                     Score &score,
                     float speedModifier);

    void spawnEntities();
    void setMove();
    void shoot();
    void playerShoot();
    void checkClipping();
    bool checkCollisions();
    bool collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2);
    void update();
    const void draw(sf::RenderWindow &renderWindow); // ToDo: remove
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

    void spawnSpiral(entity::ID id, textures::ID shipVariant, MovementDirection movementDirection, MovementState movementState);
    void spawnMeteoroid();
    void spawnSatellites();

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
