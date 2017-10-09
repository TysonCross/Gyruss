/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   Main Game controller implementation
///
/// Implements the Game loop, and game states
///
/// Music by Eric Matyas (www.http://soundimage.org)
/// Sounds from Freesounds (www.freesounds.org)
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "Game.hpp"

#ifdef DEBUG_ONLY
#include <sstream>
#include <iostream>
#endif // DEBUG_ONLY

Game::Game()
{
    _resolution = sf::Vector2i{1920, 1080};
    sf::Image icon;
    if (!icon.loadFromFile("resources/icon.png")) return;
    loadResources(); //load all graphics into the resource holder
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    _mainWindow.create(sf::VideoMode(_resolution.x, _resolution.y, 32), "Gyruss", sf::Style::Close, settings);
    _mainWindow.setMouseCursorVisible(false);
    _mainWindow.setVerticalSyncEnabled(true);
    _mainWindow.setIcon(32, 32, icon.getPixelsPtr());
    _windowPosition = _mainWindow.getPosition();

    _winCondition = 100; // Number of enemies needed to kill to win.
    _gameState = game::GameState::Splash;
    _shaking = 0;
}

void Game::Start()
{
    while (_gameState != game::GameState::Exiting)
    {
        startGameLoop();
    }
    Quit();
}

void Game::startGameLoop()
{
    Clock mainClock;
    Clock totalTimer;
    Clock speedTimer;
    Clock aliveTimer;
    Time timeSinceUpdate = sf::Time::Zero;
    float timeStep = 1.f / 60.f; //60 frames per second
    auto speedModifier = 0.5f; //defines how fast the game should be at the start
    auto increaseSpeedThreshold = 1.5f;  // How often the game speeds up (in seconds)
    auto globalSpeedIncrease = 0.02f; // Game speeds up this amount every time
    _inputHandler.reset(); //clear all previous inputs in the inputHandler

    _mainWindow.clear(sf::Color::Black);

    //First Game State
    if (_gameState == game::GameState::Splash)
        showSplashScreen();

    if (_gameState == game::GameState::GameOverLose)
        showGameOverScreen(false);

    if (_gameState == game::GameState::GameOverWin)
        showGameOverScreen(true);

    #ifdef DEBUG_ONLY
    // Debug mode: displays frames-per-second in title bar
    FPS fps;
    #endif // DEBUG_ONLY

    ///-------------------------------------------
    ///  Game Playing starts
    ///-------------------------------------------
    _score.reset();

    // Load game music
    if(_soundController.loadMusic())
        _soundController.playMusic();

    // Generate starField
    auto numberOfStars = 60;
    StarField starField(_resolution, 3, numberOfStars);

    // Generate playerShip object
    auto shipPathRadiusPadding = 0.05f;
    const auto shipPathRadius = (_resolution.y / 2) - (_resolution.y * shipPathRadiusPadding);
    const auto shipScale = 0.22;
    PlayerShip playerShip(_resolution,
                          shipPathRadius,
                          0,
                          shipScale,
                          entity::PlayerShip,
                          _textures);

    // Generate entityController object to manage all game objects movement, creation and destruction
    EntityController entityController(_resolution,
                                      playerShip,
                                      _textures,
                                      _score,
                                      speedModifier);

    // Generate shield object for playerShip
    Shield shield(_resolution,
                  shipPathRadius,
                  0,
                  shipScale,
                  _textures,
                  playerShip);

    // Create a hud object to show current lives and game stats
    HUD hud(_resolution,
            _mainWindow,
            _fonts,
            _score,
            playerShip);

    // Initialise the playerShip move sound
    _soundController.playSound(sounds::PlayerMove,0,100,1);

    ///-------------------------------------------
    ///  Main Game Loop (time advance)
    ///-------------------------------------------
    while (_gameState == game::GameState::Playing)
    {
        ///-------------------------------------------
        /// Events
        ///-------------------------------------------
        // Deal with user input
        Event event;
        while (_mainWindow.pollEvent(event))
        {
            _inputHandler.pollInput(_gameState, playerShip, event);

            #ifdef DEBUG_ONLY
            // Debug function (developer cheat keys to tweak and test game-play)
            debugKeys(event, playerShip, entityController);
            #endif // DEBUG_ONLY
        }

        // Frame timing events
        timeSinceUpdate += mainClock.getElapsedTime();
        mainClock.restart();

        // Game gets faster the longer you stay alive
        if(speedTimer.getElapsedTime().asSeconds() > increaseSpeedThreshold)
        {
            speedTimer.restart();
            entityController.changeGlobalSpeed(globalSpeedIncrease);
        }

        ///-------------------------------------------
        ///  Fixed Timestep
        ///-------------------------------------------
        while (timeSinceUpdate.asSeconds() >= timeStep)
        {
            timeSinceUpdate = sf::Time::Zero;

            entityController.spawnEntities();
            _inputHandler.setPlayerShipMove(playerShip, timeStep);
            entityController.setMove();
            entityController.shoot();
            entityController.checkClipping();

            ///-------------------------------------------
            ///  Player Death
            ///-------------------------------------------

            // Returns true if the player has collided. (also does global entity collision check)
            if (entityController.checkCollisions())
            {
                if (!playerShip.isInvulnerable())
                {
                    playerDeathEvents(playerShip, entityController);
                }
            }

            ///-------------------------------------------
            /// Pre update() Sound events
            ///-------------------------------------------

            playEventSounds(playerShip, entityController);

            ///-------------------------------------------
            /// Update() all entities
            ///-------------------------------------------
            update(playerShip, entityController);

            ///-------------------------------------------
            ///  Render
            ///-------------------------------------------
            render(starField, playerShip, entityController, shield, hud);

            #ifdef DEBUG_ONLY
            fps.update();
            std::ostringstream ss;
            ss << fps.getFPS();
            _mainWindow.setTitle(ss.str());
            #endif // DEBUG_ONLY

            ///-------------------------------------------
            ///  End game state
            ///-------------------------------------------
            endGameCheck(playerShip);

        }
    }
}

