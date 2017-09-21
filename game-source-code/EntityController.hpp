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
#include "EntityPlayerShip.hpp"
#include "EntityEnemy.hpp"
#include "EntityBullet.hpp"
#include "EntityExplosion.hpp"

using entityList = std::list<std::unique_ptr<Entity>>;
using bulletList = std::list<std::unique_ptr<EntityBullet>>;
using enemyList = std::list<std::unique_ptr<EntityEnemy>>;
using explosionList = std::list<std::unique_ptr<EntityExplosion>>;
using clockVector = std::vector<std::unique_ptr<sf::Clock>>;

class EntityController
{
public:
    EntityController();
    EntityController(sf::Vector2i resolution,
                     float playerShipPathRadius,
                     float playerShipScale,
                     TextureHolder& textures,
                     SoundHolder& sounds);

    void spawnEnemies();
    void tellPlayerShipToShoot();
    void tellPlayerShipToMove(float distance);
    const int getPlayerLives();
    void setMove();
    void shoot();
    void checkClipping();
    bool checkCollisions();
    void update();
    void draw(sf::RenderWindow &renderWindow); // ToDo: remove
#ifdef DEBUG
    void debug();
#endif // DEBUG


private:
    bool collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2);
    void generateEntities(int number_enemies,
                          int number_bullets_enemy,
                          int number_bullets_player,
                          int number_explosions);

//    template <typename T>
//    void generateEntities<T>(int number_entities,std::list<std::unique_ptr<T>>);

//    void generateEnemies(int number_enemies);
//    void generateBullets(int number_bullets_enemy);
//    void generatePlayerBullets(int number_nullets_player);
//    void generateExplosions(int number_explosions);

    sf::Vector2i _resolution;
    TextureHolder& _textureHolder;
    SoundHolder& _soundHolder;
    EntityPlayerShip _playerShip;
    bulletList _bulletsEnemyActive;
    bulletList _bulletsEnemyInactive;
    bulletList _bulletsPlayerActive;
    bulletList _bulletsPlayerInactive;
    enemyList _enemiesActive;
    enemyList _enemiesInactive;
    explosionList _explosionsActive;
    explosionList _explosionsInactive;
    sf::Clock _timerSpawn;
    sf::Clock _timerShoot;
};


#endif //PROJECT_ENTITYCONTROLLER_HPP
