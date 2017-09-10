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
    //---------------------------------------------
    // SHIP CREATION
    int shipAngle = 0;
    const auto shipPathRadius = (gameHeight / 2) - (gameHeight * 0.1);
    sf::Event event;
    sf::Clock clock;
    sf::Color color(sf::Color::Black);

    sf::Texture texture;
    if (!texture.loadFromFile("resources/player_model.png"));
    sf::Sprite ship;

    //sf::Sprite ship(texture);
    //ship.setScale(0.5, 0.5);
    //ship.setOrigin(ship.getGlobalBounds().width / 2, ship.getGlobalBounds().height / 2);

    // SHIP CREATION
    //---------------------------------------------

    PlayerShip playerShip(ship, texture, (gameHeight / 2) - (gameHeight * 0.1),0,0.5);

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


            if (event.type == sf::Event::EventType::KeyPressed)
            {
                if (_keysPressed.count(event.key.code) == 0) //optimisation: should we check against expected/allowed keys
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
            if ((event.key.code == sf::Keyboard::Q) || (event.key.code == sf::Keyboard::X))
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                {
                    _gameState = Game::Exiting;
                    break;
                }
            }
            if (event.key.code == sf::Keyboard::Left)
            playerShip.move(-2, gameWidth, gameHeight);

            if (event.key.code == sf::Keyboard::Right)
                playerShip.move(2, gameWidth, gameHeight);

        } // End of input polling

        //std::cout << "Angle: " << shipAngle;
        // std::cout << " Position: (" << ship.getPosition().x << ", " << ship.getPosition().y << ")";
        //std::cout << " Time between frame: " << clock.getElapsedTime().asMicroseconds();
        //std::cout << std::endl;


        //---------------------------------------------
        // Ship movement
//        shipAngle = shipAngle % 360;
//        if (shipAngle < 0)
//            shipAngle += 360;
//        //Rotate coordinate system by 90 degrees
//        ship.setPosition(shipPathRadius * sin(shipAngle * (pi / 180)) + gameWidth / 2,
//                         shipPathRadius * cos(shipAngle * (pi / 180)) + gameHeight / 2);
//        ship.setRotation(-shipAngle);
        //---------------------------------------------

        playerShip.move(0,gameWidth,gameHeight);

        //Send all inputs to the inputController
        inputHandler.resolveKeyMapping(_keysPressed);

        //Get all objects to be drawn

        clock.restart();

        _mainWindow.clear(color);
        _mainWindow.draw(ship);
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