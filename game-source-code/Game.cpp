/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    Game.cpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/09
/// \brief   Main Game controller implementation
///
/// Implements the Game loop, and game states
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Game.hpp"


//Static Member redeclaration
Game::GameState Game::_gameState = Splash;
ResourceMapper Game::_resourceMapper;
common::Resolution Game::_resolution;
sf::RenderWindow Game::_mainWindow;
std::map<int, bool> Game::_keysPressed;


void Game::Start()
{
    _resolution.x = std::stoi(_resourceMapper.getResourceValues("Resolution").at(0));
    _resolution.y = std::stoi(_resourceMapper.getResourceValues("Resolution").at(1));

    sf::Image icon;
    icon.loadFromFile(_resourceMapper.getResource("WindowIcon"));


    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile(_resourceMapper.getResource("StartSound"));
    sound.setBuffer(buffer);
    sound.play();


    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    _mainWindow.create(sf::VideoMode(_resolution.x, _resolution.y, 32), "Gyruss",
                       sf::Style::Close, settings );
    //_mainWindow.setKeyRepeatEnabled(true);
    _mainWindow.setMouseCursorVisible(false);
    _mainWindow.setVerticalSyncEnabled(true);
    _mainWindow.setFramerateLimit(60);
    _mainWindow.setIcon(32, 32, icon.getPixelsPtr());

    while (_gameState != Game::Exiting)
    {
        InitializeGameLoop();
    }
    _mainWindow.close();
}

void Game::InitializeGameLoop()
{
    //-------------------------------------------
    //  Setup
    //-------------------------------------------
    sf::Event event;
    sf::Clock clock;
    sf::Color color(sf::Color::Black);

    //-------------------------------------------
    //  Display Splashscreen
    //-------------------------------------------
    //First Game State
    if (_gameState == Game::Splash)
    {
        showSplashScreen();
    }

    //-------------------------------------------
    //  Game Playing starts
    //-------------------------------------------
    //Spawn starField bg
    auto number_of_stars = 20;
    sf::RectangleShape star_shape({});
    StarField starField( star_shape, _resolution.x, _resolution.y, 6, number_of_stars);

    //Spawn Player ship
    const auto shipPathRadius = (_resolution.y / 2) - (_resolution.y * 0.08f);
    PlayerShip playerShip(_resourceMapper, shipPathRadius, 0, 0.4);

    //input Handler
    InputHandler inputHandler;

    //-------------------------------------------
    //  Main Game Loop (time advance)
    //-------------------------------------------
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

            if (event.type == sf::Event::EventType::KeyReleased)
                if (event.key.code == sf::Keyboard::Space)
                {
                    playerShip.shoot();
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

        //-------------------------------------------
        //  Update and events
        //-------------------------------------------
        inputHandler.resolveKeyMapping(_keysPressed, playerShip);


        //ToDo: Update all the relevant objects

        //-------------------------------------------
        //  Presentation
        //-------------------------------------------
        _mainWindow.clear(color);

        //ToDo: Draw all the visible objects

//        for (auto &element : starField.getStarField())
        for (int i = 0; i < number_of_stars; ++i)
        {
            starField.moveStars(star_shape,_mainWindow);
            //_mainWindow.draw(star_shape);
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
    if (splashScreen.show(_mainWindow,_resourceMapper) == 0)
    {
        _gameState = Game::Playing;
        return;
    }
    _gameState = Game::Exiting;
}