void Game::update(PlayerShip &playerShip, EntityController &entityController)
{
    _score.update();
    playerShip.update();
    entityController.update();
}

void Game::shakeWindow()
{
    Event event;
    while (_mainWindow.pollEvent(event))
    {
        if (event.type == Event::Closed) _mainWindow.close();
    }

    if (_shaking > 0)
    {
        auto pos_temp = _windowPosition;
        auto shake_amount = 25;
        _mainWindow.setPosition(Vector2i(pos_temp.x + rand() % shake_amount,
                                         pos_temp.y + rand() % shake_amount));

        if (++_shaking >= 5)
            _shaking = 0;
    }
    _mainWindow.display(); // Display window for each shaking frame
}

void Game::render(StarField &starField,
                  const PlayerShip &playerShip,
                  EntityController &entityController,
                  Shield &shield,
                  HUD &hud)
{
    _windowPosition = _mainWindow.getPosition();
    _mainWindow.clear(Color::Black);

    for (const auto &element : starField.getStarField())
        starField.moveAndDrawStars(_mainWindow, entityController.getSpeed() * 0.001f);

    for (auto &enemy : entityController.getEnemies())
        _mainWindow.draw(enemy->getSprite());

    for (auto &bullet : entityController.getBulletsEnemy())
        _mainWindow.draw(bullet->getSprite());

    for (auto &bullet : entityController.getBulletsPlayer())
        _mainWindow.draw(bullet->getSprite());

    for (auto &meteoroid : entityController.getMeteoroids())
        _mainWindow.draw(meteoroid->getSprite());

    for (auto &explosion : entityController.getExplosions())
        _mainWindow.draw(explosion->getSprite());

    _mainWindow.draw(playerShip.getSprite());

    if (playerShip.isInvulnerable())
            {
                shield.update();
                _mainWindow.draw(shield.getSprite());
            }
            else shield.reset();

    hud.draw();

    // Shake the screen in the event the the playerShip dies.
    while (_shaking > 0) shakeWindow();
    _mainWindow.setPosition(_windowPosition);

    _mainWindow.display(); // Main Render call
}

void Game::playEventSounds( PlayerShip &playerShip, EntityController &entityController)
{// Player move sound
    _soundController.setPosition(sounds::PlayerMove, {playerShip.getPosition().x, playerShip.getPosition().y, -5});
    _soundController.setPitch(sounds::PlayerMove, fabs(playerShip.getFutureAngle() / 4));  // Engine pitch rises to be audible when moving

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
}

void Game::showSplashScreen()
{
    _soundController.stopMusic();
    _soundController.stopSound(sounds::PlayerMove);
    _soundController.playSound(sounds::StartSound);

    ScreenSplash splashScreen;

    if (splashScreen.draw(_mainWindow, _textures, _fonts, _resolution) == 0)
    {
        _gameState = game::GameState::Playing;
        return;
    }
    _gameState = game::GameState::Exiting;
}

