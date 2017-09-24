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

#ifdef DEBUG_ONLY
#include <sstream>
#include <iostream>
#endif // DEBUG_ONLY

Game::Game()
{
    _makePlayerInvulnerable = false;
}

void Game::Start()
{
    // Todo: Need to choose better way to set the resolution. settings screen and set Resource perhaps?
    _resolution = sf::Vector2i{1920, 1080};

    sf::Image icon;
    if (!icon.loadFromFile("resources/icon.png")) return;

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
    sf::Clock speed;
    sf::Time timeSinceUpdate = sf::Time::Zero;
    float timeStep = 1.f / 60.f;
    auto speedModifier = 0.5f;
    auto increaseSpeedThreshold = 1;
    _inputHandler.reset();

#ifdef DEBUG_ONLY
    FPS fps;
#endif // DEBUG_ONLY

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
    _score.reset();
    _music.setLoop(true);
    _music.setVolume(25);
    if (!_music.openFromFile("resources/game_music.ogg"))
    {
        _gameState = game::GameState::Exiting;
        return;// error
    } else
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
                          entity::PlayerShip,
                          _textures);

    EntityController entityController(_resolution,
                                      playerShip,
                                      _textures,
                                      _score,
                                      speedModifier);

    HUD hud(_resolution, _mainWindow, _textures, _fonts, _score, playerShip);

//    _timeAliveClock.restart();
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
#ifdef DEBUG_ONLY
            auto speedChange = 0.1f;
            if (event.type == sf::Event::EventType::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::RBracket)
                    entityController.changeGlobalSpeed(speedChange);

                if (event.key.code == sf::Keyboard::LBracket)
                    entityController.changeGlobalSpeed(-speedChange);

                if (event.key.code == sf::Keyboard::P)
                    _makePlayerInvulnerable = true;

                if (event.key.code == sf::Keyboard::O)
                    _makePlayerInvulnerable = false;

                if (event.key.code == sf::Keyboard::K)
                        playerShip.die();
            }
#endif // DEBUG_ONLY
        }

        timeSinceUpdate += clock.getElapsedTime();
        clock.restart();
        // Enemy movment get faster the longer the player lives
        if(speed.getElapsedTime().asSeconds() > increaseSpeedThreshold)
        {
            speed.restart();
            entityController.changeGlobalSpeed(0.001);
        }
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
                if (!_makePlayerInvulnerable)
                {
                    playerShip.die();
                    _soundController.playSound(sounds::PlayerDeath);
                    _soundController.playSound(sounds::Explosion);
                    _inputHandler.reset();
                    shaking = 1;
                }
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

            ///-------------------------------------------
            ///  Render
            ///-------------------------------------------
            _mainWindow.clear(sf::Color::Black);

            for (const auto &element : starField.getStarField())
                starField.moveAndDrawStars(_mainWindow, entityController.getSpeed() * 0.001f);

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

            _mainWindow.setPosition(pos);
            hud.draw();
            _mainWindow.display();

#ifdef DEBUG_ONLY
            fps.update();
            std::ostringstream ss;
            ss << fps.getFPS();
            _mainWindow.setTitle(ss.str());
#endif // DEBUG_ONLY

            // End Game
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
    if (splashScreen.draw(_mainWindow, _textures, _fonts, _resolution) == 0)
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
    recordHighScore();
    ScreenGameOver gameOverScreen;
    if (gameOverScreen.draw(_mainWindow, _textures, _fonts, _resolution, _score) == 0)
    {
        _gameState = game::GameState::Splash;
        return;
    }
    _gameState = game::GameState::Exiting;
}

void Game::loadResources()
{
    // Load Textures
    _textures.load(textures::SplashScreen, "resources/splash.png");
    _textures.load(textures::SplashScreenExtra, "resources/splash_spacefight.png");
    _textures.load(textures::GameOverScreen, "resources/gameover.png");
    _textures.load(textures::SplashControls, "resources/splash_controls.png");
    _textures.load(textures::GameOverCredits, "resources/gameover_credits.png");
    _textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    _textures.load(textures::BulletPlayer, "resources/bullet_player.png");
    _textures.load(textures::BulletEnemy, "resources/bullet_enemy.png");
    _textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");
    _textures.load(textures::EnemyShipPurple, "resources/enemyship_purple.png");
    _textures.load(textures::Explosion, "resources/explosion.png");

    // Load Fonts
    _fonts.load(fonts::Title, "resources/danube.ttf");
    _fonts.load(fonts::Default, "resources/fax_sans_beta.otf");
}

void Game::recordHighScore()
{

    std::string filename = "highscores.txt";
    std::ifstream inputFile(filename,
                            std::ios::in);


    if (!inputFile.is_open())
    {
        throw std::runtime_error("Game::recordHighScore - Unable to open input file: " + filename);
    }
    inputFile.seekg(0, std::ios::beg);


    std::string oldHighScore = "";
    inputFile >> oldHighScore;

    std::string::size_type sizeString;   // alias of size_t
    int oldValue = std::stoi(oldHighScore, &sizeString);

    if (_score.getScore() > oldValue)
    {
        std::ofstream outputFile(filename, std::ios::out);
        if (!outputFile.is_open())
        {
            throw std::runtime_error("Game::recordHighScore - Unable to open output file: " + filename);
        }
        outputFile << _score.getScore();
        outputFile.close();
    }

    inputFile.close();
    return;
}