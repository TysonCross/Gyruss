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
                                   EntityPlayerShip &playerShip,
                                   TextureHolder &textureHolder, // ToDo: remove, along with Sounds
                                   SoundHolder &soundHolder) : _resolution(resolution),
                                                               _textureHolder(textureHolder), // ToDo: remove
                                                               _soundHolder(soundHolder) // ToDo: remove
{
    // Reset timers for the enemy spawning and shooting
    _timerSpawn.restart();
    _timerShoot.restart();
}

void EntityController::spawnEnemies()
{
    float enemySpawnTime = rand()%3 + 2;
    if (_timerSpawn.getElapsedTime().asSeconds() > enemySpawnTime)
    {
        _timerSpawn.restart();
        auto shipVariant = static_cast<textures::ID>(rand()%2);
        auto enemy = std::make_unique<EntityEnemy>(_resolution,
                                                   0, 0, 0.5,
                                                   _textureHolder, // ToDo: remove
                                                   _soundHolder, // ToDo: remove
                                                   shipVariant);
        _enemies.push_front(std::move(enemy));
    }
}


void EntityController::shoot(EntityPlayerShip &playerShip)
{
    if (playerShip.isShooting())
    { auto bullet = std::make_unique<EntityBullet>(_resolution,
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
            auto bullet_enemy = std::make_unique<EntityBullet>(_resolution,
                                                               enemy->getDistanceFromCentre(),
                                                               enemy->getAngle(),
                                                               0.5,
                                                               _textureHolder,
                                                               textures::BulletEnemy);
            _bulletsEnemy.push_front(std::move(bullet_enemy));
        }
    }
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
            auto random_move = rand() % 12 + (-2);
            auto playableZoneRadiusFactor = 8;

            if (enemy->getDistanceFromCentre() < (_resolution.y / playableZoneRadiusFactor))
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

bool EntityController::checkCollisions(EntityPlayerShip &playerShip)
{
    bool player_is_hit = false;

    // Enemy -> PlayerShip (enemy explodes, player dies)
    for( auto enemy = _enemies.begin(); enemy != _enemies.end();)
    {
        if (collides(playerShip.getSprite(), (*enemy)->getSprite()))
        {
            auto explosion = std::make_unique<EntityExplosion>(_resolution,
                                                               playerShip.getDistanceFromCentre(),
                                                               playerShip.getAngle(),
                                                               (*enemy)->getScale().x * 2,
                                                               _textureHolder,
                                                               _soundHolder,
                                                               textures::Explosion);

            _explosions.push_back(std::move(explosion));
            enemy = _enemies.erase(enemy);
            player_is_hit = true;
        }
        else
            enemy++;
    }

    // EnemyBullets -> PlayerShip (player explodes + dies, bullet disappears)
    for( auto bullet = _bulletsEnemy.begin(); bullet != _bulletsEnemy.end();)
    {
        if (collides(playerShip.getSprite(), (*bullet)->getSprite()))
        {
            auto explosion = std::make_unique<EntityExplosion>(_resolution,
                                                               playerShip.getDistanceFromCentre(),
                                                               playerShip.getAngle(),
                                                               playerShip.getScale().x * 2,
                                                               _textureHolder,
                                                               _soundHolder,
                                                               textures::Explosion);
            _explosions.push_back(std::move(explosion));
            bullet = _bulletsEnemy.erase(bullet);
            player_is_hit = true;
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
                auto explosion = std::make_unique<EntityExplosion>(_resolution,
                                                                   (*enemy)->getDistanceFromCentre(),
                                                                   (*enemy)->getAngle(),
                                                                   (*enemy)->getScale().x * 2,
                                                                   _textureHolder,
                                                                   _soundHolder,
                                                                   textures::Explosion);
                _explosions.push_back(std::move(explosion));
                bullet = _bulletsPlayer.erase(bullet);
                (*enemy)->die();
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

    return player_is_hit;
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