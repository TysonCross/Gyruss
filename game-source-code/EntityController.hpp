/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   controller and manager for game entity objects
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

using entityList = std::list<std::unique_ptr<Entity>>;
using bulletList = std::list<std::unique_ptr<Bullet>>;
using enemyList = std::list<std::unique_ptr<Enemy>>;
using explosionList = std::list<std::unique_ptr<Explosion>>;

class EntityController
{
public:
    EntityController(sf::Vector2i resolution,
                     PlayerShip &playerShip,
                     TextureHolder &textures);

    void spawnEnemies();
    void setMove();
    void shoot();
    void checkClipping();
    bool checkCollisions();
    void update();
    const void draw(sf::RenderWindow &renderWindow); // ToDo: remove
    const bool explosionOccurred();
    const bool shootingOccurred();
    void increaseGlobalSpeed(float amount);
    void decreaseGlobalSpeed(float amount);

#ifdef DEBUG
    void debug();
#endif // DEBUG


private:
    bool collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2);
    void checkEnemyToPlayerShipCollisions();

    PlayerShip& _playerShip;
    sf::Vector2i _resolution;
    TextureHolder& _textureHolder;
    bulletList _bulletsEnemy;
    bulletList _bulletsPlayer;
    enemyList _enemies;
    explosionList _explosions;
    sf::Clock _timerSpawn;
    sf::Clock _timerShoot;
    sf::Clock _totalTime;
    bool _explosionHasOccurred;
    bool _enemyShootEventHasOccurred;
    bool _playerHasBeenHit;
    float _speed_modifier;

    void checkEnemyBulletsToPlayerShipCollisions();

    void checkPlayerBulletsToEnemyCollisions();
};


#endif //PROJECT_ENTITYCONTROLLER_HPP
