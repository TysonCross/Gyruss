/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Controller and manager for game entity objects
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
#include "Meteoroid.hpp"
#include "Score.hpp"
#include "PerlinNoise.hpp"

using entityList = std::list<std::unique_ptr<Entity>>;
using bulletList = std::list<std::unique_ptr<Bullet>>;
using enemyList = std::list<std::unique_ptr<Enemy>>;
using explosionList = std::list<std::unique_ptr<Explosion>>;
using meteoroidList = std::list<std::unique_ptr<Meteoroid>>;

////////////////////////////////////////////////////////////
/// \brief EntityController Class, used to manage the process of all game objects, such as bullets,
/// enemy ships and Meteroids.
////////////////////////////////////////////////////////////
class EntityController
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor for the EntityController class. Called directly
    /// from game object to handel the creation, destruction and drawing of all game objects.
    ///
    /// On every game frame, respective functions are called to evaluate game entity states, such
    /// as spawning new enemies, collisions and enemy bullet shooting
    ///
    /// \param resolution The Screen resolution of the game
    /// \param playerShip The playership, generated from the game.cpp. needed for collision detection
    /// \param textures used to create new entities that require this class for creation
    /// \param score object to track the current game score, enemies killed and player deaths. created in game.cpp
    /// \param speedModifier defines how fast the game runs at a particular time to speed up game as time progresses
    ///
    /// \see sf::Vector2i
    /// \see PlayerShip.hpp
    /// \see Score.hpp
    /// \see ResourceHolder.hpp
    ///////////////////////////////////////////////////////////////
    EntityController(sf::Vector2i resolution,
                     PlayerShip &playerShip,
                     TextureHolder &textures,
                     Score &score,
                     float speedModifier);

    ////////////////////////////////////////////////////////////
    /// \brief Spawns an enemy of a defined id and variant in a spiral direction(movementState)
    /// function is called from spawnEntities
    ///
    /// This function includes: spiral inwards, spiral outwards and wandering movement
    ///
    /// \param id defines the kind of ship spawned
    /// \param shipVariant defines the look of the ship spawned
    /// \param movementDirection enum, showing clockwise or counterclockwise ship direction
    /// \param movementState spesifies what kind of spiral the ship is doing: inwards, outwards or wandering
    ///
    /// \see Enemy.hpp
    ////////////////////////////////////////////////////////////
    void spawnSpiral(entity::ID id,
                     textures::ID shipVariant,
                     MovementDirection movementDirection,
                     MovementState movementState);

    ////////////////////////////////////////////////////////////
    /// \brief Spawns a meteoroid
    /// function is called from spawnEntities
    ///
    /// \see Meteoroid.hpp
    ////////////////////////////////////////////////////////////
    void spawnMeteoroid();

    ////////////////////////////////////////////////////////////
    /// \brief Spawns a Satellite, a type of Enemy.
    /// function is called from spawnEntities
    ///
    /// \see Enemy.hpp
    ////////////////////////////////////////////////////////////
    void spawnSatellites();

    ////////////////////////////////////////////////////////////
    /// \brief inititates the spawn event for enemies, satellites and Meteoroid
    ///
    /// Defines the spawn chances based on a combination of delay between spawns
    /// and random event chances. Has imposed maximum & minimum number of enemys
    /// that can be alive at one time
    ///
    /// \see Enemy.hpp
    /// \see spawnMeteoroid
    /// \see spawnSatellites
    /// \see spawnSpiral
    /// \see Enemy.hpp
    /// \see Meteorid.hpp
    ////////////////////////////////////////////////////////////
    void spawnEntities();

    ////////////////////////////////////////////////////////////
    /// \brief initiates a player shoot event based on current gun level
    /// and adds bullet to bullet vector
    ///
    /// \see PlayerShip.hpp
    ////////////////////////////////////////////////////////////
    void playerShoot();

    ////////////////////////////////////////////////////////////
    /// \brief initiates a player shoot event based on current gun level
    /// and adds bullet to bullet vector
    ///
    /// \see playerShoot()
    ////////////////////////////////////////////////////////////
    void shoot();

    ////////////////////////////////////////////////////////////
    /// \brief changes enemy movement state based on current ship position and
    /// random chance to change flight pattern
    ///
    /// This function is directly responsible for how the game plays.
    /// Actual movements are done by preformEnemyMove
    ///
    /// \see preformEnemyMove()
    ////////////////////////////////////////////////////////////
    void setMove();

    ////////////////////////////////////////////////////////////
    /// \brief Executes ship movement, based on ship movement state defined in
    /// setMove function
    ///
    /// Programmatic method of moving ships around, based on movement state
    ///
    /// \param enemy enemy ship to be moved
    /// \param currentEnemyMovementState movement state that the ship should preform operation in. be it spiral in or others
    /// \param growShipScreenZone defines region where the ship should grow and not change state
    /// \param currentEnemyRadius defines the current size of the enemy ship
    ///
    /// \see setMove()
    /// \see Enemy.hpp
    ////////////////////////////////////////////////////////////
    void preformEnemyMove(std::unique_ptr<Enemy> &enemy,
                          MovementState currentEnemyMovementState,
                          float growShipScreenZone,
                          float currentEnemyRadius);

    ////////////////////////////////////////////////////////////
    /// \brief checks all playerShips to see if they are outside of the play range.
    /// In the event that they are, remove them from the game(reset the ships)
    ////////////////////////////////////////////////////////////
    void checkClipping();

    ////////////////////////////////////////////////////////////
    /// \brief Responsible for dealing with all collision with all game objects.
    /// PlayerBullet->Enemy, EnemyBullet->PlayerShip, PlayerBullet->EnemyBullet,
    ///
    /// In the event that they are, remove them from the game (reset the ships or delete bullets).
    /// Also responsible for generating explosion events on ship deaths
    ///
    /// \see collides()
    ///
    /// \return a bool, true if collision occurred with playerShip. false if not.
    ////////////////////////////////////////////////////////////
    bool checkCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief used to check for collisions between two sprites
    ///
    /// \param sprite1 first sprite that is fed in, compared to sprite2
    /// \param sprite2 second sprite that is fed in, compared to sprite1
    ///
    /// \see checkCollision()
    ///
    /// \return a bool, true if collision, false if not
    ////////////////////////////////////////////////////////////
    bool collides(const sf::Sprite &sprite1,
                  const sf::Sprite &sprite2);

    ////////////////////////////////////////////////////////////
    /// \brief Updates all game objects by calling the underlying update functions.
    /// Called on every frame, to move entities around the screen as well as other functions
    ////////////////////////////////////////////////////////////
    void update();

    ////////////////////////////////////////////////////////////
    /// \brief used to draw all game elements by looping over all vectors of entites
    /// and drawing the underlying sprite. Called on every frame.
    ///
    /// \param renderWindow feeds in the draw window to enable the Entity controlor to draw on the current window
    ///
    /// \see sf::RenderWindow
    ////////////////////////////////////////////////////////////
    const void draw(sf::RenderWindow &renderWindow);

    ////////////////////////////////////////////////////////////
    /// \brief Getter to return if an explosion has occurred on the current frame.
    /// Used to deal with multiple explosions occurred in quick succession to reset
    /// the explosion object and sound generation.
    ///
    /// \see SoundController.hpp
    ///
    /// \return a bool relating to if an explosion occurred in the current frame
    ////////////////////////////////////////////////////////////
    const bool explosionOccurred();

    ////////////////////////////////////////////////////////////
    /// \brief Getter to return if an bullet has been shot in the current frame
    ///
    /// \return a bool relating to if a bullet was fired in the current frame
    ////////////////////////////////////////////////////////////
    const bool shootingOccurred();

    ////////////////////////////////////////////////////////////
    /// \brief adjust the game speed as time goes on to make it more challenging.
    /// Has imposed maximum, minimum and default interval values.
    ///
    /// \param amount defines the amount to increase the global speed by
    ////////////////////////////////////////////////////////////
    void changeGlobalSpeed(float amount);

    ////////////////////////////////////////////////////////////
    /// \brief Reverts the game speed to the stock default value
    ////////////////////////////////////////////////////////////
    void resetGlobalSpeed();

    ////////////////////////////////////////////////////////////
    /// \brief Getter to return the current game speed
    ///
    /// \return the current speed of the gameplay
    ////////////////////////////////////////////////////////////
    const float getSpeed() const;

    ////////////////////////////////////////////////////////////
    /// \brief Destroys all enemies of a particular type. This is useful
    /// When a game event requires all of one type of enemy to be removed. For example,
    /// if the player dies, all satellites that are still alive should be removed.
    ///
    /// \param type defines the type of enemy to kill
    ////////////////////////////////////////////////////////////
    void killAllEnemiesOfType(entity::ID type);

