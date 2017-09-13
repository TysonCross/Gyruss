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


#include <iostream>
#include "Game.hpp"


//Static Member redeclaration
Game::GameState Game::_gameState = Splash;
ResourceMapper Game::_resourceMapper;
InputHandler Game::_inputHandler;
common::Resolution Game::_resolution;
sf::RenderWindow Game::_mainWindow;
std::map<int, bool> Game::_keysPressed;


void Game::Start()
{
    // Todo: Need to choose better way to set the resolution. settings screen and setResource perhaps?
    _resolution.x = std::stoi(_resourceMapper.getResourceValues("Resolution").at(0));
    _resolution.y = std::stoi(_resourceMapper.getResourceValues("Resolution").at(1));

//    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
//    for (std::size_t i = 0; i < modes.size(); ++i)
//    {
//        sf::VideoMode mode = modes[i];
//        std::cout << "Mode #" << i << ": "
//                  << mode.width << "x" << mode.height << " - "
//                  << mode.bitsPerPixel << " bpp" << std::endl;
//    }
//
//    _resolution.x = modes.at(3).width;
//    _resolution.y = modes.at(3).height;

    sf::Image icon;
    icon.loadFromFile(_resourceMapper.getResource("WindowIcon"));

    sf::SoundBuffer buffer;
    buffer.loadFromFile(_resourceMapper.getResource("StartSound"));
    sf::Sound sound(buffer);
    sound.play();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    _mainWindow.create(sf::VideoMode(_resolution.x, _resolution.y, 32), "Gyruss",
                       sf::Style::Close , settings );
    //_mainWindow.setKeyRepeatEnabled(true);
    _mainWindow.setMouseCursorVisible(false);
    _mainWindow.setVerticalSyncEnabled(true);
    _mainWindow.setFramerateLimit(60); // Todo : Limit framerate manually
    _mainWindow.setIcon(32, 32, icon.getPixelsPtr());

    while (_gameState != Game::Exiting)
    {
        InitializeGameLoop();
    }
    _mainWindow.close();
}

void Game::InitializeGameLoop()
{
    sf::Clock clock;
    sf::Time timeSinceUpdate = sf::Time::Zero;

    const sf::Color black(sf::Color::Black);

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
    if (!music.openFromFile(_resourceMapper.getResourceValues("Music").at(0)))
        return; // error
    music.play();

    auto number_of_stars = 80;
    StarField starField(_resolution, 3, number_of_stars);

    const auto shipPathRadius = (_resolution.y / 2) - (_resolution.y * 0.08f);
    PlayerShip playerShip(_resourceMapper, _resolution, shipPathRadius, 0, 0.3);

    sf::Event event;
    enum ButtonState {Up,Down};
    bool previousButtonState = 0;

    ///-------------------------------------------
    ///  Main Game Loop (time advance)
    ///-------------------------------------------
    while (_gameState == Game::Playing)
    {
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
// Need to have a proper polling here to check previous gamestate
            if (event.type == sf::Event::EventType::KeyPressed)
                if (event.key.code == sf::Keyboard::Space)
                    if (previousButtonState == 0)
                    {
                        playerShip.shoot();
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

        ///-------------------------------------------
        ///  Update and events
        ///-------------------------------------------
        _inputHandler.resolveKeyMapping(_keysPressed, playerShip);

        // /ToDo: Update all the relevant objects

        ///-------------------------------------------
        ///  Render
        ///-------------------------------------------
        _mainWindow.clear(black);

        // /ToDo: Draw all the visible objects

        for (const auto &element : starField.getStarField())
        //for (int i = 0; i < number_of_stars; ++i)
        {
            starField.moveAndDrawStars(_mainWindow);
        }

        _mainWindow.draw(playerShip.getSprite());

        // Show the screen buffer
        _mainWindow.display();

        clock.restart();
    }
}

void Game::showSplashScreen()
{
    SplashScreen splashScreen;
    if (splashScreen.show(_mainWindow,_resourceMapper,_resolution) == 0)
    {
        _gameState = Game::Playing;
        return;
    }
    _gameState = Game::Exiting;
}