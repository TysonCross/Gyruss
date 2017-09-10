//--------------------------------------------------------------------------
// Student  1239448
// @file    Game.cpp
// @author  Tyson Cross and Chris Maree
// @date    2017/09/09
// @brief   Main Game controller implementation
//
// Implements the Game loop, and game states
//
// Copyright (c) 2017 Tyson Cross and Chris Maree, Wits University, All rights reserved.
//--------------------------------------------------------------------------

#include <iostream>
#include "Game.hpp"
#include "SplashScreen.hpp"
#include "InputHandler.hpp"
#include "PlayerShip.hpp"
#include "ResourceMapper.hpp"

struct Star
{
    float x;
    float y;
    float z;
};

//Static Member redeclarations
Game::GameState Game::_gameState = Splash;
key_map Game::_keysPressed;
sf::RenderWindow Game::_mainWindow;

void Game::Start()
{
    sf::Image icon;
    icon.loadFromFile("resources/icon.png");

    sf::ContextSettings settings;
    settings.antialiasingLevel = 2;

    _mainWindow.create(sf::VideoMode(resolution.x, resolution.y, 32), "Gyruss",
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
    sf::Event event;
    sf::Clock clock;
    sf::Color color(sf::Color::Black);

    const auto shipPathRadius = (resolution.y / 2) - (resolution.y * 0.08f);

    ResourceMapper resourceMapper;
    PlayerShip playerShip(resourceMapper, shipPathRadius, 0, 0.25);

    //Game Handler
    InputHandler inputHandler;

    //------Star Field------------
    const int width = std::stoi(resourceMapper.getResourceValues("Resolution").at(0));
    const auto height= std::stoi(resourceMapper.getResourceValues("Resolution").at(1));
    const auto number_of_stars = 60;
    const auto maximum_depth = 4;
    const auto star_size = 5;
    const auto star_speed = 0.08;
    auto star_scale = 0.0f;

    std::vector<Star> starField;
    //starField.reserve(number_of_stars);
    sf::RectangleShape star(sf::Vector2f(star_size,star_size));

    //Initialize star random placement
    for( auto i = 0; i < number_of_stars; i++)
    {
        Star temp;
        temp.x = rand() % width - (width / 2.0f);
        temp.y = rand() % height - (height / 2.0f);
        //z-Depth
        temp.z = -1 * 1.0f * (rand() % maximum_depth) - maximum_depth;
        starField.push_back(temp);
    }
    //-----------------------------

    //Game States
    if (_gameState == Game::Splash)
    {
        ShowSplashScreen();
    }

    //Game Loop
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

        inputHandler.resolveKeyMapping(_keysPressed, playerShip);

        //ToDo: Get all the objects to be drawn

        clock.restart();

        _mainWindow.clear(color);

        //----Star Loop-------
        //for( auto i = 0; i < starField.size(); i++)
        for ( auto& sun : starField )
        {
//            point.z += star_speed;
//
//            if (starField.at(i).z >= 0.0f)
//            {
//                starField.at(i).z = -maximum_depth;
//            }
//            if (starField.at(i).z < -maximum_depth)
//            {
//                star_scale = 0;
//            }
            sun.z += star_speed;

            if (sun.z >= 0.0f)
            {
                //reuse stars
               sun.z = -1*maximum_depth;
            }
            if (sun.z < -maximum_depth)
            {
                //tiny
                star_scale = 0;
            }
            else
            {
                star_scale = (sun.z + (maximum_depth))/ (maximum_depth);
            }
            //Dimming
            star.setFillColor(sf::Color(255* star_scale,255* star_scale,255* star_scale));
            //Scaling
            star.setSize(sf::Vector2f(star_size * star_scale, star_size * star_scale));
            //Moving
            star.setPosition(sf::Vector2f(-sun.x / sun.z + (width/2),
                                          sun.y / sun.z + (height/2)));

            _mainWindow.draw(star);
        }

        _mainWindow.draw(playerShip.getSprite());
        //-----------------
        _mainWindow.display();
    }
}

void Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    if (splashScreen.Show(_mainWindow) == 0)
    {
        _gameState = Game::Playing;
        return;
    }
    _gameState = Game::Exiting;
    //Todo : add error codes for missing resources
}