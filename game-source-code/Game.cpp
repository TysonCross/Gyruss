/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   Main Game controller implementation
///
/// Implements the Game loop, and game states
///
/// Music by Eric Matyas (www.http://soundimage.org)
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Game.hpp"

void Game::Start()
{
    // Todo: Need to choose better way to set the resolution. settings screen and set Resource perhaps?
     _resolution = sf::Vector2i{1920,1080};

    sf::Image icon;
    if (!icon.loadFromFile("resources/icon.png")) return ;

    loadResources();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    _mainWindow.create(sf::VideoMode(_resolution.x, _resolution.y, 32),
                       "Gyruss",
                       sf::Style::Close,
                       settings);

    _mainWindow.setMouseCursorVisible(false);
    _mainWindow.setVerticalSyncEnabled(true);
    _mainWindow.setIcon(32, 32, icon.getPixelsPtr());


    while (_gameState != game::GameState::Exiting)
    {
        initializeGameLoop();
    }
    Quit();
}

void Game::Quit()
{
    _mainWindow.close();
}

void Game::initializeGameLoop()
{
    sf::Clock clock;
    sf::Clock shootTimer;
    sf::Clock enemyTimer;
    sf::Clock enemyTimer2;
    sf::Time timeSinceUpdate = sf::Time::Zero;
    float timeStep = 1.f / 60.f;

    _inputHandler.reset();

#ifdef DEBUG
    FPS fps;
#endif // DEBUG

    auto shaking = 0; // Controls the shaking of the main renderWindow when a player loses a life
    auto pos = _mainWindow.getPosition();
    _mainWindow.clear(sf::Color::Black);

    //First Game State
    if (_gameState == game::GameState::Splash)
        showSplashScreen();

    if (_gameState == game::GameState::GameOver)
        showGameOverScreen();

    ///-------------------------------------------
    ///  Game Playing starts
    ///-------------------------------------------
    sf::Music music;
    music.setLoop(true);
    music.setVolume(25);
    if (!music.openFromFile("resources/game_music.ogg"))
    {
        _gameState = game::GameState::Exiting;
        return;// error
    }
    else
        music.play();

    auto number_of_stars = 60;
    StarField starField(_resolution, 3, number_of_stars);

    //Set the player circle radius
    // Todo: Config.ini file
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (_resolution.y / 2) - (_resolution.y * shipPathRadiusPadding);
    const auto shipScale = 0.28;
    PlayerShip playerShip(_resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          _textures,
                          _sounds);

    // Todo: Enemy creation
    // Temp
    std::vector<std::unique_ptr<Enemy>> enemyVector;
    std::vector<std::unique_ptr<Bullet>> bulletPlayerVector;
    std::vector<std::unique_ptr<Bullet>> bulletEnemyVector;
    std::vector<std::unique_ptr<Explosion>> explosionVector;

    ///-------------------------------------------
    ///  Main Game Loop (time advance)
    ///-------------------------------------------

    while (_gameState == game::GameState::Playing)
    {
        sf::Event event;
        while (_mainWindow.pollEvent(event))
        {
            _inputHandler.pollInput(_gameState,
                                    playerShip, // Could be entityHandler?
                                    event);
        }

        ///-------------------------------------------
        /// Events
        ///-------------------------------------------
        timeSinceUpdate += clock.getElapsedTime();
        clock.restart();

        ///-------------------------------------------
        ///  Fixed Timestep
        ///-------------------------------------------
        while (timeSinceUpdate.asSeconds() >= timeStep)
        {
            timeSinceUpdate = sf::Time::Zero;
            _inputHandler.update(playerShip, timeStep);


            // entityController.create(); // All entity updates (move updates?)
            // entityController.move()
            // entityController.shoot()

            // Create enemies
            ///////////////////////////////////////////////////////

            if (enemyTimer.getElapsedTime().asSeconds() > (rand()%3 + 2))
            {
                enemyTimer.restart();
                auto enemy = std::make_unique<Enemy>(_resolution,
                                                     0, 0, 1,
                                                     _textures,
                                                     _sounds,
                                                     textures::EnemyShipGrey);
                enemyVector.push_back(std::move(enemy));
            }

            if (enemyTimer2.getElapsedTime().asSeconds() > (rand()%4 + 3))
            {
                enemyTimer2.restart();
                auto enemy = std::make_unique<Enemy>(_resolution,
                                                     0, 0, 1,
                                                     _textures,
                                                     _sounds,
                                                     textures::EnemyShipPurple);
                enemyVector.push_back(std::move(enemy));
            }

            // PlayerBullet creation
            if (playerShip.isShooting())
            {
                auto bullet = std::make_unique<Bullet>(_resolution,
                                                       playerShip.getDistanceFromCentre(),
                                                       playerShip.getAngle(),
                                                       0.5,
                                                       _textures,
                                                       textures::BulletPlayer);
                bulletPlayerVector.push_back(std::move(bullet));
            }


            // Move enemies
            for (auto &enemyShip : enemyVector)
            {
                if (enemyShip->getRadius() > _resolution.y / 2.f)
                {
                    auto random_angle = (rand() % 3 + 2.0f);
                    auto random_move = rand() % 10 + (-2);
                    auto playableZoneRadiusFactor = 8;
                    if (enemyShip->getDistanceFromCentre() < _resolution.y / playableZoneRadiusFactor)
                    {
                        enemyShip->setMove(1 + random_angle, 18);
                    } else
                    {
                        enemyShip->setMove(random_angle, random_move);
                    }
                } else
                {
                    enemyShip->reset();
                }

                // Enemies shoot
                if (shootTimer.getElapsedTime().asMilliseconds() > (rand() % 2000 + 100))
                {
                    shootTimer.restart();
                    auto bullet_enemy = std::make_unique<Bullet>(_resolution,
                                                                 enemyShip->getDistanceFromCentre(),
                                                                 enemyShip->getAngle(),
                                                                 0.5,
                                                                 _textures,
                                                                 textures::BulletEnemy);

                    enemyShip->setShoot();
                    bulletEnemyVector.push_back(std::move(bullet_enemy));
                }
            }

            // Temp enemy generation hack ends here
            //////////////////////////////////////////////////////////////

            // entityController.checkCollides();

            // ToDo: Check Collisions
            // Enemy -> PlayerShip operations: (number_of_active_enemy)
            for (auto enemy = enemyVector.begin(); enemy != enemyVector.end();)
            {
                if (collides(playerShip.getSprite(), (*enemy)->getSprite()))
                {
                    auto explosion = std::make_unique<Explosion>(_resolution,
                                                                 playerShip.getDistanceFromCentre(),
                                                                 playerShip.getAngle(),
                                                                 (*enemy)->getScale().x * 2,
                                                                 _textures,
                                                                 _sounds,
                                                                 textures::Explosion);
                    explosionVector.push_back(std::move(explosion));
                    playerShip.die();
                    _inputHandler.reset();
                    shaking = 1;
                    enemy = enemyVector.erase(enemy);
                } else
                {
                    ++enemy;
                }
            }

            // PlayerBullets -> Enemy operations :(number_of_active_bullets * number_of_active_enemies)
            for (auto enemy = enemyVector.begin(); enemy != enemyVector.end();++enemy)
            {
                for (auto bullet = bulletPlayerVector.begin(); bullet != bulletPlayerVector.end();)
                {
                    if (collides((*bullet)->getSprite(), (*enemy)->getSprite()))
                    {
                        bullet = bulletPlayerVector.erase(bullet);
                        (*enemy)->die();
                    } else
                    {
                        ++bullet;
                    }
                }
            }

            // EnemyBullets -> PlayerShip operations:(number_of_enemy_bullets)
            for (auto enemy = enemyVector.begin(); enemy != enemyVector.end();)
            {
                if ((*enemy)->getLives()==0)
                {
                    auto explosion = std::make_unique<Explosion>(_resolution,
                                                                 (*enemy)->getDistanceFromCentre(),
                                                                 (*enemy)->getAngle(),
                                                                 (*enemy)->getScale().x * 2,
                                                                 _textures,
                                                                 _sounds,
                                                                 textures::Explosion);
                    explosionVector.push_back(std::move(explosion));
                    enemy = enemyVector.erase(enemy);
                } else
                {
                    ++enemy;
                }
            }

            // EnemyBullets -> die events operations:(number_of_enemy_bullets)
            for (auto bullet = bulletEnemyVector.begin(); bullet != bulletEnemyVector.end();)
            {
                if (collides(playerShip.getSprite(), (*bullet)->getSprite()))
                {
                    auto explosion = std::make_unique<Explosion>(_resolution,
                                                                 playerShip.getDistanceFromCentre(),
                                                                 playerShip.getAngle(),
                                                                 playerShip.getScale().x * 2,
                                                                 _textures,
                                                                 _sounds,
                                                                 textures::Explosion);
                    playerShip.die();
                    _inputHandler.reset();
                    shaking = 1;
                    bullet = bulletEnemyVector.erase(bullet);
                } else
                {
                    ++bullet;
                }
            }

            // Kill explosions that are finished (that are inactive)
            for (auto explosion = explosionVector.begin(); explosion != explosionVector.end();)
            {
                if ((*explosion)->getLives() == 0)
                {
                    explosion = explosionVector.erase(explosion);
                } else
                {
                    ++explosion;
                }
            }

            // entityController.checkClipping();

            // Clipping of bullets outside frustum (make inactive)
            for (auto bullet = bulletEnemyVector.begin(); bullet != bulletEnemyVector.end();)

            {
                if ((*bullet)->getRadius() > _resolution.y / 2.f)
                {
                    bullet = bulletEnemyVector.erase(bullet);
                } else
                {
                    ++bullet;
                }
            }

            // Clipping of playerBullets (make inactive)
            for (auto bullet = bulletPlayerVector.begin(); bullet != bulletPlayerVector.end();)
            {
                if(((*bullet)->getSprite().getPosition().x > (_resolution.x/2) - 10)
                    && ((*bullet)->getSprite().getPosition().y > (_resolution.y/2) - 10)
                    && ((*bullet)->getSprite().getPosition().x < (_resolution.x/2) + 10)
                    && ((*bullet)->getSprite().getPosition().y < (_resolution.y/2) + 10))
                {
                    bullet = bulletPlayerVector.erase(bullet);
                } else
                {
                    ++bullet;
                }
            }

            // entityController update();
            // ToDo: Update all movement and perform actions
            playerShip.update();

            for (auto &enemyShip : enemyVector)
            {
                enemyShip->update();
            }

            for(auto &bullet : bulletPlayerVector)
            {
                bullet->update();
                bullet->setMove(-25);
            }

            for(auto &bullet : bulletEnemyVector)
            {
                bullet->update();
                bullet->setMove(20);
            }

            for(auto &explosion : explosionVector)
            {
                explosion->update();
            }

            //  Render
            _mainWindow.clear(sf::Color::Black);
            // /ToDo: Draw all the visible objects
            for (const auto &element : starField.getStarField())
                starField.moveAndDrawStars(_mainWindow);

            //////////////////////////////////////////////////////////////////
            // Temp Enemy draw hack
            for (auto &enemyShip : enemyVector)
            {
                _mainWindow.draw(enemyShip->getSprite());
            }

            for(auto &bullet : bulletPlayerVector)
            {
                _mainWindow.draw(bullet->getSprite());
            }

            for(auto &bullet : bulletEnemyVector)
            {
                _mainWindow.draw(bullet->getSprite());
            }

            for(auto &explosion : explosionVector)
            {
                _mainWindow.draw(explosion->getSprite());
            }
            // Temp enemy draw hack ends here
            ///////////////////////////////////////////////////////

            _mainWindow.draw(playerShip.getSprite());


            while (shaking > 0)
            {
                sf::Event event;
                while (_mainWindow.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed) _mainWindow.close();
                }

                if (shaking > 0)
                {
                    auto pos_temp = pos;
                    _mainWindow.setPosition(sf::Vector2i(pos_temp.x + rand() % 25, pos_temp.y + rand() % 25));

                    if (++shaking >= 5)
                        shaking = 0;
                }
                _mainWindow.display();
            }

            _mainWindow.setPosition(pos);
            _mainWindow.display();

#ifdef DEBUG
            fps.update();
            std::ostringstream ss;
            ss << fps.getFPS();
            _mainWindow.setTitle(ss.str());
#endif // DEBUG

            if (playerShip.getLives() <= 0)
            {
                _gameState = game::GameState::GameOver;
            }
        }
    }
}

