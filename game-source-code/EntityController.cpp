/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Controller and manager for game entity objects
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "EntityController.hpp"
#ifdef DEBUG_ONLY
#include <iostream>
#endif // DEBUG_ONLY
#include <iostream>

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
    _satellitesAlive = 0;
    _timerSpawnFromCentre.restart();
    _timerSpawnFromPerimeter.restart();
    _timerSatellite.restart();
    _timerMeteoroid.restart();
    _totalTime.restart();
    _explosionHasOccurred = false;
    _defaultSpeed = speedModifier;
    _speedModifier = _defaultSpeed;
    // Generic properties set at construction
    _bulletPlayerSpeed = 25;
    _bulletEnemySpeed = 20;
    _meteoroidSpeed = 30;
    auto seed0 = 4294967296; //Seeds for PerlinNoise (prime numbers)
    auto seed1 = 1664525;
    auto _xNoise = PerlinNoise(seed0);
    auto _yNoise = PerlinNoise(seed1);

}


void EntityController::spawnSpiral(entity::ID id, textures::ID shipVariant, MovementDirection movementDirection, MovementState movementState)
{
    float spiralDistanceFromCentre;
    float spiralAngle;
    switch (movementState)
    {
        case (MovementState::SpiralIn):
            spiralDistanceFromCentre=(_resolution.y/2)-1;//Spawn just inside play zone,1 pixel in
            spiralAngle=180+_playerShip.getAngle(); //Spawn opposite side to playership
            _timerSpawnFromPerimeter.restart();
            break;

        case (MovementState::SpiralOut):
            spiralDistanceFromCentre=0;
            spiralAngle=0;
            _timerSpawnFromCentre.restart();
            break;
        case (MovementState::Wandering):
            spiralDistanceFromCentre=rand()%_resolution.x/4; //random position to start wandering
            spiralAngle=rand()%360-180;
            _timerSpawnFromCentre.restart();
            break;
        default :
            break;
    }

    auto enemy = std::make_unique<Enemy>(_resolution,
                                         spiralDistanceFromCentre,
                                         spiralAngle,
                                         0.5,
                                         id,
                                         _textureHolder,
                                         shipVariant,
                                         movementState,
                                         movementDirection);

    _enemies.push_front(std::move(enemy)); //add enemy to enemy vector
}


void EntityController::spawnMeteoroid()
{
    _timerMeteoroid.restart();
    auto randomAngle = rand()%360;
    auto meteoroid = std::make_unique<Meteoroid>(_resolution,
                                                 0,
                                                 randomAngle,
                                                 1,
                                                 entity::Meteoroid,
                                                 _textureHolder,
                                                 textures::Meteoroid);
    _meteoroids.push_front(std::move(meteoroid));

}

void EntityController::spawnSatellites()
{
    _timerSatellite.restart();
    auto satelliteCirclingRadius = _resolution.y/20;
    auto satelliteSpawnScale = 0.7;
    auto movementDirection = static_cast<MovementDirection>(rand() % 2); //random clock or couterclockwise
    auto numberOfSatellites = 3;
    _satellitesAlive = numberOfSatellites + 1; //only ever want 3 alive at a time. add to the counter
    auto angle = 0;
    auto currentShipRadius = _playerShip.getRadius(); //current playership location is used for satellite spawn
    auto currentShipAngle = _playerShip.getAngle();
    auto satelliteScaleSize = 0.4;
    //convert back from polar to x&y to define the offset of satellite
    auto spawnAngle = common::degreeToRad(currentShipAngle+180); //spawn on other side to playership
    auto satelliteSpawnLocation = sf::Vector2f{float(satelliteScaleSize*currentShipRadius*sin(spawnAngle)),
                                               float(satelliteScaleSize*currentShipRadius*cos(spawnAngle))};
    for (auto i = 0; i < numberOfSatellites; i++) //need to spawn 3 Satellites. run loop 3 times
    {
        //introduce a random element on spawn and add to the generic centre the others use
        auto randomOffsetX = (rand() % 20 + 10.0f);
        auto randomOffsetY = (rand() % 20 + 10.0f);
        //spawn ships at a slight random offset from centre of rotation point
        satelliteSpawnLocation={satelliteSpawnLocation.x+randomOffsetX,satelliteSpawnLocation.y+randomOffsetY};
        auto enemy = std::make_unique<Enemy>(_resolution,
                                             satelliteCirclingRadius,
                                             angle,
                                             satelliteSpawnScale,
                                             entity::Satellite,
                                             _textureHolder,
                                             textures::Satellite,
                                             MovementState::SmallCircling,
                                             movementDirection);

        angle += 120; //increment by 360/3 to provide symetric spawning
        enemy->setScale(0,0);
        enemy->setMove(angle,satelliteCirclingRadius,satelliteSpawnLocation); //moves satellite on its spawn so its not off screen
        enemy->move();
        _enemies.push_front(std::move(enemy));
    }
}

