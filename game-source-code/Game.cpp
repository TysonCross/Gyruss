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

Game::GameState Game::_gameState = Splash;
sf::RenderWindow Game::_mainWindow;
const int gameWidth = 1080;
const int gameHeight = 1080;

void Game::Start(void)
{

    sf::Image icon;
    icon.loadFromFile("resources/icon.png");

    _mainWindow.create(sf::VideoMode(gameWidth, gameHeight, 32), "Gyruss",
                       sf::Style::Titlebar | sf::Style::Close);
    _mainWindow.setKeyRepeatEnabled(true);
    _mainWindow.setMouseCursorVisible(false);
    _mainWindow.setVerticalSyncEnabled(true);
    _mainWindow.setMouseCursorGrabbed(true);
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
    sf::Event event;
    sf::Clock clock;
    sf::Color color(sf::Color::Black);

    sf::Texture texture;
    if (!texture.loadFromFile("resources/player_model.png"))
    {
        _mainWindow.close();
    }

    sf::Sprite ship(texture);
    ship.setOrigin(ship.getGlobalBounds().width/2,ship.getGlobalBounds().height/2);
    ship.setPosition(gameWidth/2, gameHeight/2);

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
                        ship.move(-5, 0);

                    if ((event.key.code == sf::Keyboard::D) || (event.key.code == sf::Keyboard::Right))
                        ship.move(5, 0);

                    break;
                }
            }

            std::cout << "Elapsed time since last frame: " << clock.getElapsedTime().asMicroseconds() << std::endl;
            clock.restart();

            _mainWindow.clear(color);
            _mainWindow.draw(ship);
            _mainWindow.display();
        }
    }
}

void Game::ShowSplashScreen()
{
        SplashScreen splashScreen;
        splashScreen.Show(_mainWindow);
        _gameState = Playing;
}