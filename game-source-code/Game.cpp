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
    sf::Clock enemyTimer;
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
    PlayerShip playerShip(_textures, _sounds, _resolution, shipPathRadius, 0, 0.35);

    // Todo: Enemy creation
    // Temp
    std::vector<Enemy> enemyVector;
    std::vector<Bullet> bulletVector;
    std::vector<Bullet> bulletVectorEnemy;

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
                Bullet bullet(_textures,
                              _sounds,
                              _resolution,
                              playerShip.getDistanceFromCentre(),
                              playerShip.getAngle(),
                              1,
                              textures::BulletPlayer);
                bulletVector.push_back(bullet);
            }

            ///////////////////////////////////////////////////////
            // Temp Enemy generation hack
            auto i = 0;
            const auto OVERSCAN_X = _resolution.x * 0.1;
            const auto OVERSCAN_Y = _resolution.y * 0.1;

            auto test = fmod(enemyTimer.getElapsedTime().asSeconds(),5000000)/5 > 0.01;
            if (!test)
            {
                Enemy enemy(_textures,
                                _sounds,
                                _resolution,
                                0, 0, 1,
                                textures::EnemyShipPurple);
                enemyVector.push_back(enemy);
            } else enemyTimer.restart();

            for (auto &enemyShip : enemyVector)
            {
                if (enemyShip.getRadius() > _resolution.y / 2.f)
                {
                    i++;
                    auto random_angle = rand() % 3 + 2;
                    auto random_move = rand() % 8 + (-2);
                    if (enemyShip.getDistanceFromCentre() < _resolution.y / 8)
                    {
                        enemyShip.setMove(1 + random_angle, 16);
                    } else
                    {
                        enemyShip.setMove(random_angle, random_move);
                    }
                } else
                {
                    enemyShip.reset();
                }

                auto shootInfrequency = 20;
                auto shootChance = 5;
                Bullet bullet_enemy(_textures,
                                    _sounds,
                                    _resolution,
                                    enemyShip.getDistanceFromCentre(),
                                    enemyShip.getAngle(),
                                    1,
                                    textures::BulletEnemy);

                if ((!(rand() % shootInfrequency) % shootChance)
                    && (enemyShip.getDirectionAngle() + enemyShip.getAngle() >= 90))
                {
                    enemyShip.setShoot();
                    bulletVectorEnemy.push_back(bullet_enemy);
                }
            }


            // Temp enemy generation hack ends here
            //////////////////////////////////////////////////////////////


            // ToDo: Check Collisions
            for (auto i = 0; i!=enemyVector.size(); ++i)
            {
                if (collides(playerShip.getSprite(), enemyVector.at(i).getSprite()))
                {
                    enemyVector.erase(enemyVector.begin()+i);
                    i--;
                }
            }
            enemyVector.shrink_to_fit();

            for (auto i = 0; i != bulletVector.size(); ++i)
            {
                for (auto j = 0; j != enemyVector.size(); ++j)
                {
                    if (collides(bulletVector.at(i).getSprite(), enemyVector.at(j).getSprite()))
                    {
//                        bulletVector.erase(bulletVector.begin() + i);
                        enemyVector.erase(enemyVector.begin() + j);
//                        i--;
                        j--;
                    }
                }
            }
            enemyVector.shrink_to_fit();
            bulletVector.shrink_to_fit();


            for (auto i = 0; i!=bulletVectorEnemy.size(); ++i)
            {
                if (collides(playerShip.getSprite(), bulletVectorEnemy.at(i).getSprite()))
                {
                    bulletVectorEnemy.erase(bulletVectorEnemy.begin()+i);
                    i--;
                }
            }
            bulletVectorEnemy.shrink_to_fit();


            // Clipping of bullets outside frustum
            for (auto i = 0; i!=bulletVectorEnemy.size(); ++i)

            {
                if (bulletVectorEnemy.at(i).getRadius() > _resolution.y / 2.f)
                {
                    bulletVectorEnemy.erase(bulletVectorEnemy.begin() + i);
                    i--;
                }
            }
            bulletVectorEnemy.shrink_to_fit();

            for (auto i = 0; i!=bulletVector.size(); ++i)
            {
                if(((bulletVector.at(i).getSprite().getPosition().x > (_resolution.x/2) - 10)
                     && (bulletVector.at(i).getSprite().getPosition().y > (_resolution.y/2) - 10)
                     && (bulletVector.at(i).getSprite().getPosition().x < (_resolution.x/2) + 10)
                     && (bulletVector.at(i).getSprite().getPosition().y < (_resolution.y/2) + 10)))
                {
                    bulletVector.erase(bulletVector.begin() + i);
                    i--;
                }
            }
            bulletVector.shrink_to_fit();


            // ToDo: Update all movement and perform actions

            playerShip.update();

            for (auto &enemyShip : enemyVector)
            {
                enemyShip.update();
            }

            for(auto &bullet : bulletVector)
            {
                bullet.update();
                bullet.setMove(-30);
            }

            for(auto &bullet : bulletVectorEnemy)
            {
                                bullet.update();
                bullet.setMove(30);
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
                _mainWindow.draw(enemyShip.getSprite());
            }

            for(auto &bullet : bulletVector)
            {
                _mainWindow.draw(bullet.getSprite());
            }

            for(auto &bullet : bulletVectorEnemy)
            {
                _mainWindow.draw(bullet.getSprite());
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

    return sqrt((distance_x * distance_x) + (distance_y * distance_y)) <= radius_1 + radius_2;
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
