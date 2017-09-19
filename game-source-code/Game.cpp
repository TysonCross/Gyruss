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
    // Todo: Need to choose better way to set the resolution. settings screen and setResource perhaps?
    _resolution.x = 1920;
    _resolution.y = 1080;

    sf::Image icon;
    if (!icon.loadFromFile("resources/icon.png"))
    {
        return ;
    }

    loadResources();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    _mainWindow.create(sf::VideoMode(_resolution.x, _resolution.y, 32),
                       "Gyruss",
                       sf::Style::Close,
                       settings );

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

#ifdef DEBUG
    FPS fps;
#endif // DEBUG

    const sf::Color black(sf::Color::Black);
    sf::Sound sound(_sounds.get(sounds::StartSound));
    sound.play();

    //First Game State
    if (_gameState == game::GameState::Splash)
        showSplashScreen();

    if (_gameState == game::GameState::GameOver)
        showSplashScreen();
    ///-------------------------------------------
    ///  Game Playing starts
    ///-------------------------------------------
    sf::Music music;
    music.setLoop(true);
    music.setVolume(25);
    if (!music.openFromFile("resources/game_music.ogg"))
        return; // error
    music.play();

    auto number_of_stars = 60;
    StarField starField(_resolution, 3, number_of_stars);

    //Set the player circle radius
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (_resolution.y / 2) - (_resolution.y * shipPathRadiusPadding);
    PlayerShip playerShip(_resolution,
                          shipPathRadius,
                          0, 0.35,
                          _textures,
                          _sounds);

    // Todo: Enemy creation
    // Temp
    std::vector<std::unique_ptr<Enemy>> enemyVector;
    std::vector<std::unique_ptr<Bullet>> bulletPlayerVector;
    std::vector<std::unique_ptr<Bullet>> bulletEnemyVector;

    ///-------------------------------------------
    ///  Main Game Loop (time advance)
    ///-------------------------------------------

    bool previousButtonState = 0;

    while (_gameState == game::GameState::Playing)
    {
        sf::Event event;
        while (_mainWindow.pollEvent(event))
        {
            _inputHandler.pollInput(_gameState,
                                    playerShip, //Should be entityHandler
                                    event,
                                    previousButtonState);
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
            // /ToDo: Check all the relevant objects and planned actions
            _inputHandler.update(playerShip, timeStep);

            // ToDo : Make bullet creation an event
            if (playerShip.isShooting())
            {
                auto bullet = std::make_unique<Bullet>(_resolution,
                                                       playerShip.getDistanceFromCentre(),
                                                       playerShip.getAngle(), 0.5,
                                                       _textures,
                                                       textures::BulletPlayer);
                bulletPlayerVector.push_back(std::move(bullet));
            }

            ///////////////////////////////////////////////////////
            // Temp Enemy generation hack
            auto i = 0;
            const auto OVERSCAN_X = _resolution.x * 0.1;
            const auto OVERSCAN_Y = _resolution.y * 0.1;

            if (enemyTimer.getElapsedTime().asSeconds() > (rand()%4 + 2))
            {
                enemyTimer.restart();
                auto enemy = std::make_unique<Enemy>(_resolution,
                                                     0, 0, 1,
                                                     _textures,
                                                     _sounds,
                                                     textures::EnemyShipGrey);
                enemyVector.push_back(std::move(enemy));
            }

            if (enemyTimer2.getElapsedTime().asSeconds() > (rand()%3 + 3))
            {
                enemyTimer2.restart();
                auto enemy = std::make_unique<Enemy>(_resolution,
                                                     0, 0, 1,
                                                     _textures,
                                                     _sounds,
                                                     textures::EnemyShipPurple);
                enemyVector.push_back(std::move(enemy));
            }


            for (auto &enemyShip : enemyVector)
            {
                if (enemyShip->getRadius() > _resolution.y / 2.f)
                {
                    i++;
                    auto random_angle = rand() % 3 + 2;
                    auto random_move = rand() % 10 + (-2);
                    if (enemyShip->getDistanceFromCentre() < _resolution.y / 8)
                    {
                        enemyShip->setMove(1 + random_angle, 16);
                    } else
                    {
                        enemyShip->setMove(random_angle, random_move);
                    }
                } else
                {
                    enemyShip->reset();
                }
                if (shootTimer.getElapsedTime().asMilliseconds() > (rand() % 2000 + 100))
                {
                    shootTimer.restart();
                    auto bullet_enemy = std::make_unique<Bullet>(_resolution,
                                                                 enemyShip->getDistanceFromCentre(),
                                                                 enemyShip->getAngle(), 0.5,
                                                                 _textures,
                                                                 textures::BulletEnemy);

                    enemyShip->setShoot();
                    bulletEnemyVector.push_back(std::move(bullet_enemy));
                }
            }


            // Temp enemy generation hack ends here
            //////////////////////////////////////////////////////////////


            // ToDo: Check Collisions
            for (auto enemy = enemyVector.begin(); enemy != enemyVector.end();)
            {
                if (collides(playerShip.getSprite(), (*enemy)->getSprite()))
                {
                    playerShip.die();
                    enemy = enemyVector.erase(enemy);
                } else
                {
                    ++enemy;
                }
            }

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

            for (auto enemy = enemyVector.begin(); enemy != enemyVector.end();)
            {
                if ((*enemy)->getLives()==0)
                {
                    enemy = enemyVector.erase(enemy);
                } else
                {
                    ++enemy;
                }
            }

                for (auto bullet = bulletEnemyVector.begin(); bullet != bulletEnemyVector.end();)
            {
                if (collides(playerShip.getSprite(), (*bullet)->getSprite()))
                {
                    playerShip.die();
                    bullet = bulletEnemyVector.erase(bullet);
                } else
                {
                    ++bullet;
                }
            }

            // Clipping of bullets outside frustum
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

            // ToDo: Update all movement and perform actions

            playerShip.update();

            for (auto &enemyShip : enemyVector)
            {
                enemyShip->update();
            }

            for(auto &bullet : bulletPlayerVector)
            {
                bullet->update();
                bullet->setMove(-30);
            }

            for(auto &bullet : bulletEnemyVector)
            {
                bullet->update();
                bullet->setMove(30);
            }


            //  Render
            _mainWindow.clear(black);
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
            // Temp enemy draw hack ends here
            ///////////////////////////////////////////////////////

            _mainWindow.draw(playerShip.getSprite());

            _mainWindow.display();

#ifdef DEBUG
            fps.update();
            std::ostringstream ss;
            ss << fps.getFPS();
            _mainWindow.setTitle(ss.str());
#endif // DEBUG

            if (playerShip.getLives() == 0)
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
    _textures.load(textures::SplashControls,"resources/splash_controls.png");
    _textures.load(textures::PlayerShip,"resources/player_ship_animated.png");
    _textures.load(textures::BulletPlayer,"resources/bullet_player.png");
    _textures.load(textures::BulletEnemy,"resources/bullet_enemy.png");
    _textures.load(textures::EnemyShipGrey,"resources/enemyship_grey.png");
    _textures.load(textures::EnemyShipPurple,"resources/enemyship_purple.png");
//    _textures.load(textures::EnemyShipGenerator,"resource/generator.png");
//    _textures.load(textures::Meteoroid,"resource/meteoroid.png");
//    _textures.load(textures::Satellite,"resource/satellite.png");

    _sounds.load(sounds::StartSound,"resources/startup.ogg");
    _sounds.load(sounds::SpawnSound,"resources/ship_spawn.ogg");
    _sounds.load(sounds::PlayerMove,"resources/thrust.ogg");
    _sounds.load(sounds::PlayerShoot,"resources/shoot_laser.ogg");
    _sounds.load(sounds::EnemyShoot,"resources/shoot_phaser.ogg");
    _sounds.load(sounds::PlayerDeath,"resources/player_death.ogg");

    _fonts.load(fonts::Title,"resources/danube.ttf");
    _fonts.load(fonts::Info,"resources/fax_sans_beta.otf");
}
