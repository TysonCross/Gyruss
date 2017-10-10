/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Controller and manager for game entity objects
/////////////////////////////////////////////////////////////////////

#include "EntityController.hpp"

EntityController::EntityController(sf::Vector2i resolution,
                                   PlayerShip &playerShip,
                                   TextureHolder &textureHolder,
                                   Score &score,
                                   float speedModifier) : _resolution{resolution},
                                                          _playerShip{playerShip},
                                                          _textureHolder{textureHolder},
                                                          _score{score}
{
    // Reset timers for the enemy spawning and shooting
    _satellitesAlive = 0;
    _timerSpawnFromCentre.restart();
    _timerSpawnFromPerimeter.restart();
    _timerSpawnWanderer.restart();
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
    _xNoise = PerlinNoise(seed0);
    _yNoise = PerlinNoise(seed1);
}


void EntityController::spawnBasicEnemy(entity::ID id,
                                       textures::ID shipVariant,
                                       MovementDirection movementDirection,
                                       MovementState movementState)
{
    float spiralDistanceFromCentre;
    float spiralAngle;

    switch (movementState)
    {
        case (MovementState::SpiralIn):
        {
            spiralDistanceFromCentre = (_resolution.y / 3) - 1;//Spawn just inside play zone
            spiralAngle = _playerShip.getAngle() + 180; //Spawn opposite side to playerShip
            _timerSpawnFromPerimeter.restart();
            break;
        }

        case (MovementState::SpiralOut):
        {
            spiralDistanceFromCentre = 0;
            spiralAngle = 0;
            _timerSpawnFromCentre.restart();
            break;
        }

        case (MovementState::Wandering):
        {
            spiralDistanceFromCentre = (_resolution.y / 3) - rand() % 10; // Slightly random position to start wandering
            spiralAngle = _playerShip.getAngle() + rand() % 90 + 180; // Random angle, avoiding playerShip
            _timerSpawnWanderer.restart();
            break;
        }

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

    // SpiralIn and Wandering need to have their move set on spawn to prevent clipping. SpiralOut does not
    // need this as it is in the centre to begin with.
    if((movementState==MovementState::Wandering)||(movementState==MovementState::SpiralIn))
    {
        enemy->setScale(0, 0);
        enemy->setMove(0, 0);
        enemy->move();
    }
    _enemies.push_front(std::move(enemy)); // Add enemy to enemy vector
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
    auto numberOfSatellites = 3;
    _satellitesAlive = numberOfSatellites + 1; // Only ever want 3 alive at a time (index starts at 1)
    auto satelliteCirclingRadius = _resolution.y / 20;
    auto satelliteSpawnScale = 0.7;
    auto movementDirection = static_cast<MovementDirection>(rand() % 2); // Random clockwise or counter-clockwise
    auto angle = 0;
    auto currentShipRadius = _playerShip.getRadius(); // Current playership location is used for satellite spawn
    auto currentShipAngle = _playerShip.getAngle();
    auto satelliteScaleSize = 0.4;
    auto spawnAngle = common::degreeToRad(currentShipAngle+180);     // Offset of satellite
                                                                     // Spawn on other side to playerShip
    auto satelliteSpawnLocation = sf::Vector2f{float(satelliteScaleSize*currentShipRadius*sin(spawnAngle)),
                                               float(satelliteScaleSize*currentShipRadius*cos(spawnAngle))};
    for (auto i = 0; i < numberOfSatellites; i++) //need to spawn 3 Satellites. run loop 3 times
    {
        //introduce a random element on spawn and add to the generic centre the others use
        auto randomOffsetX = rand() % 20 + 10.0f;
        auto randomOffsetY = rand() % 20 + 10.0f;

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

        angle += 120; // Symmetric spawning
        enemy->setScale(0,0);
        enemy->setMove(0,0,satelliteSpawnLocation); // Ensure  satellite not off-screen
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
        auto maxNumberEnemies = 8;
        if (_enemies.size() < maxNumberEnemies)
        {
            auto shipVariant = static_cast<textures::ID>(rand() % 2);
            auto shipType = static_cast<entity::ID>(shipVariant);
            auto movementDirection = static_cast<MovementDirection>(rand() % 2);

            // Spawn enemy spiral out
            float enemySpawnFromCentreTimer = float(fmod(rand(), 1.2f) + 0.8f);
            if ((_timerSpawnFromCentre.getElapsedTime().asSeconds() > enemySpawnFromCentreTimer)
                || (_enemies.size() <= minNumberEnemies))
            {
                spawnBasicEnemy(shipType, shipVariant, movementDirection, MovementState::SpiralOut);
            }

            // Spawn enemy spiral in
            float enemySpawnFromPerimeterTimer = float(fmod(rand(), 2.4f) + 1.6f);
            if ((_timerSpawnFromPerimeter.getElapsedTime().asSeconds() > enemySpawnFromPerimeterTimer)
                || (_enemies.size() <= minNumberEnemies))
            {
                spawnBasicEnemy(shipType, shipVariant, movementDirection, MovementState::SpiralIn);
            }

            // Spawn enemy wanderer
            float enemySpawnWandererTimer = float(fmod(rand(), 3.4f) + 2.6f);

            if ((_timerSpawnWanderer.getElapsedTime().asSeconds() > enemySpawnWandererTimer)
                || (_enemies.size() <= minNumberEnemies))
            {
                spawnBasicEnemy(entity::BasicWanderer, textures::EnemyShipYellow, movementDirection, MovementState::Wandering);
            }

        }
        // Spawn satellites
        if (_satellitesAlive == 0)
        {
            float satelliteSpawn = float(fmod(rand(), 5.f) + 15.f);
            if (_timerSatellite.getElapsedTime().asSeconds() > satelliteSpawn)
                spawnSatellites();
        }
        else
        {
            _timerSatellite.restart();
        }
        // Spawn meteoroids
        auto meteoroidSpawnEventTimer = fmod(rand(),8.f) + 10.f;
        if (_timerMeteoroid.getElapsedTime().asSeconds() > meteoroidSpawnEventTimer)
            spawnMeteoroid();
    }
}

void EntityController::playerShoot()
{
    auto numberOfBullets = 1;
    auto bulletOffset = 3.8f; // Adjust so bullet spawns just in front of ship
    auto bulletScale = _playerShip.getScale().x * 1.5f;

    if (_playerShip.isUpgraded())
    {
        numberOfBullets = 2;
    }

    for (auto i = 0; i < numberOfBullets; i++) // 1 or 2 bullets
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

void EntityController::enemyShoot()
{
    _enemyShootEventHasOccurred = false;
    auto minNumberEnemyBullets = 0; //rand() % 2;
    auto doNotFireInsideThisRadius = (_resolution.y / 2) * 0.05; // Only shoot when closer (5% of circle radius)
    float enemyShootTime = float(fmod(rand(),2.5f) + 3.2f);
    for (auto &enemy : _enemies)    // All enemies need a chance to shoot
    {
        if (enemy->getDistanceFromCentre() > doNotFireInsideThisRadius)
        {
            if ((enemy->getShootTimerElapsedTime() > enemyShootTime)
                || (_bulletsEnemy.size() < minNumberEnemyBullets))
            {
                enemy->resetShootTimer();
                auto bullet_enemy = std::make_unique<Bullet>(_resolution,
                                                             enemy->getRadius(),
                                                             enemy->getAngle(),
                                                             0.3,
                                                             entity::EnemyBullet,
                                                             _textureHolder,
                                                             textures::BulletEnemy);

                _bulletsEnemy.push_front(move(bullet_enemy));
                _enemyShootEventHasOccurred = true;
            }
        }
    }
}

void EntityController::shoot()
{
    // Player shooting (Bullet creation)
    if (_playerShip.isShooting())
        playerShoot();

    // Enemy Shooting
    enemyShoot();
}

const bool EntityController::shootingOccurred()
{
    return _enemyShootEventHasOccurred;
}

void EntityController::setEnemyMoveState()
{
    auto growShipScreenZone = _resolution.y/5.f; // Prevents change in behaviour near boundary
    auto shipClipScreenZone = _resolution.y/2.5f; // Prevents change in behaviour near boundary
    auto minimumRadius = (_resolution.y/2)*0.06; // Specifies minimum radius that within no behaviour changes occur

    for (auto &enemy : _enemies)
    {
        // Generic properties for each enemy. defined in the loop as per enemy specific
        auto currentEnemyMovementState = enemy->getMovementState();
        auto currentEnemyRadius = enemy->getRadius();
        auto currentEnemyType = enemy->getType();
        if ((currentEnemyRadius > _resolution.y / 2.f)  // Don't leave game play area, re-spawn in centre after leaving
             || ((currentEnemyMovementState == MovementState::SpiralIn) && (currentEnemyRadius < minimumRadius))) // Reset from spiral inwards
        {
            enemy->reset();
        }
        else
        {
            // Random values to define ship movement
            auto randomStateChange = rand()%100+1; // 1 to 100%, chance to change state

            // Chance that the ship will enter a new movement state
            if (((currentEnemyType  == entity::Basic) || (currentEnemyType  == entity::BasicAlternate)) // Only apply changes to normal ships
                && (currentEnemyRadius > growShipScreenZone)  // Don't change state if ship is too small
                && (currentEnemyRadius < shipClipScreenZone)) // Don't change state if ship is too big and is going to fly off screen
            {

                if (randomStateChange < 6)                                          // 5% chance
                {
                    enemy->setMovementState(MovementState::CircleOffsetLeft);
                }
                if (randomStateChange > 6 && randomStateChange < 13)                // 5% chance
                {
                    enemy->setMovementState(MovementState::CircleOffsetRight);
                } else if ((randomStateChange > 50) && (randomStateChange < 52))    // 2% chance
                {
                    enemy->setMovementState(MovementState::SpiralIn);
                } else if (randomStateChange == 60)                                 // 1% change
                {
                    enemy->setMovementState(MovementState::SpiralOut);
                }
            }
            setEnemyMove(enemy, currentEnemyMovementState, growShipScreenZone, currentEnemyRadius);
        }
    }
}

void EntityController::setEnemyMove(std::unique_ptr<Enemy> &enemy,
                                    MovementState currentEnemyMovementState,
                                    float growShipScreenZone,
                                    float currentEnemyRadius)
{

    auto shipCircleRadius = _resolution.y / 3.f;    // Size of spiral side circle radius
    auto shipOffsetIncrement = rand() % 3 + 1.f;    // How circle offset changes
    auto shipRadiusIncrease = rand() % 3 + 1.f;     // How much to increment the ship radius by
    auto distantSpeedMultiplier = 10.f;             // How fast the ship circles grow in the small region of the screen
    auto satelliteGrowIncrement = 2.0f;             // Satellites grow at a different rate, faster than other entities
    auto randomAngle = rand() % 2 + 2.0f;           // Constantly increasing random angle of rotation
    auto perlinNoiseAngleOffset = 5.0f;             // Size of angle offset used in perlinNoise movement
    auto perlinNoiseSpeedScaler = 3.0f;             // Scales speed of perlinNoise
    auto perlinRadiusOffset = 70.0f;                // Change in radius for perlinNoise


    auto currentEnemyDirectionSign = enemy->getMovementDirectionSign();
    auto currentEnemyTimeAlive = enemy->getAliveTimeElapsedTime();
    auto currentEnemyCentre = enemy->getCentre();


    // Movement (based on behaviour state)
    switch (currentEnemyMovementState)
    {
        case (MovementState::SpiralOut) : // Standard spiral-out movement
        {
            if (currentEnemyRadius < growShipScreenZone) // Grow faster if close to the centre
            {
                enemy->setMove(randomAngle * _speedModifier,
                               shipRadiusIncrease * distantSpeedMultiplier * _speedModifier,
                               currentEnemyCentre);
            }
            else
                enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                               shipRadiusIncrease * _speedModifier,
                               currentEnemyCentre);
            break;
        }

        case (MovementState::SpiralIn) : // Spiral in movement. decrement the radius
        {
            enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                           -shipRadiusIncrease * _speedModifier,
                           currentEnemyCentre);
            break;
        }

        case (MovementState::CircleOffsetRight) : // Perform a "circle" move Right, by offsetting centre of circle
        {
            if (currentEnemyCentre.x < shipCircleRadius)
            {
                enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                               0,
                               {currentEnemyCentre.x + shipOffsetIncrement, currentEnemyCentre.y});
            }
            else
            {
                enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                               +shipRadiusIncrease * _speedModifier,
                               currentEnemyCentre);
            }
            break;
        }

        case (MovementState::CircleOffsetLeft) : // Perform a "circle" move Left, by offsetting centre of circle
        {
            if (currentEnemyCentre.x > -shipCircleRadius)
            {
                enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                               0,
                               {currentEnemyCentre.x - shipOffsetIncrement, currentEnemyCentre.y});
            }
            else
            {
                enemy->setMove(randomAngle * currentEnemyDirectionSign * _speedModifier,
                               +shipRadiusIncrease * _speedModifier,
                               currentEnemyCentre);
            }
            break;
        }

        case (MovementState::SmallCircling) : // Small circle movement, used for satellites
        {
            enemy->setMove(randomAngle * _speedModifier,
                           satelliteGrowIncrement,
                           currentEnemyCentre);
            break;
        }

        case (MovementState::Wandering): // Set the angle and radius position based on a perlinNoise value
        {
            //calculate a angle and radius change based on the perlinNoise generator that is then scaled and offset
            auto perlinX = float(_xNoise.noise(currentEnemyTimeAlive) * perlinNoiseAngleOffset -
                             floor(perlinNoiseAngleOffset / 2));
            auto perlinY = float((_yNoise.noise(currentEnemyTimeAlive / perlinNoiseSpeedScaler) * perlinRadiusOffset -
                                  perlinRadiusOffset / 2));

            enemy->setMove(perlinX * currentEnemyDirectionSign * _speedModifier,
                           perlinY * _speedModifier,
                           {0, 0});
            break;
        }
    }
}

