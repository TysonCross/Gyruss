/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   controller and manager for game entity objects
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "EntityController.hpp"
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

EntityController::EntityController(sf::Vector2i resolution,
                                   PlayerShip &playerShip,
                                   TextureHolder &textureHolder) : _resolution(resolution),
                                                                   _playerShip(playerShip),
                                                                   _textureHolder(textureHolder) // ToDo: remove
{
    // Reset timers for the enemy spawning and shooting
    _timerSpawn.restart();
    _timerShoot.restart();
    _totalTime.restart();
    _explosionHasOccurred = false;
    _speed_modifier = 0.75f;
}

void EntityController::spawnEnemies()
{
    // Initial delay before first enemies spawn.
    if (_totalTime.getElapsedTime().asSeconds() > 1)
    {
        int minNumberEnemies = 2;
        float enemySpawnTime = rand() % 3 + 2;
        if ((_timerSpawn.getElapsedTime().asSeconds() > enemySpawnTime)
            || (_enemies.size() <= minNumberEnemies))
        {
            _timerSpawn.restart();
            auto shipVariant = static_cast<textures::ID>(rand() % 1);
            auto enemy = std::make_unique<Enemy>(_resolution,
                                                 0, 0, 0.5,
                                                 _textureHolder, // ToDo: remove
                                                 shipVariant);
            _enemies.push_front(std::move(enemy));
        }
    }
}

void EntityController::shoot()
{
    if (_playerShip.isShooting())
    { auto bullet = std::make_unique<Bullet>(_resolution,
                                                   _playerShip.getDistanceFromCentre(),
                                                   _playerShip.getAngle(),
                                                   0.5,
                                                   _textureHolder,
                                                   textures::BulletPlayer);
        _bulletsPlayer.push_front(std::move(bullet));
    }

    _enemyShootEventHasOccurred = false;
    auto minNumberEnemyBullets = 1;
    auto dontFireInsideThisRadius = (_resolution.y/2)*0.05; // only shoot when closer
    float enemyShootTime = (rand()% 9000 + 500); // In Milliseconds
    for (auto &enemy : _enemies)
    {
        if (enemy->getDistanceFromCentre() > dontFireInsideThisRadius)
        {
            if ((_timerShoot.getElapsedTime().asMilliseconds() > enemyShootTime)
                || (_bulletsEnemy.size() <= minNumberEnemyBullets))
            {
                _timerShoot.restart();
                auto bullet_enemy = std::make_unique<Bullet>(_resolution,
                                                             enemy->getDistanceFromCentre(),
                                                             enemy->getAngle(),
                                                             0.5,
                                                             _textureHolder,
                                                             textures::BulletEnemy);
                _bulletsEnemy.push_front(std::move(bullet_enemy));
                _enemyShootEventHasOccurred = true;
            }
        }
    }
}

const bool EntityController::shootingOccurred()
{
    return _enemyShootEventHasOccurred;
}
void EntityController::setMove()
{
    // Reset enemies outside cylindrical frustum back to the centre. Otherwise, set up the
    // future enemy movement (and move faster - immediately after spawning - to get closer to the player)
    for (auto &enemy : _enemies)
    {
        if (enemy->getRadius() > _resolution.y / 2.f)
        {
            auto random_angle = (rand() % 3 + 2.0f);
            auto random_move = rand() % 15 + (-2);
            auto playableZoneRadiusFactor = 8;

            if (enemy->getDistanceFromCentre() < (_resolution.y / playableZoneRadiusFactor))
            {
                enemy->setMove(1 + random_angle, 15*_speed_modifier);
            } else
            {
                enemy->setMove(random_angle, random_move*_speed_modifier);
            }
        } else
            enemy->reset();
    }
}

bool EntityController::checkCollisions()
{
    _explosionHasOccurred = false;
    _playerHasBeenHit = false;

    checkEnemyToPlayerShipCollisions();
    checkEnemyBulletsToPlayerShipCollisions();
    checkPlayerBulletsToEnemyCollisions();

    return _playerHasBeenHit;
}

void EntityController::checkPlayerBulletsToEnemyCollisions()
{// PlayerBullets -> Enemy (enemy explodes, playerbullet disappears)
    for(auto enemy = _enemies.begin(); enemy != _enemies.end(); ++enemy)
    {
        for(auto bullet = _bulletsPlayer.begin(); bullet != _bulletsPlayer.end();)
        {
            if (collides((*bullet)->getSprite(), (*enemy)->getSprite()))
            {
                auto explosion = std::make_unique<Explosion>(_resolution,
                                                                  (*enemy)->getDistanceFromCentre(),
                                                                  (*enemy)->getAngle(),
                                                                   (*enemy)->getScale().x * 2,
                                                                  _textureHolder,
                                                                  textures::Explosion);
                _explosions.push_back(std::move(explosion));
                bullet = _bulletsPlayer.erase(bullet);
                (*enemy)->die();
                _explosionHasOccurred = true;
            } else
                bullet++;
        }
    }

    // Process Enemy death events from PlayerBullets collisions above
    for(auto enemy = _enemies.begin(); enemy != _enemies.end();)
    {
        if ((*enemy)->getLives() == 0)
        {
            enemy = _enemies.erase(enemy);
        } else
            enemy++;
    }
}