void EntityController::spawnEntities()
{
    // Initial delay before first enemies spawn
    if (_totalTime.getElapsedTime().asSeconds() > 1)
    {
        auto minNumberEnemies = 1;
        auto maxNumberEnemies = 7;
        if (_enemies.size() < maxNumberEnemies)
        {

            //spawn enemy spiral out
            float enemySpawnFromCentreTimer = fmod(rand(),1.2f) + 0.8f;
            auto shipVariant = static_cast<textures::ID>(rand() % 2);
            auto movementDirection = static_cast<MovementDirection>(rand()%2);

            if ((_timerSpawnFromCentre.getElapsedTime().asSeconds() > enemySpawnFromCentreTimer)
                || (_enemies.size() <= minNumberEnemies))
            {
                spawnSpiral(entity::Basic,shipVariant,movementDirection,MovementState::SpiralOut);
            }

            // spawn enemy spiral in(or wander)
            float enemySpawnFromPerimeterTimer = fmod(rand(),2.4f) + 1.6f;
            if ((_timerSpawnFromPerimeter.getElapsedTime().asSeconds() > enemySpawnFromPerimeterTimer)
                || (_enemies.size() <= minNumberEnemies)) {
                auto movementState = static_cast<MovementState >(rand()%2+1); //random chance to spiral in or wander
                spawnSpiral(entity::Basic, shipVariant, movementDirection, movementState);
            }
        }
        // spawn satellites
        if (_satellitesAlive == 0)
        {
            float satelliteSpawn = fmod(rand(), 5.f) + 15.f;
            if (_timerSatellite.getElapsedTime().asSeconds() > satelliteSpawn)
                spawnSatellites();
        }
        else
        {
            _timerSatellite.restart();
        }
        //spawn meteroids
        auto meteoroidSpawnEventTimer = fmod(rand(),8.f) + 10.f;
        if (_timerMeteoroid.getElapsedTime().asSeconds() > meteoroidSpawnEventTimer)
            spawnMeteoroid();
    }
}