void Game::showGameOverScreen(bool gameOutcome)
{
    _soundController.stopSound(sounds::PlayerMove);
    if (gameOutcome)
        _soundController.playSound(sounds::GameOverWinSound);
    else
        _soundController.playSound(sounds::GameOverLoseSound);
    _soundController.stopMusic();
    recordHighScore(); //calls to save score to disk
    ScreenGameOver gameOverScreen(gameOutcome);
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
    _textures.load(textures::GameOverLoseScreen, "resources/gameoverlose.png");
    _textures.load(textures::GameOverWinScreen, "resources/gameoverwin.png");
    _textures.load(textures::SplashControls, "resources/splash_controls.png");
    _textures.load(textures::GameOverCredits, "resources/gameover_credits.png");
    _textures.load(textures::PlayerShip, "resources/player_ship_animated.png");
    _textures.load(textures::BulletPlayer, "resources/bullet_player.png");
    _textures.load(textures::BulletEnemy, "resources/bullet_enemy.png");
    _textures.load(textures::Meteoroid, "resources/meteoroid.png");
    _textures.load(textures::Planet, "resources/earth.png");
    _textures.load(textures::EnemyShipGrey, "resources/enemyship_grey.png");
    _textures.load(textures::EnemyShipPurple, "resources/enemyship_purple.png");
    _textures.load(textures::EnemyShipYellow, "resources/enemyship_yellow.png");
    _textures.load(textures::Satellite, "resources/satellite.png");
    _textures.load(textures::Explosion, "resources/explosion.png");
    _textures.load(textures::Shield, "resources/shield.png");

    // Load Fonts
    _fonts.load(fonts::Title, "resources/danube.ttf");
    _fonts.load(fonts::Default, "resources/fax_sans_beta.otf");
}

void Game::recordHighScore()
{
    string filename = "highscores.txt";
    ifstream inputFile(filename, std::ios::in);


    if (!inputFile.is_open())
    {
        throw runtime_error("Game::recordHighScore - Unable to open input file: " + filename);
    }
    inputFile.seekg(0, std::ios::beg);


    string oldHighScore = "";
    inputFile >> oldHighScore;

    string::size_type sizeString;   // alias of size_t
    int oldValue = std::stoi(oldHighScore, &sizeString);

    if (_score.getScore() > oldValue)
    {
        std::ofstream outputFile(filename, std::ios::out);
        if (!outputFile.is_open())
        {
            throw runtime_error("Game::recordHighScore - Unable to open output file: " + filename);
        }
        outputFile << _score.getScore();
        outputFile.close();
    }
    inputFile.close();
    return;
}

void Game::playerDeathEvents(PlayerShip &playerShip, EntityController &entityController)
{
    playerShip.die();
    _score.resetLifeTimer();
    _soundController.playSound(sounds::PlayerDeath);
    _soundController.playSound(sounds::Explosion);
    _inputHandler.reset();
    entityController.resetGlobalSpeed();
    entityController.killAllEnemiesOfType(entity::Satellite);
    _shaking = 1;
}

void Game::endGameCheck(const PlayerShip &playerShip)
{
    if (playerShip.getLives() <= 0)
    {
        //_score.resetLifeTimer();
        _gameState = game::GameOverLose;
    }

    if(_score.getEnemiesKilled() >= _winCondition)
    {
        _score.resetLifeTimer();
        _gameState = game::GameOverWin;
    }
}

void Game::Quit()
{
    _mainWindow.close();
}

void Game::debugKeys(const Event &event, PlayerShip &playerShip, EntityController &entityController)
{
    // Debug keys for game-play tuning and developer usage
    auto speedChange = 0.1f;
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::RBracket)
            entityController.changeGlobalSpeed(speedChange);
        if (event.key.code == Keyboard::LBracket)
            entityController.changeGlobalSpeed(-speedChange);
        if (event.key.code == Keyboard::P)
            playerShip.makeInvulnerable(true);
        if (event.key.code == Keyboard::O)
            playerShip.makeInvulnerable(false);
        if (event.key.code == Keyboard::K)
            playerDeathEvents(playerShip, entityController);
        if (event.key.code == Keyboard::L)
            playerShip.upgrade();
        if (event.key.code == Keyboard::I)
        {
            auto enemyType = static_cast<entity::ID >(rand() % 2);
            auto textureVariant = static_cast<textures::ID>(rand() % 2);
            auto movementDir = static_cast<MovementDirection >(rand() % 2);
            auto movementState = static_cast<MovementState>(rand() % 5);
            entityController.spawnBasicEnemy(enemyType,
                                             textureVariant,
                                             movementDir,
                                             movementState);
        }
    }
}