/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   controller and manager for game entity objects
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "EntityController.hpp"
#include <iostream>

EntityController::EntityController(sf::Vector2i resolution,
                                   float playerShipPathRadius,
                                   float playerShipScale,
                                   TextureHolder &textureHolder, // ToDo: remove, along with Sounds
                                   SoundHolder &soundHolder) : _playerShip(resolution,
                                                                           playerShipPathRadius,
                                                                           0,
                                                                           playerShipScale,
                                                                           textureHolder,
                                                                           soundHolder),
                                                               _resolution(resolution),
                                                               _textureHolder(textureHolder), // ToDo: remove
                                                               _soundHolder(soundHolder) // ToDo: remove
{
    const int number_enemies = 50;
    const int number_bullets_enemy = 100;
    const int number_bullets_player = 60;
    const int number_explosions = 100;

    // Generate timers for the enemy spawning and shooting
    _timerSpawn.restart();
    _timerShoot.restart();

    // Generate pool of basic enemies, made up from either the two variants
    for (auto i = 0; i < number_enemies; i++)
    {
        auto shipVariant = static_cast<textures::ID>(rand()%2);
        auto enemy = std::make_unique<EntityEnemy>(_resolution,
                                                   0, 0, 1,
                                                   _textureHolder, // ToDo: remove
                                                   _soundHolder, // ToDo: remove
                                                   shipVariant);
        _enemiesInactive.push_front(std::move(enemy));
    }

    // Generate pool of player bullets
    for (auto i = 0; i < number_bullets_player; i++)
    {
        auto bullet = std::make_unique<EntityBullet>(_resolution,
                                                     0, 0, 1,
                                                     _textureHolder, // ToDo: remove
                                                     textures::BulletPlayer);
        _bulletsPlayerInactive.push_front(std::move(bullet));
    }

    // Generate pool of enemy bullets
    for (auto i = 0; i < number_bullets_enemy; i++)
    {
        auto bullet = std::make_unique<EntityBullet>(_resolution,
                                                     0, 0, 1,
                                                     _textureHolder, // ToDo: remove
                                                     textures::BulletEnemy);
        _bulletsEnemyInactive.push_front(std::move(bullet));
    }

    // Generate pool of explosions
    for (auto i = 0; i < number_explosions; i++)
    {
        auto explosion = std::make_unique<EntityExplosion>(_resolution,
                                                           0, 0, 1,
                                                           _textureHolder, // ToDo: remove
                                                           _soundHolder, // ToDo: remove
                                                           textures::Explosion);
        _explosionsInactive.push_front(std::move(explosion));
    }
}

void EntityController::spawnEnemies()
{
    float enemySpawnTime = rand()%3 + 2;
    if (_timerSpawn.getElapsedTime().asSeconds() > enemySpawnTime)
    {
        _timerSpawn.restart();
        _enemiesActive.push_front(std::move(_enemiesInactive.front()));
        _enemiesInactive.pop_front();
    }
}

void EntityController::tellPlayerShipToShoot()
{
   _playerShip.setShoot();
}

void EntityController::tellPlayerShipToMove(float distance)
{
    _playerShip.setMove(distance);
}

void EntityController::shoot()
{
    if (_playerShip.isShooting())
    {
        _bulletsPlayerActive.push_front(std::move(_bulletsPlayerInactive.front()));
        _bulletsPlayerInactive.pop_front();
        _bulletsPlayerActive.front()->reset();
        _bulletsPlayerActive.front()->setMove(_playerShip.getAngle(),
                                              _playerShip.getDistanceFromCentre());
    }

    float enemyShootTime = (rand() % 2000 + 100);
    for (auto &enemy : _enemiesActive)
    {
        if (_timerShoot.getElapsedTime().asMilliseconds() > enemyShootTime)
        {
            _timerShoot.restart();

            _bulletsEnemyActive.push_front(std::move(_bulletsEnemyInactive.front()));
            _bulletsEnemyInactive.pop_front();

            _bulletsEnemyActive.front()->setMove(enemy->getDistanceFromCentre(),
                                                 enemy->getAngle());
        }
    }
}

const int EntityController::getPlayerLives()
{
    return _playerShip.getLives();
}


void EntityController::setMove()
{
    // Reset enemies outside cylindrical frustum back to the centre, otherwise, set their moves
    for (auto &enemy : _enemiesActive)
    {
        if (enemy->getRadius() > _resolution.y / 2.f)
        {
            auto random_angle = (rand() % 3 + 2.0f);
            auto random_move = rand() % 10 + (-2);
            auto playableZoneRadiusFactor = 8;
            if (enemy->getDistanceFromCentre() < _resolution.y / playableZoneRadiusFactor)
            {
                enemy->setMove(1 + random_angle, 18);
            } else
            {
                enemy->setMove(random_angle, random_move);
            }
        } else
            enemy->reset();
    }
}

void EntityController::checkClipping()
{
    // Clip away enemy bullets outside cylindrical frustum
    for (auto bullet = _bulletsEnemyActive.begin(); bullet != _bulletsEnemyActive.end();)
    {
        if ((*bullet)->getRadius() > _resolution.y / 2.f)
        {
            _bulletsEnemyInactive.splice(_bulletsEnemyInactive.begin(), _bulletsEnemyActive, bullet++);
        } else
            bullet++;
    }

    // Clip away player bullets at centre
    auto radius_buffer = 10; // should be smaller than playableZoneRadiusFactor above
    for (auto bullet = _bulletsPlayerActive.begin(); bullet != _bulletsPlayerActive.end();)
    {
        if (((*bullet)->getPosition().x > (_resolution.x / 2) - radius_buffer)
            && ((*bullet)->getPosition().y > (_resolution.y / 2) - radius_buffer)
            && ((*bullet)->getPosition().x < (_resolution.x / 2) + radius_buffer)
            && ((*bullet)->getPosition().y < (_resolution.y / 2) + radius_buffer))
        {
            _bulletsPlayerInactive.splice(_bulletsPlayerInactive.begin(), _bulletsPlayerActive, bullet++);
        } else
            bullet++;
    }

    // Remove any finished explosions
    for (auto explosion = _explosionsActive.begin(); explosion != _explosionsActive.end();)
    {
        if ((*explosion)->getLives() == 0) // ToDo: Make boolean, is_finished
        {
            _explosionsInactive.splice(_explosionsInactive.begin(), _explosionsActive, explosion++);

        } else
            explosion++;
    }
}


