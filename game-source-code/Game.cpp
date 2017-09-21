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

//    //Set the player circle radius
//    // Todo: Config.ini file
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (_resolution.y / 2) - (_resolution.y * shipPathRadiusPadding);
    const auto shipScale = 0.28;
    EntityController entityController(_resolution,
                                      shipPathRadius,
                                      shipScale,
                                      _textures,
                                      _sounds);

    ///-------------------------------------------
    ///  Main Game Loop (time advance)
    ///-------------------------------------------

    while (_gameState == game::GameState::Playing)
    {
        sf::Event event;
        while (_mainWindow.pollEvent(event))
        {
            _inputHandler.pollInput(_gameState,
                                    entityController, // Could be entityHandler?
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

            _inputHandler.update(entityController, timeStep);

            entityController.spawnEnemies();
            entityController.setMove();
            entityController.shoot();
            entityController.checkClipping();
           if(entityController.checkCollisions())
           {
               _inputHandler.reset();
               shaking = 1;
           }
            entityController.update();

#ifdef DEBUG
        entityController.debug();
#endif // DEBUG

            ///-------------------------------------------
            ///  Render
            ///-------------------------------------------
            _mainWindow.clear(sf::Color::Black);

            for (const auto &element : starField.getStarField())
                starField.moveAndDrawStars(_mainWindow);

            entityController.draw(_mainWindow);

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

            if (entityController.getPlayerLives() <= 0)
            {
                _gameState = game::GameState::GameOver;
            }
        }
    }
}

void Game::showSplashScreen()
{
    ScreenSplash splashScreen;
    if (splashScreen.show(_mainWindow,_textures,_sounds, _fonts, _resolution) == 0)
    {
        _gameState = game::GameState::Playing;
        return;
    }
    _gameState = game::GameState::Exiting;
}

void Game::showGameOverScreen()
{
    ScreenGameOver gameOverScreen;
    if (gameOverScreen.show(_mainWindow,_textures,_sounds, _fonts, _resolution) == 0)
    {
        _gameState = game::GameState::Splash;
        return;
    }
    _gameState = game::GameState::Exiting;
}

//bool Game::collides(const sf::Sprite &sprite1, const sf::Sprite &sprite2)
//{
//    auto shrink_factor = 4.f + 0.2f;
//    float radius_1 = (sprite1.getGlobalBounds().width + sprite1.getGlobalBounds().height) / shrink_factor;
//    float radius_2 = (sprite2.getGlobalBounds().width + sprite2.getGlobalBounds().height) / shrink_factor;
//    float distance_x = sprite1.getPosition().x - sprite2.getPosition().x;
//    float distance_y = sprite1.getPosition().y - sprite2.getPosition().y;
//
//    return  radius_1 + radius_2 >= sqrt((distance_x * distance_x) + (distance_y * distance_y));
//}

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
    _sounds.load(sounds::Explosion,"resources/explosion.ogg");
    _fonts.load(fonts::Title,"resources/danube.ttf");
    _fonts.load(fonts::Info,"resources/fax_sans_beta.otf");
}