void EntityController::playerShoot()
{
    auto numberOfBullets = 1;
    auto bulletOffset = 3.8f; //adjust so bullet spawns just ahead of ship
    auto bulletScale = _playerShip.getScale().x * 1.5f;

    if (_playerShip.isUpgraded())
    {
        numberOfBullets = 2;
    }

    for (auto i = 0; i < numberOfBullets; i++) //based on 1, or 2 bullets
    {
        if (numberOfBullets == 1)
            bulletOffset = 0;
        else
            bulletOffset *= -1;

        auto bullet = std::make_unique<Bullet>(_resolution,
                                               _playerShip.getDistanceFromCentre(),
                                               _playerShip.getAngle() + bulletOffset,
                                               bulletScale,
                                               entity::PlayerBullet,
                                               _textureHolder,
                                               textures::BulletPlayer);

        _bulletsPlayer.push_front(std::move(bullet));
        _score.incrementBulletsFired();
    }
}
void EntityController::shoot()
{
    // Player shooting (Bullet creation)
    if (_playerShip.isShooting())
    {
        playerShoot();
    }

    // Enemy Shooting
    _enemyShootEventHasOccurred = false;
    auto minNumberEnemyBullets = 0;
    auto doNotFireInsideThisRadius = (_resolution.y/2)*0.05; // only shoot when closer ( 5% of circle radius)
    float enemyShootTime = (fmod(rand(),2.5f) + 3.2f);
    for (auto &enemy : _enemies)    //all enemies need a chance to shoot
    {
        if (enemy->getDistanceFromCentreWithOffset() > doNotFireInsideThisRadius)
        {
            if ((enemy->getShootTimerElapsedTime() > enemyShootTime)
                || (_bulletsEnemy.size() < minNumberEnemyBullets))
            {
                enemy->resetShootTimer();
                auto bullet_enemy = std::make_unique<Bullet>(_resolution,
                                                             enemy->getRadius(),
                                                             enemy->getAngleWithOffset(),
                                                             0.3,
                                                             entity::EnemyBullet,
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
    auto growShipScreenZone = _resolution.y/5.f; // Prevents change in behaviour near boundary
    auto shipClipScreenZone = _resolution.y/2.5f; // Prevents change in behaviour near boundary
    auto minimumRadius = (_resolution.y/2)*0.06; // specifies minimum radius that within no behavour changes occur

    for (auto &enemy : _enemies)
    {
        // Generic properties for each enemy. defined in the loop as per enemy spesific
        auto currentEnemyMovementState = enemy->getMovementState();
        auto currentEnemyRadius= enemy->getRadius();
        auto currentEnemyType = enemy->getType();
        if ((currentEnemyRadius > _resolution.y / 2.f)  // Don/t leave game play area, respawn in centre after leaving
             || ((currentEnemyMovementState == MovementState::SpiralIn) && (currentEnemyRadius < minimumRadius)))//reset from spiral inwards
        {
            enemy->reset();
        }
        else
        {
            // Random values to define ship movement
            auto randomStateChange=(rand()%100+1); // 1 to 100%, chance to change state

            // Chance that the ship will enter a new movement state
            if (((currentEnemyType  == entity::Basic) || (currentEnemyType  == entity::BasicAlternate)) //only apply changes to normal ships
                && (currentEnemyRadius > growShipScreenZone) //dont change state if ship is too small
                && (currentEnemyRadius < shipClipScreenZone) //dont change state if ship is too big and is going to fly off screen
                    &&(currentEnemyMovementState!= MovementState::Wandering)) //if the ship spawned in a wandering, then it must remain as such
            {

                if (randomStateChange < 6)                                      //5% chance
                {
                    enemy->setMovementState(MovementState::CircleOffsetLeft);
                }
                if (randomStateChange > 6 && randomStateChange < 13)            //5% chance
                {
                    enemy->setMovementState(MovementState::CircleOffsetRight);
                } else if ((randomStateChange > 50) && (randomStateChange < 52))  // 2% chance
                {
                    enemy->setMovementState(MovementState::SpiralIn);
                } else if (randomStateChange == 60)                               //1% change
                {
                    enemy->setMovementState(MovementState::SpiralOut);
                }
            }
            PreformEnemyMove(enemy, currentEnemyMovementState, growShipScreenZone, currentEnemyRadius);
        }
    }
}
void EntityController::PreformEnemyMove(std::unique_ptr<Enemy> &enemy, MovementState currentEnemyMovementState, float growShipScreenZone, float currentEnemyRadius){
    // Common movement parameters
    auto shipCircleRadius=_resolution.y/3.f; // defines size of spiral side circle radius
    auto shipOffsetIncrement=rand()%3+1.f; // defines how circle offset changes. random on each frame
    auto shipRadiusIncrease=rand()%3+1.f; // defines how much to increment the ship radius by
    auto distantSpeedMultiplier = 10.f; // effects how fast the ship circles grow
    auto satelliteGrowIncrement = 2.0f; //satellites grow at a different rate, faster than other entities

    auto currentEnemyDirectionSign = enemy->getMovementDirectionSign();
    auto currentEnemyCentre = enemy->getCentre();

    auto randomAngle = (rand() % 2 + 2.0f);

// Movement (based on behaviour state)
    switch (currentEnemyMovementState)
    {
        case (MovementState::SpiralOut) : //sStandard spiral-out movement
        {
            if (currentEnemyRadius < growShipScreenZone) //grow faster if close to the centre
                enemy->setMove(randomAngle * _speedModifier,
                               shipRadiusIncrease * distantSpeedMultiplier * _speedModifier,
                               currentEnemyCentre);
            else
                enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                               shipRadiusIncrease * _speedModifier,
                               currentEnemyCentre);
            break;
        }
        case (MovementState::SpiralIn) : //spiral in movement. decrement the radius
            enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                           -shipRadiusIncrease * _speedModifier,
                           currentEnemyCentre);
            break;
        case (MovementState::CircleOffsetRight) : // Perform a "dive-bomb" move, by offsetting centre of circle
            if (currentEnemyCentre.x < shipCircleRadius)
            {
                enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                               0,
                               {currentEnemyCentre.x + shipOffsetIncrement, currentEnemyCentre.y});
            } else
            {
                enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                               +shipRadiusIncrease * _speedModifier,
                               currentEnemyCentre);
            }
            break;
        case (MovementState::CircleOffsetLeft) :
            if (currentEnemyCentre.x > -shipCircleRadius)
            {
                enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                               0,
                               {currentEnemyCentre.x - shipOffsetIncrement,currentEnemyCentre.y});
            } else
            {
                enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                               +shipRadiusIncrease * _speedModifier,
                               currentEnemyCentre);
            }
            break;
        case (MovementState::SmallCircling) :
            enemy->setMove(randomAngle*_speedModifier,
                           satelliteGrowIncrement,
                           currentEnemyCentre);
            break;
        case (MovementState::Wandering):
            enemy->setMove(float(_xNoise.noise(enemy->getAliveTimeElapsedTime())*5+2*currentEnemyDirectionSign)*_speedModifier,
                           float(_yNoise.noise(enemy->getAliveTimeElapsedTime()/3)*50-25)*_speedModifier,
                           {0,0});
    }
}


