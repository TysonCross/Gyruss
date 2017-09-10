//--------------------------------------------------------------------------
// Student  1239448
// @file    Game.cpp
// @author  Tyson Cross
// @date    2017/09/09
// @brief   Main Game controller implementation
//
// Implements the Game loop, and game states
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------

#include <iostream>
#include <cmath>

#include "Game.hpp"
#include "SplashScreen.hpp"
#include "InputHandler.hpp"
#include "PlayerShip.hpp"

Game::GameState Game::_gameState = Splash;
key_map Game::_keysPressed;
sf::RenderWindow Game::_mainWindow;

void
Game::Start()
{
    sf::Image icon;
    icon.loadFromFile("resources/icon.png");

    _mainWindow.create(sf::VideoMode(gameWidth, gameHeight, 32), "Gyruss",
                       sf::Style::Titlebar | sf::Style::Close);
    //_mainWindow.setKeyRepeatEnabled(true);
    //_mainWindow.setMouseCursorVisible(false);
    _mainWindow.setVerticalSyncEnabled(true);
    _mainWindow.setFramerateLimit(60);
    _mainWindow.setIcon(32, 32, icon.getPixelsPtr());

    while (_gameState != Game::Exiting)
    {
        GameLoop();
    }
    _mainWindow.close();
}

void
Game::GameLoop()
{

    sf::Event event;
    sf::Clock clock;
    sf::Color color(sf::Color::Black);

    //Todo: the sprite and texture should be created by and in the playerShip object
    sf::Texture shipTexture;
    sf::Sprite shipSprite;
    const auto shipPathRadius = (gameHeight / 2) - (gameHeight * 0.1f);
    PlayerShip playerShip(shipSprite, shipTexture, shipPathRadius,0 , 0.25);

    //Game Handler
    InputHandler inputHandler;

    if (_gameState == Game::Splash)
    {
        ShowSplashScreen();
    }
    while (_gameState == Game::Playing)
    {
        //Check for events since last frame
        while (_mainWindow.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
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

        //Get all objects to be drawn

        clock.restart();

        _mainWindow.clear(color);
        _mainWindow.draw(playerShip.getSprite());
        _mainWindow.display();
    }
}

void
Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.Show(_mainWindow);
    _gameState = Playing;
}