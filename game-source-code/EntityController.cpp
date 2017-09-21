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
                                                                   _textureHolder(textureHolder) // ToDo: remove
{
    // Reset timers for the enemy spawning and shooting
    _timerSpawn.restart();
    _timerShoot.restart();
    _explosionEvent = false;
    _speed_modifier = 0.75f;
}

void EntityController::spawnEnemies()
{
    int min_number_enemies = 2;
    float enemySpawnTime = rand()%3 + 2;
    if ((_timerSpawn.getElapsedTime().asSeconds() > enemySpawnTime)||
            (_enemies.size() <= min_number_enemies))
    {
        _timerSpawn.restart();
        auto shipVariant = static_cast<textures::ID>(rand()%2);
        auto enemy = std::make_unique<Enemy>(_resolution,
                                                   0, 0, 0.5,
                                                   _textureHolder, // ToDo: remove
                                                   shipVariant);
        _enemies.push_front(std::move(enemy));
    }
}


void EntityController::shoot(PlayerShip &playerShip)
{
    _shootEvent = false;
    if (playerShip.isShooting())
    { auto bullet = std::make_unique<Bullet>(_resolution,
                                                   playerShip.getDistanceFromCentre(),
                                                   playerShip.getAngle(),
                                                   0.5,
                                                   _textureHolder,
                                                   textures::BulletPlayer);
        _bulletsPlayer.push_front(std::move(bullet));
    }

    float enemyShootTime = (rand()% 9000 + 500);
    for (auto &enemy : _enemies)
    {
        if (_timerShoot.getElapsedTime().asMilliseconds() > enemyShootTime)
        {
            _timerShoot.restart();
            auto bullet_enemy = std::make_unique<Bullet>(_resolution,
                                                               enemy->getDistanceFromCentre(),
                                                               enemy->getAngle(),
                                                               0.5,
                                                               _textureHolder,
                                                               textures::BulletEnemy);
            _bulletsEnemy.push_front(std::move(bullet_enemy));
            _shootEvent = true;
        }
    }
}

bool EntityController::shootingOccurred()
{
    return _shootEvent;
}
void EntityController::setMove()
{
    // Reset enemies outside cylindrical frustum back to the centre
    // otherwise, set their moves (and move faster immediately after spawning to get closer to player)
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

bool EntityController::checkCollisions(PlayerShip &playerShip)
{
    bool player_is_hit = false;
    bool explosion_occurred = false;

    // Enemy -> PlayerShip (enemy explodes, player dies)
    for( auto enemy = _enemies.begin(); enemy != _enemies.end();)
    {
        if (collides(playerShip.getSprite(), (*enemy)->getSprite()))
        {
            auto explosion = std::make_unique<Explosion>(_resolution,
                                                               playerShip.getDistanceFromCentre(),
                                                               playerShip.getAngle(),
                                                               (*enemy)->getScale().x * 2,
                                                               _textureHolder,
                                                               textures::Explosion);

            _explosions.push_back(std::move(explosion));
            enemy = _enemies.erase(enemy);
            if (!playerShip.isInvulnerable())
                player_is_hit = true;
            explosion_occurred = true;
#ifdef DEBUG
            std::cout << "Explosion! : Enemy hit PlayerShip" << std::endl;
#endif // DEBUG
        }
        else
            enemy++;
    }

    // EnemyBullets -> PlayerShip (player explodes + dies, bullet disappears)
    for( auto bullet = _bulletsEnemy.begin(); bullet != _bulletsEnemy.end();)
    {
        if (collides(playerShip.getSprite(), (*bullet)->getSprite()))
        {
            auto explosion = std::make_unique<Explosion>(_resolution,
                                                               playerShip.getDistanceFromCentre(),
                                                               playerShip.getAngle(),
                                                               playerShip.getScale().x * 2,
                                                               _textureHolder,
                                                               textures::Explosion);
            _explosions.push_back(std::move(explosion));
            bullet = _bulletsEnemy.erase(bullet);
            if (!playerShip.isInvulnerable())
                player_is_hit = true;
            explosion_occurred = true;
#ifdef DEBUG
            std::cout << "Explosion! : EnemyBullet hit Player" << std::endl;
#endif // DEBUG
        } else
            bullet++;

    }

    // PlayerBullets -> Enemy (enemy explodes, playerbullet disappears)
    for( auto enemy = _enemies.begin(); enemy != _enemies.end(); ++enemy)
    {
        for( auto bullet = _bulletsPlayer.begin(); bullet != _bulletsPlayer.end();)
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
                explosion_occurred = true;
#ifdef DEBUG
                std::cout << "Explosion! : PlayerBullet hit enemy" << std::endl;
#endif // DEBUG
            } else
                bullet++;
        }
    }

    // Process Enemy death events from PlayerBullets collisions above
    for( auto enemy = _enemies.begin(); enemy != _enemies.end();)
    {
        if ((*enemy)->getLives() == 0)
        {
            enemy = _enemies.erase(enemy);
        } else
            enemy++;
    }

    if (explosion_occurred)
        _explosionEvent = true;

    return player_is_hit;
}

bool EntityController::explosionOccurred()
{
    return _explosionEvent;
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

    _explosionEvent = false;
    _shootEvent = false;
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

void EntityController::draw(sf::RenderWindow &renderWindow)
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
//    auto size_player_bullets = std::distance(_bulletsPlayer.begin(), _bulletsPlayer.end());
//    auto size_enemy_bullets = std::distance(_bulletsEnemy.begin(), _bulletsEnemy.end());
//    if (size_enemy_bullets > 0)
//        std::cout << "Enemy Bullets active: " << size_enemy_bullets << std::endl;
//    if (size_player_bullets > 0)
//        std::cout << "Player Bullets active: " << size_player_bullets << std::endl;
}
#endif // DEBUG