bool EntityController::checkCollisions()
{
    _explosionHasOccurred = false;
    _playerHasBeenHit = false;

    checkEnemyToPlayerShipCollisions();
    checkEnemyBulletsToPlayerShipCollisions();
    checkPlayerBulletsToEnemyCollisions();
    checkMeteoroidToPlayerShipCollisions();
    checkPlayerBulletsToMeteoroidCollisions();

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
                                                             (*enemy)->getRadius(),
                                                             (*enemy)->getAngleWithOffset(),
                                                             (*enemy)->getScale().x * 2,
                                                             entity::Explosion,
                                                             _textureHolder,
                                                             textures::Explosion);
                _explosions.push_back(std::move(explosion));
                bullet = _bulletsPlayer.erase(bullet);
                (*enemy)->die();
                _score.incrementEnemiesKilled((*enemy)->getType());
                enemyKilled((*enemy)->getType());
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
        }
        else
            enemy++;
    }
}

void EntityController::killAllEnemiesOfType(entity::ID type)
{
    for (auto enemy = _enemies.begin(); enemy != _enemies.end();)
    {
        auto enemyType = (*enemy)->getType();
        if (enemyType == entity::Satellite)
        {
            _satellitesAlive = 0;
        }

        if (enemyType == type)
        {
            enemy = _enemies.erase(enemy);
        }
        else
            enemy++;
    }
}

