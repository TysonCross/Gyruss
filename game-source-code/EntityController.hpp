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
using clockVector = std::vector<std::unique_ptr<sf::Clock>>;

class EntityController
{
public:
    EntityController();
    EntityController(sf::Vector2i resolution,
                     PlayerShip &playerShip,
                     TextureHolder &textures);

    void spawnEnemies();
    void setMove();
    void shoot(PlayerShip &playerShip);
    void checkClipping();
    bool checkCollisions(PlayerShip &playerShip);
    void update();
    void draw(sf::RenderWindow &renderWindow); // ToDo: remove
    bool explosionOccurred();
    bool shootingOccurred();
    void increaseGlobalSpeed(float amount);
    void decreaseGlobalSpeed(float amount);

#ifdef DEBUG
    void debug();
#endif // DEBUG


private:
    bool collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2);
//    void generateEntities(int number_enemies,
//                          int number_bullets_enemy,
//                          int number_bullets_player,
//                          int number_explosions);

//    template <typename T>
//    void generateEntities<T>(int number_entities,std::list<std::unique_ptr<T>>);

//    void generateEnemies(int number_enemies);
//    void generateBullets(int number_bullets_enemy);
//    void generatePlayerBullets(int number_bullets_player);
//    void generateExplosions(int number_explosions);

    sf::Vector2i _resolution;
    TextureHolder& _textureHolder;
    bulletList _bulletsEnemy;
    bulletList _bulletsPlayer;
    enemyList _enemies;
    explosionList _explosions;
    sf::Clock _timerSpawn;
    sf::Clock _timerShoot;
    bool _explosionEvent;
    bool _shootEvent;
    float _speed_modifier;
};


#endif //PROJECT_ENTITYCONTROLLER_HPP