void Game::showSplashScreen()
{
    SplashScreen splashScreen;
    if (splashScreen.show(_mainWindow,_textures,_sounds, _fonts, _resolution) == 0)
    {
        _gameState = game::GameState::Playing;
        return;
    }
    _gameState = game::GameState::Exiting;
}

void Game::showGameOverScreen()
{
    GameOverScreen gameOverScreen;
    if (gameOverScreen.show(_mainWindow,_textures,_sounds, _fonts, _resolution) == 0)
    {
        _gameState = game::GameState::Splash;
        return;
    }
    _gameState = game::GameState::Exiting;
}

bool Game::collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
{
    auto shrink_factor = 4.f + 0.2f;
    float radius_1 = (sprite1.getGlobalBounds().width + sprite1.getGlobalBounds().height) / shrink_factor;
    float radius_2 = (sprite2.getGlobalBounds().width + sprite2.getGlobalBounds().height) / shrink_factor;
    float distance_x = sprite1.getPosition().x - sprite2.getPosition().x;
    float distance_y = sprite1.getPosition().y - sprite2.getPosition().y;

    return  radius_1 + radius_2 >= sqrt((distance_x * distance_x) + (distance_y * distance_y));
}

void Game::loadResources()
{
    //Load Textures and Sounds
    _textures.load(textures::SplashScreen,"resources/splash.png");
    _textures.load(textures::GameOverScreen,"resources/gameover.png");
    _textures.load(textures::SplashControls,"resources/splash_controls.png");
    _textures.load(textures::PlayerShip,"resources/player_ship_animated.png");
    _textures.load(textures::BulletPlayer,"resources/bullet_player.png");
    _textures.load(textures::BulletEnemy,"resources/bullet_enemy.png");
    _textures.load(textures::EnemyShipGrey,"resources/enemyship_grey.png");
    _textures.load(textures::EnemyShipPurple,"resources/enemyship_purple.png");
    _textures.load(textures::Explosion,"resources/explosion.png");
//    _textures.load(textures::EnemyShipGenerator,"resource/generator.png");
//    _textures.load(textures::Meteoroid,"resource/meteoroid.png");
//    _textures.load(textures::Satellite,"resource/satellite.png");

    _sounds.load(sounds::StartSound,"resources/startup.ogg");
    _sounds.load(sounds::SpawnSound,"resources/ship_spawn.ogg");
    _sounds.load(sounds::GameOverSound,"resources/gameover.ogg");
    _sounds.load(sounds::PlayerMove,"resources/thrust.ogg");
    _sounds.load(sounds::PlayerShoot,"resources/shoot_laser.ogg");
    _sounds.load(sounds::EnemyShoot,"resources/shoot_phaser.ogg");
    _sounds.load(sounds::PlayerDeath,"resources/player_death.ogg");
    _sounds.load(sounds::Explosion,"resources/player_death.ogg");
    _fonts.load(fonts::Title,"resources/danube.ttf");
    _fonts.load(fonts::Info,"resources/fax_sans_beta.otf");
}