void EntityController::checkPlayerBulletsToMeteoroidCollisions()
{
    // PlayerBullets -> Enemy (enemy explodes, PlayerBullet disappears)
    for (auto meteoroid = _meteoroids.begin(); meteoroid != _meteoroids.end(); ++meteoroid)
    {
        for (auto bullet = _bulletsPlayer.begin(); bullet != _bulletsPlayer.end();)
        {
            if (collides((*bullet)->getSprite(), (*meteoroid)->getSprite()))
            {
                auto explosion = std::make_unique<Explosion>(_resolution,
                                                             (*bullet)->getRadius(),
                                                             (*bullet)->getAngle(),
                                                             (*bullet)->getScale().x / 2,
                                                             entity::Explosion,
                                                             _textureHolder,
                                                             textures::Explosion);
                _explosions.push_back(std::move(explosion));
                bullet = _bulletsPlayer.erase(bullet);
                _explosionHasOccurred = true;
            } else
                bullet++;
        }
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
            {
                _playerHasBeenHit = true;
            }
            _explosionHasOccurred = true;
        }
        else
            bullet++;

    }
}

void EntityController::checkMeteoroidToPlayerShipCollisions()
{// Meteoroids -> PlayerShip (player explodes + dies, meteor keeps going)
    for (auto meteoroid = _meteoroids.begin(); meteoroid != _meteoroids.end(); meteoroid++)
    {
        if (collides(_playerShip.getSprite(), (*meteoroid)->getSprite()))
        {
            auto explosion = std::make_unique<Explosion>(_resolution,
                                                         _playerShip.getDistanceFromCentre(),
                                                         _playerShip.getAngle(),
                                                         (*meteoroid)->getScale().x,
                                                         entity::Explosion,
                                                         _textureHolder, // ToDo : Remove me
                                                         textures::Explosion); // ToDo : Remove me
            _explosions.push_back(std::move(explosion));
            if (!_playerShip.isInvulnerable())
            {
                _playerHasBeenHit = true;
            }
            _explosionHasOccurred = true;
        }
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
            _score.incrementEnemiesKilled((*enemy)->getType());
            enemyKilled((*enemy)->getType());
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
    // Clip away projectiles (bullets/meteoroids) outside cylindrical frustum
    for (auto bullet = _bulletsEnemy.begin(); bullet != _bulletsEnemy.end();)
    {
        if ((*bullet)->getRadius() > _resolution.y / 2)
        {
            bullet = _bulletsEnemy.erase(bullet);
        } else
            bullet++;
    }

    for (auto meteoroid = _meteoroids.begin(); meteoroid != _meteoroids.end();)
    {
        if ((*meteoroid)->getRadius() > _resolution.y / 2)
        {
            meteoroid = _meteoroids.erase(meteoroid);
        } else
            meteoroid++;
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
        bullet->setMove(-_bulletPlayerSpeed);
    }

    for (auto &bullet : _bulletsEnemy)
    {
        bullet->update();
        bullet->setMove(_bulletEnemySpeed * _speedModifier);
    }

    for (auto &meteoroid : _meteoroids)
    {
        meteoroid->update();
        meteoroid->setMove(_meteoroidSpeed * _speedModifier);
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

    for (auto &meteoroid : _meteoroids)
        renderWindow.draw(meteoroid->getSprite());

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

void EntityController::resetGlobalSpeed()
{
    _speedModifier = _defaultSpeed;
}

void EntityController::enemyKilled(entity::ID type)
{
    if (type == entity::Satellite)
    {
        _satellitesAlive--;
    }
    if (_satellitesAlive == 1)
    {
        upgradePlayerShip();
        _satellitesAlive = 0;
    }
}

void EntityController::upgradePlayerShip()
{
    _playerShip.upgrade();
}