bool EntityController::checkCollisions()
{
    bool player_is_hit = false;

    // Enemy -> PlayerShip
    for( auto enemy = _enemiesActive.begin(); enemy != _enemiesActive.end();)
    {
        if (collides(_playerShip.getSprite(), (*enemy)->getSprite()))
        {
            _explosionsActive.push_front(std::move(_explosionsInactive.front()));
            _explosionsInactive.pop_front();
            _explosionsActive.front()->setMove(_playerShip.getDistanceFromCentre(),
                                               _playerShip.getAngle());

            _enemiesInactive.splice(_enemiesInactive.begin(), _enemiesActive, enemy++);
            player_is_hit = true;
        }
        else
            enemy++;
    }

    // EnemyBullets -> EntityPlayerShip
    for( auto bullet = _bulletsEnemyActive.begin(); bullet != _bulletsEnemyActive.end();)
    {
        if (collides(_playerShip.getSprite(), (*bullet)->getSprite()))
        {
            _explosionsActive.push_front(std::move(_explosionsInactive.front()));
            _explosionsInactive.pop_front();
            _explosionsActive.front()->setMove(_playerShip.getDistanceFromCentre(),
                                               _playerShip.getAngle());
            player_is_hit = true;
            _bulletsEnemyInactive.splice(_bulletsEnemyInactive.begin(), _bulletsEnemyActive, bullet++);

        } else
            bullet++;

    }

    // PlayerBullets -> Enemy
    for( auto enemy = _enemiesActive.begin(); enemy != _enemiesActive.end(); ++enemy)
    {
        for( auto bullet = _bulletsPlayerActive.begin(); bullet != _bulletsPlayerActive.end();)
        {
            if (collides((*bullet)->getSprite(), (*enemy)->getSprite()))
            {
                _bulletsPlayerInactive.splice(_bulletsPlayerInactive.begin(),_bulletsPlayerActive,bullet++);
                (*enemy)->die();
            } else
                bullet++;
        }
    }

    // Process Enemy death events from PlayerBullets collisions above
    for( auto enemy = _enemiesActive.begin(); enemy != _enemiesActive.end();)
    {
        if ((*enemy)->getLives() == 0)
        {
            _enemiesInactive.splice(_enemiesInactive.begin(), _enemiesActive, enemy++);

            _explosionsActive.push_front(std::move(_explosionsInactive.front()));
            _explosionsInactive.pop_front();
            _explosionsActive.front()->setMove((*enemy)->getDistanceFromCentre(),
                                               (*enemy)->getAngle());
            _explosionsActive.front()->getSprite().setScale((*enemy)->getScale().x * 2,
                                                            (*enemy)->getScale().y * 2);
        } else
            enemy++;
    }

    if (player_is_hit) _playerShip.die();
    return player_is_hit;
}


void EntityController::update()
{
    _playerShip.update();

    for (auto &enemy : _enemiesActive)
        enemy->update();

    for (auto &bullet : _bulletsPlayerActive)
    {
        bullet->update();
        bullet->setMove(-25);
    }

    for (auto &bullet : _bulletsEnemyActive)
    {
        bullet->update();
        bullet->setMove(20);
    }

    for (auto &explosion : _explosionsActive)
        explosion->update();
}

bool EntityController::collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
{
    auto shrink_factor = 4.f + 0.2f;
    float radius_1 = (sprite1.getGlobalBounds().width + sprite1.getGlobalBounds().height) / shrink_factor;
    float radius_2 = (sprite2.getGlobalBounds().width + sprite2.getGlobalBounds().height) / shrink_factor;
    float distance_x = sprite1.getPosition().x - sprite2.getPosition().x;
    float distance_y = sprite1.getPosition().y - sprite2.getPosition().y;

    return  radius_1 + radius_2 >= sqrt((distance_x * distance_x) + (distance_y * distance_y));
}
void EntityController::draw(sf::RenderWindow &renderWindow)
{

    for (auto &enemy : _enemiesActive)
        renderWindow.draw(enemy->getSprite());

    for (auto &bullet : _bulletsEnemyActive)
        renderWindow.draw(bullet->getSprite());

    for (auto &bullet : _bulletsPlayerActive)
        renderWindow.draw(bullet->getSprite());

    for (auto &explosion : _explosionsActive)
        renderWindow.draw(explosion->getSprite());

    renderWindow.draw(_playerShip.getSprite());

}
#ifdef DEBUG

void EntityController::debug()
{
    auto size_player_bullets = std::distance(_bulletsPlayerActive.begin(), _bulletsPlayerActive.end());
    auto size_enemy_bullets = std::distance(_bulletsEnemyActive.begin(), _bulletsEnemyActive.end());
    if (size_enemy_bullets > 0)
        std::cout << "Enemy Bullets active: " << size_enemy_bullets << std::endl;
    if (size_player_bullets > 0)
        std::cout << "Player Bullets active: " << size_player_bullets << std::endl;
}
#endif // DEBUG