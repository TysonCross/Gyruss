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
#include <iostream>

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
    sf::Clock total;
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
    _music.setLoop(true);
    _music.setVolume(25);
    if (!_music.openFromFile("resources/game_music.ogg"))
    {
        _gameState = game::GameState::Exiting;
        return;// error
    }
    else
        _music.play();

    auto number_of_stars = 60;
    StarField starField(_resolution, 3, number_of_stars);

    // Todo: Config.ini file
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (_resolution.y / 2) - (_resolution.y * shipPathRadiusPadding);
    const auto shipScale = 0.28;
    PlayerShip playerShip(_resolution,
                                shipPathRadius,
                                0,
                                shipScale,
                                _textures);

    EntityController entityController(_resolution,
                                      playerShip,
                                      _textures);

    ///-------------------------------------------
    ///  Main Game Loop (time advance)
    ///-------------------------------------------

    while (_gameState == game::GameState::Playing)
    {

        ///-------------------------------------------
        /// Events
        ///-------------------------------------------
        sf::Event event;
        while (_mainWindow.pollEvent(event))
        {
            _inputHandler.pollInput(_gameState,
                                    playerShip,
                                    event);
        }

        timeSinceUpdate += clock.getElapsedTime();
        clock.restart();

        ///-------------------------------------------
        ///  Fixed Timestep
        ///-------------------------------------------
        while (timeSinceUpdate.asSeconds() >= timeStep)
        {
            timeSinceUpdate = sf::Time::Zero;

            _inputHandler.update(playerShip, timeStep);
            entityController.spawnEnemies();
            entityController.shoot();
            entityController.setMove();
            entityController.checkClipping();
            if (entityController.checkCollisions())
            {
                playerShip.die();
                _soundController.playSound(sounds::PlayerDeath);
                _soundController.playSound(sounds::Explosion);
                _inputHandler.reset();
                shaking = 1;
            }
            ///-------------------------------------------
            /// Pre update() Sound events
            ///-------------------------------------------
            if (playerShip.isShooting())
                _soundController.playSound(sounds::PlayerShoot);

            if (entityController.explosionOccurred())
            {
                // Vary the pitch of the explosions
                auto pitch = (rand() % 3 + 0.8) / 3.f;
                _soundController.playSound(sounds::Explosion, pitch, 50);
            }

            if (entityController.shootingOccurred())
            {
                // Vary the pitch of the explosions
                auto pitch = (rand() % 3 + 0.8) / 3.f;
                _soundController.playSound(sounds::EnemyShoot, pitch, 90);
            }

            ///-------------------------------------------
            /// Update() all entities
            ///-------------------------------------------
            playerShip.update();
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

            if (playerShip.isInvulnerable())
                pulseColor(playerShip.getSprite(),sf::Color::Red,20,total);

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
    _soundController.playSound(sounds::StartSound);
    ScreenSplash splashScreen;
    if (splashScreen.show(_mainWindow,_textures, _fonts, _resolution) == 0)
    {
        _gameState = game::GameState::Playing;
        return;
    }
    _gameState = game::GameState::Exiting;
}

void Game::showGameOverScreen()
{
    _soundController.playSound(sounds::GameOverSound);
    _music.stop();
    ScreenGameOver gameOverScreen;
    if (gameOverScreen.show(_mainWindow,_textures, _fonts, _resolution) == 0)
    {
        _gameState = game::GameState::Splash;
        return;
    }
    _gameState = game::GameState::Exiting;
}

void Game::loadResources()
{
    // Load Textures
    _textures.load(textures::SplashScreen,"resources/splash.png");
    _textures.load(textures::SplashScreenExtra,"resources/splash_spacefight.png");
    _textures.load(textures::GameOverScreen,"resources/gameover.png");
    _textures.load(textures::SplashControls,"resources/splash_controls.png");
    _textures.load(textures::GameOverCredits,"resources/gameover_credits.png");
    _textures.load(textures::PlayerShip,"resources/player_ship_animated.png");
    _textures.load(textures::BulletPlayer,"resources/bullet_player.png");
    _textures.load(textures::BulletEnemy,"resources/bullet_enemy.png");
    _textures.load(textures::EnemyShipGrey,"resources/enemyship_grey.png");
    _textures.load(textures::EnemyShipPurple,"resources/enemyship_purple.png");
    _textures.load(textures::Explosion,"resources/explosion.png");

    // Load Fonts
    _fonts.load(fonts::Title,"resources/danube.ttf");
    _fonts.load(fonts::Info,"resources/fax_sans_beta.otf");
}

void Game::pulseColor(sf::Sprite sprite, sf::Color color, int frequency, sf::Clock& clock)
{
    float change = clock.getElapsedTime().asSeconds();
    change = common::radToDegree(common::angleFilter(change));
    auto i = fabs(sin(change*1/frequency));
    sprite.setColor(sf::Color(i*color.r,i*color.g,i*color.b));
}