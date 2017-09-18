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
    {
        showSplashScreen();
    }

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
    const auto shipPathRadius = (_resolution.y / 2) - (_resolution.y * 0.05f);
    PlayerShip playerShip(_textures, _sounds, _resolution, shipPathRadius, 0, 0.35);

    // Todo: Enemy creation
    // Temp
    Enemy enemyShip(_textures, _sounds, _resolution, 0, 0, 1, textures::EnemyShipPurple);
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
            _inputHandler.update(playerShip,timeStep);
            // ToDo : Make bullet creation an event
            if (playerShip.isShooting())
            {
                Bullet bullet(_textures,_sounds, _resolution,
                              playerShip.getDistanceFromCentre(),
                              playerShip.getAngle(), 1 , textures::BulletPlayer);
                bulletVector.push_back(bullet);
            }

            // ToDo: Check Collisions

            // ToDo: Update all movement and perform actions
            playerShip.update();


            //  Render
            _mainWindow.clear(black);
            // /ToDo: Draw all the visible objects
            for (const auto &element : starField.getStarField())
            {
                starField.moveAndDrawStars(_mainWindow);
            }

            ///////////////////////////////////////////////////////
            // Temp Enemy generation hack
            auto i = 0;
            const auto OVERSCAN_X = _resolution.x * 0.1;
            const auto OVERSCAN_Y = _resolution.y * 0.1;
            if((enemyShip.getSprite().getPosition().x < _resolution.x+OVERSCAN_X)
               && (enemyShip.getSprite().getPosition().y < _resolution.y+OVERSCAN_Y)
               && (enemyShip.getSprite().getPosition().x > 0-OVERSCAN_X)
               && (enemyShip.getSprite().getPosition().y > 0-OVERSCAN_Y))
            {
                i++;
                auto random_angle = rand() % 3 + 2;
                auto random_move = rand() % 8 + (-2);
                if(enemyShip.getDistanceFromCentre() < _resolution.y/8)
                {
                    enemyShip.move(1+random_angle, 16);
                }
                else
                {
                    enemyShip.move(random_angle, random_move);
                }
            }
            else
            {
                enemyShip.reset();
            }


            auto shootInfrequency = 20;
            auto shootChance = 5;
            Bullet bullet2(_textures, _sounds, _resolution,
                           enemyShip.getDistanceFromCentre(),
                           enemyShip.getAngle(), 1, textures::BulletEnemy);
            if ((!(rand()%shootInfrequency)%shootChance)
                &&(enemyShip.getDirectionAngle() + enemyShip.getAngle() >= 90))
            {
                enemyShip.shoot();
                bulletVectorEnemy.push_back(bullet2);
            }

            _mainWindow.draw(enemyShip.getSprite());

            for(auto &bullet : bulletVector)
            {
                bullet.move(-30);
                _mainWindow.draw(bullet.getSprite());
            }
            for(auto &bullet : bulletVectorEnemy)
            {
                bullet.move(30);
                _mainWindow.draw(bullet.getSprite());
            }

            // Temp enemy generation hack ends here
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

void Game::loadResources()
{
    //Load Textures and Sounds
    _textures.load(textures::SplashScreen,"resources/splash.png");
    _textures.load(textures::SplashControls,"resources/splash_controls.png");
    _textures.load(textures::PlayerShip,"resources/player_ship.png");
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
