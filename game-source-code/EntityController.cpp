/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Controller and manager for game entity objects
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "EntityController.hpp"

#ifdef DEBUG

#include <iostream>

#endif // DEBUG

EntityController::EntityController(sf::Vector2i resolution,
                                   PlayerShip &playerShip,
                                   TextureHolder &textureHolder,
                                   Score &score,
                                   float speedModifier) : _resolution{resolution},
                                                          _playerShip{playerShip},
                                                          _textureHolder{textureHolder}, // ToDo: remove
                                                          _score{score}
{
    // Reset timers for the enemy spawning and shooting
    _timerSpawn.restart();
    _timerShoot.restart();
    _totalTime.restart();
    _explosionHasOccurred = false;
    _speedModifier = speedModifier;
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
            auto shipVariant = static_cast<entity::ID>(rand() % 1);
            auto shipTextureVariant = static_cast<textures::ID>(shipVariant); // ToDo : Remove me
            auto enemy = std::make_unique<Enemy>(_resolution,
                                                 0, 0, 0.5,
                                                 shipVariant,
                                                 _textureHolder, // ToDo: remove
                                                 shipTextureVariant); // ToDo : Remove me
            _enemies.push_front(std::move(enemy));
        }
    }
}

void EntityController::shoot()
{
    // Player shooting (Bullet creation)
    if (_playerShip.isShooting())
    {
        auto bullet = std::make_unique<Bullet>(_resolution,
                                               _playerShip.getDistanceFromCentre(),
                                               _playerShip.getAngle(),
                                               0.5,
                                               entity::PlayerBullet,
                                               _textureHolder,
                                               textures::BulletPlayer);
        _bulletsPlayer.push_front(std::move(bullet));
        _score.incrementBulletsFired();
    }

    // Enemy Shooting
    _enemyShootEventHasOccurred = false;
    auto minNumberEnemyBullets = 1;
    auto doNotFireInsideThisRadius = (_resolution.y / 2) * 0.05; // only shoot when closer
    float enemyShootTime = (rand() % 9000 + 500); // In Milliseconds
    for (auto &enemy : _enemies)
    {
        if (enemy->getDistanceFromCentre() > doNotFireInsideThisRadius)
        {
            if ((_timerShoot.getElapsedTime().asMilliseconds() > enemyShootTime)
                || (_bulletsEnemy.size() <= minNumberEnemyBullets))
            {
                _timerShoot.restart();
                auto bullet_enemy = std::make_unique<Bullet>(_resolution,
                                                             enemy->getDistanceFromCentre(),
                                                             enemy->getAngle(),
                                                             0.5,
                                                             entity::EnemyBullet,
                                                             _textureHolder, // ToDo : Remove me
                                                             textures::BulletEnemy); // ToDo : Remove me
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
#ifdef DEBUG
//    std::cout << _speedModifier << std::endl;
#endif // DEBUG

    // Reset enemies outside cylindrical frustum back to the centre. Otherwise, set up the
    // future enemy movement (and move faster - immediately after spawning - to get closer to the player)
    for (auto &enemy : _enemies)
    {
        if (enemy->getRadius() < _resolution.y / 2.f)
        {
            auto random_angle = (rand() % 3 + 2.0f);
            auto random_move = rand() % 15 + (-2);
            auto playableZoneRadiusFactor = 8;

            if (enemy->getDistanceFromCentre() < (_resolution.y / playableZoneRadiusFactor))
            {
                enemy->setMove((1 + random_angle)* _speedModifier, 15 * _speedModifier);
            } else
            {
                enemy->setMove(random_angle* _speedModifier, random_move * _speedModifier);
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
{
    // PlayerBullets -> Enemy (enemy explodes, PlayerBullet disappears)
    for (auto enemy = _enemies.begin(); enemy != _enemies.end(); ++enemy)
    {
        for (auto bullet = _bulletsPlayer.begin(); bullet != _bulletsPlayer.end();)
        {
            if (collides((*bullet)->getSprite(), (*enemy)->getSprite()))
            {
                auto explosion = std::make_unique<Explosion>(_resolution,
                                                             (*enemy)->getDistanceFromCentre(),
                                                             (*enemy)->getAngle(),
                                                             (*enemy)->getScale().x * 2,
                                                             entity::Explosion,
                                                             _textureHolder, // ToDo : Remove me
                                                             textures::Explosion); // ToDo : Remove me
                _explosions.push_back(std::move(explosion));
                bullet = _bulletsPlayer.erase(bullet);
                (*enemy)->die();
                _score.incrementEnemiesKilled((*enemy)->getType());
                _explosionHasOccurred = true;
            } else
                bullet++;
        }
    }

    // Process Enemy death events from PlayerBullets collisions above
    // (indexing/incrementing problems prevent performing these actions in the same nested loop)
    for (auto enemy = _enemies.begin(); enemy != _enemies.end();)
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
    for (auto bullet = _bulletsEnemy.begin(); bullet != _bulletsEnemy.end();)
    {
        if (collides(_playerShip.getSprite(), (*bullet)->getSprite()))
        {
            auto explosion = std::make_unique<Explosion>(_resolution,
                                                         _playerShip.getDistanceFromCentre(),
                                                         _playerShip.getAngle(),
                                                         _playerShip.getScale().x * 2,
                                                         entity::Explosion,
                                                         _textureHolder, // ToDo : Remove me
                                                         textures::Explosion); // ToDo : Remove me
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
    for (auto enemy = _enemies.begin(); enemy != _enemies.end();)
    {
        if (collides(_playerShip.getSprite(), (*enemy)->getSprite()))
        {
            auto explosion = std::make_unique<Explosion>(_resolution,
                                                         _playerShip.getDistanceFromCentre(),
                                                         _playerShip.getAngle(),
                                                         (*enemy)->getScale().x * 2,
                                                         entity::Explosion,
                                                         _textureHolder, // ToDo : Remove me
                                                         textures::Explosion); // ToDo : Remove me

            _explosions.push_back(move(explosion));
            enemy = _enemies.erase(enemy);
            if (!_playerShip.isInvulnerable())
            {
                _playerHasBeenHit = true;
            }
            _explosionHasOccurred = true;

        } else
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
        if ((*bullet)->getRadius() > _resolution.y / 2)
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

    return radius_1 + radius_2 >= sqrt((distance_x * distance_x) + (distance_y * distance_y));
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

void EntityController::changeGlobalSpeed(float amount = 0.1f)
{
    auto minimumSpeed = 0.1f;
    if ((_speedModifier + amount) < minimumSpeed)
        _speedModifier = minimumSpeed;
    else
        _speedModifier += amount;
}

const float EntityController::getSpeed() const
{
    return _speedModifier;
}

#ifdef DEBUG

void EntityController::debug()
{
}

#endif // DEBUG