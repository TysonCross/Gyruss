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

//    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
//    for (std::size_t i = 0; i < modes.size(); ++i)
//    {
//        sf::VideoMode mode = modes[i];
//        std::cout << "Mode #" << i << ": "
//                  << mode.width << "x" << mode.height << " - "
//                  << mode.bitsPerPixel << " bpp" << std::endl;
//    }
//
//    _resolution.x = modes.at(1).width;
//    _resolution.y = modes.at(1).height;

    sf::Image icon;
    if (!icon.loadFromFile("resources/icon.png"))
    {
        return ;
    }

    loadResources();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    _mainWindow.create(sf::VideoMode(_resolution.x, _resolution.y, 32), "Gyruss",
                       sf::Style::Close , settings );
    _mainWindow.setMouseCursorVisible(false);
    _mainWindow.setVerticalSyncEnabled(true);
    _mainWindow.setIcon(32, 32, icon.getPixelsPtr());

    while (_gameState != Game::Exiting)
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
    FPS fps;

    const sf::Color black(sf::Color::Black);

    sf::Sound sound(_sounds.get(sounds::StartSound));
    sound.play();

    //First Game State
    if (_gameState == Game::Splash)
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
    Enemy enemyShip(_textures, _sounds, _resolution, 0, 0, 1, textures::EnemyShipPurple);
    // Temp
    std::vector<Bullet> bulletVector;
    std::vector<Bullet> bulletVectorEnemy;


    ///-------------------------------------------
    ///  Main Game Loop (time advance)
    ///-------------------------------------------


    while (_gameState == Game::Playing)
    {
        pollInput(playerShip,bulletVector); //temporary arguments

        ///-------------------------------------------
        /// Events
        ///-------------------------------------------
        timeSinceUpdate += clock.getElapsedTime();
        clock.restart();
        _inputHandler.resolveKeyMapping(_keysPressed);


        ///-------------------------------------------
        ///  Fixed Timestep
        ///-------------------------------------------
        while (timeSinceUpdate.asSeconds() >= timeStep)
        {
            timeSinceUpdate = sf::Time::Zero;
            // /ToDo: Update all the relevant objects
            _inputHandler.update(playerShip,timeStep);

            //  Render
            _mainWindow.clear(black);
            // /ToDo: Draw all the visible objects
            for (const auto &element : starField.getStarField())
            {
                starField.moveAndDrawStars(_mainWindow);
            }

            ///////////////////////////////////////////////////////
            // Temp Enemy generation
            auto i = 0;
            const auto OVERSCAN_X = _resolution.x * 0.1;
            const auto OVERSCAN_Y = _resolution.y * 0.1;
            if((enemyShip.getSprite().getPosition().x < _resolution.x+OVERSCAN_X)
               && (enemyShip.getSprite().getPosition().y < _resolution.y+OVERSCAN_Y)
               && (enemyShip.getSprite().getPosition().x > 0-OVERSCAN_X)
               && (enemyShip.getSprite().getPosition().y > 0-OVERSCAN_Y))
            {
                i++;
                auto random_angle = rand() % 2 + 1;
                auto random_move = rand() % 20 + (-2);
                enemyShip.move(2,20);
                
            }
            else
            {
                enemyShip.reset();
            }


            Bullet bullet2(_textures,_resolution,
                           enemyShip.getDistanceFromCentre(),
                           enemyShip.getAngle(), 1, textures::BulletEnemy);
            if ((!(rand()%50)%5)&&(enemyShip.getDirectionAngle()+enemyShip.getAngle() > 180))
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

            // Temp enemy generation ends here
            ///////////////////////////////////////////////////////

            _mainWindow.draw(playerShip.getSprite());
            _mainWindow.display();

            fps.update();
            std::ostringstream ss;
            ss << fps.getFPS();
            _mainWindow.setTitle(ss.str());

        }
    }
}

void Game::showSplashScreen()
{
    SplashScreen splashScreen;
    if (splashScreen.show(_mainWindow,_textures,_sounds, _fonts, _resolution) == 0)
    {
        _gameState = Game::Playing;
        return;
    }
    _gameState = Game::Exiting;
}

void Game::loadResources()
{
    //Load Textures and Sounds
    _textures.load(textures::SplashScreen,"resources/splash.png");
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

void Game::pollInput(PlayerShip& playerShip,std::vector<Bullet>& bulletVector)
{
    // ToDo: Move into inputHandler
    enum ButtonState {Up,Down};
    bool previousButtonState = 0;
    sf::Event event;

    //Check for events since last frame
    while (_mainWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _gameState = Game::Exiting;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
            && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
        {
            _gameState = Game::Exiting;
        }
        if (event.type == sf::Event::EventType::KeyPressed)
            if (event.key.code == sf::Keyboard::Space)
                if (previousButtonState == 0)
                {
                    playerShip.shoot();
                    Bullet bullet(_textures,_resolution,
                                  playerShip.getDistanceFromCentre(),
                                  playerShip.getAngle(), 1 , textures::BulletPlayer);
                    bulletVector.push_back(bullet);
                    // ToDo : Make bullet creation an event
                    previousButtonState = 1;
                }
        if (event.type == sf::Event::EventType::KeyReleased)
            if (event.key.code == sf::Keyboard::Space)
            {
                previousButtonState = 0;
            }

        // During the current polling period, key-presses are detected
        // if pressed added to the map, and removed if the key is released
        if (event.type == sf::Event::EventType::KeyPressed)
        {
            if (_keysPressed.count(event.key.code) == 0)
            {
                _keysPressed[event.key.code] = true;
            }
        }

        if (event.type == sf::Event::EventType::KeyReleased)
        {
            if (_keysPressed.count(event.key.code) > 0)
            {
                _keysPressed.erase(event.key.code);
            }
        }
    } // End of input polling
}