private:
    ////////////////////////////////////////////////////////////
    /// \brief checks collisions between EnemyShips->PlayerShip,
    /// removing both entities if they collide
    ////////////////////////////////////////////////////////////
    void checkEnemyToPlayerShipCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief checks collisions between EnemyBullet->PlayerShip,
    /// removing both entities if they collide
    ////////////////////////////////////////////////////////////
    void checkEnemyBulletsToPlayerShipCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief checks collisions between PlayerBullet->EnemyShip,
    /// removing both entities if they collide
    ////////////////////////////////////////////////////////////
    void checkPlayerBulletsToEnemyCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief checks collisions between Meteoroid->PlayerShip,
    /// removing both entities if they collide
    ////////////////////////////////////////////////////////////
    void checkMeteoroidToPlayerShipCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief checks collisions between PlayerBullet->Meteoroid,
    /// removing only the bullet if they collide (meteoroid are
    /// invulnerable but bullets must still be removed)
    ////////////////////////////////////////////////////////////
    void checkPlayerBulletsToMeteoroidCollisions();

    ////////////////////////////////////////////////////////////
    /// \brief used when any enemy is killed to preform additional enemy type
    /// spesific logic, such as upgrading a gun kf all satellites are killed
    ///
    /// \param type defines the type of enemy that is killed
    ////////////////////////////////////////////////////////////
    void enemyKilled(entity::ID type);

    ////////////////////////////////////////////////////////////
    /// \brief Called to upgrade the PlayerShip
    ////////////////////////////////////////////////////////////
    void upgradePlayerShip();

    ////////////////////////////////////////////////////////////
    /// \brief PlayerShip object generated from game.cpp. Is a reference
    /// as is not created in the EntityController
    ////////////////////////////////////////////////////////////
    PlayerShip& _playerShip;

    ////////////////////////////////////////////////////////////
    /// \brief Vector to store the screen size
    ////////////////////////////////////////////////////////////
    sf::Vector2i _resolution;

    ////////////////////////////////////////////////////////////
    /// \brief Texture holder, to access all game assets loaded in other context.
    /// Is a reference as is not created in the EntityController
    ////////////////////////////////////////////////////////////
    TextureHolder& _textureHolder;

    ////////////////////////////////////////////////////////////
    /// \brief A vector of unique_ptr of type <Bullet> to store all Enemy Bullets
    ////////////////////////////////////////////////////////////
    bulletList _bulletsEnemy;

    ////////////////////////////////////////////////////////////
    /// \brief A vector of unique_ptr of type <Bullet> to store all Player Bullets
    ////////////////////////////////////////////////////////////
    bulletList _bulletsPlayer;

    ////////////////////////////////////////////////////////////
    /// \brief A vector of unique_ptr of type <Enemy> to store all Enemy ships
    ////////////////////////////////////////////////////////////
    enemyList _enemies;

    ////////////////////////////////////////////////////////////
    /// \brief A vector of unique_ptr of type <Explosion> to store current explosion objects
    ////////////////////////////////////////////////////////////
    explosionList _explosions;

    ////////////////////////////////////////////////////////////
    /// \brief A vector of unique_ptr of type <meteoroids> to store flying meteoroids
    ////////////////////////////////////////////////////////////
    meteoroidList _meteoroids;

    ////////////////////////////////////////////////////////////
    /// \brief A Clock to store time from last ship spawn from perimeter. Used to stagger
    /// the spawn event of a ship flying with this formation
    ////////////////////////////////////////////////////////////
    sf::Clock _timerSpawnFromPerimeter;

    ////////////////////////////////////////////////////////////
    /// \brief A Clock to store time from last ship spawn from centre. Used to stagger
    /// the spawn event of a ship flying with this formation
    ////////////////////////////////////////////////////////////
    sf::Clock _timerSpawnFromCentre;

    ////////////////////////////////////////////////////////////
    /// \brief A clock to store the time from when a Satellite was las spawned
    ////////////////////////////////////////////////////////////
    sf::Clock _timerSatellite;

    ////////////////////////////////////////////////////////////
    /// \brief A clock to store the time from when a meteoroid was las spawned
    ////////////////////////////////////////////////////////////
    sf::Clock _timerMeteoroid;

    ////////////////////////////////////////////////////////////
    /// \brief A clock to how long the game as been running
    ////////////////////////////////////////////////////////////
    sf::Clock _totalTime;

    ////////////////////////////////////////////////////////////
    /// \brief A score object to store the current game score state. This is fed into
    /// the Entity controller on construction and is stored as a reference.
    ////////////////////////////////////////////////////////////
    Score& _score;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean to store if an explosion has occurred on the current frame
    ///
    /// \see explosionOccurred()
    ////////////////////////////////////////////////////////////
    bool _explosionHasOccurred;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean to store if an enemy has shot a bullet in the current frame
    ///
    /// \see shootingOccurred()
    ////////////////////////////////////////////////////////////
    bool _enemyShootEventHasOccurred;

    ////////////////////////////////////////////////////////////
    /// \brief Boolean to store if the playerShip was hit in the current frame
    ///
    /// \see collides()
    ////////////////////////////////////////////////////////////
    bool _playerHasBeenHit;

    ////////////////////////////////////////////////////////////
    /// \brief float to store the current game speed modifier
    ///
    /// \see getSpeed()
    /// \see resetGlobalSpeed()
    /// \see changeGlobalSpeed()
    ////////////////////////////////////////////////////////////
    float _speedModifier;

    ////////////////////////////////////////////////////////////
    /// \brief float to store the default game speed. The game speed is reset
    /// to this value when the game starts and when the player looses a life
    ///
    /// \see resetGlobalSpeed()
    ////////////////////////////////////////////////////////////
    float _defaultSpeed;

    ////////////////////////////////////////////////////////////
    /// \brief int to count the total number of satellites that are alive at a point
    ///
    /// \see spawnSatellites()
    /// \see spawnEntities()
    ////////////////////////////////////////////////////////////
    int _satellitesAlive;

    ////////////////////////////////////////////////////////////
    /// \brief float to store the speed that a player bullet should fly at
    ////////////////////////////////////////////////////////////
    float _bulletPlayerSpeed;

    ////////////////////////////////////////////////////////////
    /// \brief float to store the speed that an enemy should fly at
    ////////////////////////////////////////////////////////////
    float _bulletEnemySpeed;

    ////////////////////////////////////////////////////////////
    /// \brief float to store the speed that a meteoroid should fly at
    ///
    /// \see spawnMeteoroid()
    ////////////////////////////////////////////////////////////
    float _meteoroidSpeed;

    ////////////////////////////////////////////////////////////
    /// \brief PerlinNoise object to store the perlinNoise X parameter used in wandering
    /// playership movement
    ////////////////////////////////////////////////////////////
    PerlinNoise _xNoise;

    ////////////////////////////////////////////////////////////
    /// \brief PerlinNoise object to store the perlinNoise Y parameter used in wandering
    /// playerShip movement
    ////////////////////////////////////////////////////////////
    PerlinNoise _yNoise;
};

#endif //PROJECT_ENTITYCONTROLLER_HPP