void EntityController::checkEnemyBulletsToPlayerShipCollisions()
{// EnemyBullets -> PlayerShip (player explodes + dies, bullet disappears)
    for(auto bullet = _bulletsEnemy.begin(); bullet != _bulletsEnemy.end();)
    {
        if (collides(_playerShip.getSprite(), (*bullet)->getSprite()))
        {
            auto explosion = std::make_unique<Explosion>(_resolution,
                                                              _playerShip.getDistanceFromCentre(),
                                                              _playerShip.getAngle(),
                                                              _playerShip.getScale().x * 2,
                                                              _textureHolder,
                                                              textures::Explosion);
            _explosions.push_back(std::move(explosion));
            bullet = _bulletsEnemy.erase(bullet);
            if (!_playerShip.isInvulnerable())
                _playerHasBeenHit = true;
            _explosionHasOccurred = true;
        } else
            bullet++;

    }
}

void EntityController::checkEnemyToPlayerShipCollisions()
{// Enemy <-> PlayerShip (enemy explodes, player dies)
    for(auto enemy = _enemies.begin(); enemy != _enemies.end();)
    {
        if (collides(_playerShip.getSprite(), (*enemy)->getSprite()))
        {
            auto explosion = std::make_unique<Explosion>(_resolution,
                                                              _playerShip.getDistanceFromCentre(),
                                                              _playerShip.getAngle(),
                                                               (*enemy)->getScale().x * 2,
                                                              _textureHolder, // ToDo : Remove me
                                                               textures::Explosion);

            _explosions.push_back(move(explosion));
            enemy = _enemies.erase(enemy);
            if (!_playerShip.isInvulnerable())
            {
                _playerHasBeenHit = true;
            }
            _explosionHasOccurred = true;

        }
        else
            enemy++;
    }
}

const bool EntityController::explosionOccurred()
{
    return _explosionHasOccurred;
}

void EntityController::checkClipping()
{
    // Clip away enemy bullets outside cylindrical frustum
    for (auto bullet = _bulletsEnemy.begin(); bullet != _bulletsEnemy.end();)
    {
        if ((*bullet)->getRadius() > _resolution.y / 2.f)
        {
            bullet = _bulletsEnemy.erase(bullet);
        } else
            bullet++;
    }

    // Clip away player bullets at centre
    auto radius_buffer = 20; // should be smaller than playableZoneRadiusFactor above
    for (auto bullet = _bulletsPlayer.begin(); bullet != _bulletsPlayer.end();)
    {
        if (((*bullet)->getPosition().x > (_resolution.x / 2) - radius_buffer)
            && ((*bullet)->getPosition().y > (_resolution.y / 2) - radius_buffer)
            && ((*bullet)->getPosition().x < (_resolution.x / 2) + radius_buffer)
            && ((*bullet)->getPosition().y < (_resolution.y / 2) + radius_buffer))
        {
            bullet = _bulletsPlayer.erase(bullet);
        } else
            bullet++;
    }

    // Remove any finished explosions
    for (auto explosion = _explosions.begin(); explosion != _explosions.end();)
    {
        if ((*explosion)->getLives() == 0) // ToDo: Make boolean, is_finished
        {
            explosion = _explosions.erase(explosion);
        } else
            explosion++;
    }
}

void EntityController::update()
{
    for (auto &enemy : _enemies)
        enemy->update();

    for (auto &bullet : _bulletsPlayer)
    {
        bullet->update();
        bullet->setMove(-25);
    }

    for (auto &bullet : _bulletsEnemy)
    {
        bullet->update();
        bullet->setMove(20);
    }

    for (auto &explosion : _explosions)
        explosion->update();

    _explosionHasOccurred = false;
    _enemyShootEventHasOccurred = false;
}

bool EntityController::collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
{
    auto shrink_factor = 4 + 0.2f;
    float radius_1 = (sprite1.getGlobalBounds().width + sprite1.getGlobalBounds().height) / shrink_factor;
    float radius_2 = (sprite2.getGlobalBounds().width + sprite2.getGlobalBounds().height) / shrink_factor;
    float distance_x = sprite1.getPosition().x - sprite2.getPosition().x;
    float distance_y = sprite1.getPosition().y - sprite2.getPosition().y;

    return  radius_1 + radius_2 >= sqrt((distance_x * distance_x) + (distance_y * distance_y));
}

const void EntityController::draw(sf::RenderWindow &renderWindow)
{

    for (auto &enemy : _enemies)
        renderWindow.draw(enemy->getSprite());

    for (auto &bullet : _bulletsEnemy)
        renderWindow.draw(bullet->getSprite());

    for (auto &bullet : _bulletsPlayer)
        renderWindow.draw(bullet->getSprite());

    for (auto &explosion : _explosions)
        renderWindow.draw(explosion->getSprite());

}

void EntityController::increaseGlobalSpeed(float amount = 0.1f)
{
    _speed_modifier += amount;
}
void EntityController::decreaseGlobalSpeed(float amount = 0.1f)
{
    if(_speed_modifier < amount)
        _speed_modifier = 0.1;
    else
        _speed_modifier -= amount;
}

#ifdef DEBUG
void EntityController::debug()
{
}
#endif // DEBUG