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
        int minNumberEnemies = 1;
        int maxNumberEnemies = 5;
        float enemySpawnTime = rand() % 3 + 2;
        float enemySpawnTimeOutwards = rand() % 3 + 2;
        if (_enemies.size()<maxNumberEnemies){
            if ((_timerSpawn.getElapsedTime().asSeconds() > enemySpawnTime)
                || (_enemies.size() <= minNumberEnemies))
            {
                _timerSpawn.restart();
                auto shipVariant = static_cast<textures::ID>(rand() % 1);
                auto movmenetDirection = static_cast<MovementDirection>(rand()%2);
                auto enemy = std::make_unique<Enemy>(_resolution,
                                                     0, 0, 0.5,
                                                     _textureHolder,
                                                     shipVariant,
                                                     MovementState::SpiralOut,
                                                     movmenetDirection);
                _enemies.push_front(std::move(enemy));
            }
            if ((_timerSpawn.getElapsedTime().asSeconds() > enemySpawnTimeOutwards)
                || (_enemies.size() <= minNumberEnemies))
            {
                _timerSpawn.restart();
                auto shipVariant = static_cast<textures::ID>(rand() % 1);
                auto movmenetDirection = static_cast<MovementDirection>(rand()%2);
                auto enemy = std::make_unique<Enemy>(_resolution,
                                                     _resolution.y/2-1, common::angleFilter(180+_playerShip.getAngle()), 0.5,
                                                     _textureHolder,
                                                     shipVariant,
                                                     MovementState::SpiralIn,
                                                     movmenetDirection);
                _enemies.push_front(std::move(enemy));
            }
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
    auto minNumberEnemyBullets = 0;
    auto dontFireInsideThisRadius = (_resolution.y/2)*0.05; // only shoot when closer
    float enemyShootTime = (rand()% 9000 + 500); // In Milliseconds
    for (auto &enemy : _enemies)
    {
        if (enemy->getDistanceFromCentreWithOffset() > dontFireInsideThisRadius)
        {
            if ((_timerShoot.getElapsedTime().asMilliseconds() > enemyShootTime)
                || (_bulletsEnemy.size() <= minNumberEnemyBullets))
            {
                _timerShoot.restart();
                auto bullet_enemy = std::make_unique<Bullet>(_resolution,
                                                             enemy->getRadius(),
                                                             enemy->getAngleWithOffset(),
                                                             0.3,
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
    //common movement characteristics
    auto shipCircleRadius=300;
    auto shipOffsetIncrement=5;
    auto shipRadiusIncrease=5;
    auto growShipScreenZone = _resolution.y/5;
    auto ShipClipScreenZone = _resolution.y/2.5;

    for (auto &enemy : _enemies)
    {
        //generic properties for each enemy
        auto currentEnemeyDirectionSign = enemy->getMovementDirectionSign();
        auto currentEnemeyMovementState = enemy->getMovementState();
        auto currentEnemeyRadius= enemy->getRadius();
        auto currentXOffset = enemy->getOffsetX();
        auto currentYOffset = enemy->getOffsetY();
        auto currentEnemeyState = enemy->getMovementState();
        auto CurrentEnemeyAngle = enemy->getAngleWithOffset();

        if (currentEnemeyRadius< _resolution.y / 2.f)
        {
            //random values use
            auto random_angle = (rand() % 2 + 2.0f);
            auto random_move = rand() % 15 + (-2);
            auto randomStateChange=(rand()%100+1);

            if (currentEnemeyRadius>growShipScreenZone && currentEnemeyRadius<ShipClipScreenZone && currentEnemeyMovementState!=MovementState::figureOfEight)
            {
                //1 in 100 chance that the ship will enter a random movement state that is not spiral inwards or outwards

                if(randomStateChange<3) //1% chance
                {
                    enemy->setMovementState(MovementState::circleOffsetLeft);
                }
                if(randomStateChange>2 && randomStateChange<4) //1% chance
                {
                    enemy->setMovementState(MovementState::circleOffsetRight);
                }
                else if(randomStateChange==50) //0.5% change
                {
                    enemy->setMovementState(MovementState::SpiralOut);
                }

                else if(randomStateChange==60) //0.5% change
                {
                    enemy->setMovementState(MovementState::SpiralOut);
                }
                 if(randomStateChange>200) //2% chance
                {
                    enemy->setMovementState(MovementState::figureOfEight);
                }

            }   //end of random movement logic

            switch (enemy->getMovementState())
            {
                case (MovementState::SpiralOut) : //standard spiral out movement
                    if (currentEnemeyRadius < growShipScreenZone) //grow faster if close to the centre
                        enemy->setMove(random_angle, shipRadiusIncrease * 3,currentXOffset,currentYOffset);
                    else
                        enemy->setMove(random_angle * currentEnemeyDirectionSign, shipRadiusIncrease * _speed_modifier,
                                       currentXOffset, currentYOffset);
                    break;
                case (MovementState::SpiralIn) : //spiral in movement. decrement the radius
                    enemy->setMove(random_angle* currentEnemeyDirectionSign, -shipRadiusIncrease * _speed_modifier,currentXOffset,currentYOffset);
                    break;

                case (MovementState::circleOffsetRight) : //preform a "divebom" move by offsetting centre of circle
                    if (currentXOffset < shipCircleRadius) {
                        enemy->setMove(random_angle*currentEnemeyDirectionSign, -shipRadiusIncrease, currentXOffset + shipOffsetIncrement, currentYOffset);
                    } else {
                        enemy->setMove(random_angle*currentEnemeyDirectionSign, +shipRadiusIncrease, currentXOffset, currentYOffset);
                    }

                    break;

                case (MovementState::circleOffsetLeft) :
                    if (currentXOffset > -shipCircleRadius) {
                        enemy->setMove(random_angle*currentEnemeyDirectionSign, -shipRadiusIncrease, currentXOffset - shipOffsetIncrement, currentYOffset);
                    } else {
                        enemy->setMove(random_angle*currentEnemeyDirectionSign, +shipRadiusIncrease, currentXOffset, currentYOffset);
                    }
                    break;
//                case (MovementState::figureOfEight) :
//
//                    auto currentAngleInRad = common::degreeToRad(common::angleFilter(enemy->getAngle()));
//
//                    auto radius=sin(currentAngleInRad)*sin(currentAngleInRad);
//
//                    std::cout << radius << std::endl;
//                    if (currentXOffset<300 && currentYOffset<300)
//                    {
//                        auto newX=cos(currentAngleInRad)*radius*currentXOffset+15;
//                        auto newY=sin(currentAngleInRad)*radius*currentYOffset+15;
//                        enemy->setMove(1,0,newX,newY);
//                    }
//                    else
//                    {
//                        auto newX=cos(currentAngleInRad)*radius*300;
//                        auto newY=sin(currentAngleInRad)*radius*300;
//                        enemy->setMove(random_angle,0,newX,newY);
//                    }
//                    enemy->setMove(1,0,newX,newY);
//                    break;
            }
        } else //if enemey is outside of the radius, reset it
            enemy->reset();
        if (currentEnemeyMovementState==MovementState::SpiralIn && currentEnemeyRadius>10) // enemey spiral id and is gone,reset
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
                                                                  (*enemy)->getRadius(),
                                                                  (*enemy)->getAngleWithOffset(),
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