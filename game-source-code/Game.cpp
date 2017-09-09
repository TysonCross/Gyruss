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
#include "Game.hpp"
#include "SplashScreen.hpp"
#include <cmath>

Game::GameState Game::_gameState = Splash;
sf::RenderWindow Game::_mainWindow;

const int gameWidth = 1920;
const int gameHeight = 1080;
const float pi = 3.1415;

void Game::Start()
{
    sf::Image icon;
    icon.loadFromFile("resources/icon.png");

    _mainWindow.create(sf::VideoMode(gameWidth, gameHeight, 32), "Gyruss",
                       sf::Style::Titlebar | sf::Style::Close);
    _mainWindow.setKeyRepeatEnabled(true);
    _mainWindow.setMouseCursorVisible(false);
    //_mainWindow.setMouseCursorGrabbed(true);
    _mainWindow.setVerticalSyncEnabled(true);
    _mainWindow.setFramerateLimit(60);
    _mainWindow.setIcon(32, 32, icon.getPixelsPtr());

    _gameState = Splash;

    while (_gameState != Game::Exiting)
    {
        GameLoop();
    }
    _mainWindow.close();
}

void Game::GameLoop()
{
    int shipAngle = 0;
    const auto shipPathRadius = (gameHeight/2)-(gameHeight*0.1);
    sf::Event event;
    sf::Clock clock;
    sf::Color color(sf::Color::Black);

    sf::Texture texture;
    if (!texture.loadFromFile("resources/player_model.png"))
    {
        _mainWindow.close();
    }

    sf::Sprite ship(texture);
    ship.setScale(0.5,0.5);
    ship.setOrigin(ship.getGlobalBounds().width/2,ship.getGlobalBounds().height/2);

    if (_gameState == Game::Splash)
    {
        ShowSplashScreen();
    }
    while (_gameState == Game::Playing)
    {
        //Check for events since last frame
        while (_mainWindow.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed :_gameState = Game::Exiting;
                    break;

                case sf::Event::KeyPressed :
                {
                    if ((event.key.code == sf::Keyboard::Q) || (event.key.code == sf::Keyboard::X))
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                            || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                        {
                            _gameState = Game::Exiting;
                            break;
                        }
                    if ((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::Left))
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
                            || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                            shipAngle -= 5;
                        else
                            shipAngle -= 2;

                    if ((event.key.code == sf::Keyboard::D) || (event.key.code == sf::Keyboard::Right))
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
                            || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                            shipAngle += 5;
                        else
                            shipAngle += 2;

                    if (event.key.code == sf::Keyboard::Space)
                    {
                        shipAngle = 0;
                    }

                    break;
                }
            }
        } // End of input polling

            std::cout << "Angle is: " << shipAngle << " and position: (" << ship.getPosition().x << ", " << ship.getPosition().y << ")";
            std::cout << " Elapsed time since last frame: " << clock.getElapsedTime().asMicroseconds() << std::endl;
            clock.restart();

            shipAngle = shipAngle % 360;
            if(shipAngle<0)shipAngle+=360;
            //Rotate coordinate system by 90 degrees
            ship.setPosition(shipPathRadius*sin(shipAngle*(pi/180))+gameWidth/2,shipPathRadius*cos(shipAngle*(pi/180))+gameHeight/2);
            ship.setRotation(-shipAngle);

            //Send all inputs to the inputController

            //Get all objects to be drawn

            _mainWindow.clear(color);
            _mainWindow.draw(ship);
            _mainWindow.display();
        }
    }

void Game::ShowSplashScreen()
{
        SplashScreen splashScreen;
        splashScreen.Show(_mainWindow);
        _gameState = Playing;
}