void EntityController::setBulletMove()
{
    for (auto &bullet : _bulletsPlayer)
    {
        bullet->setMove(-_bulletPlayerSpeed);
    }

    for (auto &bullet : _bulletsEnemy)
    {
        bullet->setMove(_bulletEnemySpeed * _speedModifier);
    }
}

void EntityController::setMeteoroidMove()
{
    for (auto &meteoroid : _meteoroids)
    {
        meteoroid->setMove(_meteoroidSpeed * _speedModifier);
    }
}

void EntityController::setMove()
{
    setBulletMove();
    setMeteoroidMove();
    setEnemyMoveState();
}

void EntityController::update()
{
    for (auto &enemy : _enemies)
        enemy->update();

    for (auto &bullet : _bulletsPlayer)
    {
        bullet->update();
    }

    for (auto &bullet : _bulletsEnemy)
    {
        bullet->update();
    }

    for (auto &meteoroid : _meteoroids)
    {
        meteoroid->update();
    }

    for (auto &explosion : _explosions)
        explosion->update();

    // Reset shoot and explosion events
    _explosionHasOccurred = false;
    _enemyShootEventHasOccurred = false;
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
                                                             (*enemy)->getAngle(),
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
            }
            else
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
            }
            else
                bullet++;
        }
    }
}
void EntityController::checkEnemyBulletsToPlayerShipCollisions()
{
    // EnemyBullets -> PlayerShip (player explodes + dies, bullet disappears)
    for (auto bullet = _bulletsEnemy.begin(); bullet != _bulletsEnemy.end();)
    {
        if (collides(_playerShip.getSprite(), (*bullet)->getSprite()))
        {
            auto explosion = std::make_unique<Explosion>(_resolution,
                                                         _playerShip.getDistanceFromCentre(),
                                                         _playerShip.getAngle(),
                                                         _playerShip.getScale().x * 2,
                                                         entity::Explosion,
                                                         _textureHolder,
                                                         textures::Explosion);
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
{
    // Meteoroids -> PlayerShip (player explodes + dies, meteor keeps going)
    for (auto meteoroid = _meteoroids.begin(); meteoroid != _meteoroids.end(); meteoroid++)
    {
        if (collides(_playerShip.getSprite(), (*meteoroid)->getSprite()))
        {
            auto explosion = std::make_unique<Explosion>(_resolution,
                                                         _playerShip.getDistanceFromCentre(),
                                                         _playerShip.getAngle(),
                                                         (*meteoroid)->getScale().x,
                                                         entity::Explosion,
                                                         _textureHolder,
                                                         textures::Explosion);
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
{
    // Enemy <-> PlayerShip (enemy explodes, player dies)
    for (auto enemy = _enemies.begin(); enemy != _enemies.end();)
    {
        if (collides(_playerShip.getSprite(), (*enemy)->getSprite()))
        {
            auto explosion = std::make_unique<Explosion>(_resolution,
                                                         _playerShip.getDistanceFromCentre(),
                                                         _playerShip.getAngle(),
                                                         (*enemy)->getScale().x * 2,
                                                         entity::Explosion,
                                                         _textureHolder,
                                                         textures::Explosion);
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
    // Clip away projectiles (bullets/meteoroids) outside cylindrical frustum at playerShip Camera plane
    for (auto bullet = _bulletsEnemy.begin(); bullet != _bulletsEnemy.end();)
    {
        if ((*bullet)->getRadius() > _resolution.y / 2)
        {
            bullet = _bulletsEnemy.erase(bullet);
        }
        else
            bullet++;
    }

    for (auto meteoroid = _meteoroids.begin(); meteoroid != _meteoroids.end();)
    {
        if ((*meteoroid)->getRadius() > _resolution.y / 2)
        {
            meteoroid = _meteoroids.erase(meteoroid);
        }
        else
            meteoroid++;
    }

    // Clip away player bullets at centre
    auto radius_buffer = 20;
    for (auto bullet = _bulletsPlayer.begin(); bullet != _bulletsPlayer.end();)
    {
        if (((*bullet)->getPosition().x > (_resolution.x / 2) - radius_buffer)
            && ((*bullet)->getPosition().y > (_resolution.y / 2) - radius_buffer)
            && ((*bullet)->getPosition().x < (_resolution.x / 2) + radius_buffer)
            && ((*bullet)->getPosition().y < (_resolution.y / 2) + radius_buffer))
        {
            bullet = _bulletsPlayer.erase(bullet);
        }
        else
            bullet++;
    }

    // Remove any finished explosions
    for (auto explosion = _explosions.begin(); explosion != _explosions.end();)
    {
        if ((*explosion)->getLives() == 0)
        {
            explosion = _explosions.erase(explosion);
        }
        else
            explosion++;
    }
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

const bulletList& EntityController::getBulletsPlayer() const
{
    return _bulletsPlayer;
}

const bulletList& EntityController::getBulletsEnemy() const
{
    return _bulletsEnemy;
}

const enemyList& EntityController::getEnemies() const
{
    return _enemies;
}

const meteoroidList& EntityController::getMeteoroids() const
{
    return _meteoroids;
}

const explosionList& EntityController::getExplosions() const
{
    return _explosions;
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