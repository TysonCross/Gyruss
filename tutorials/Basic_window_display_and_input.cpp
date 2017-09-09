//--------------------------------------------------------------------------
// Student  1239448
// @file    main.cpp
// @author  Tyson Cross
// @date    6/9/17
// @brief   Exploratory SFML code
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------
#include <iostream>
#include "SFML/Graphics.hpp"
#include <random>

int main(int argc, char **argv)
{
    const int gameWidth = 1920;
    const int gameHeight = 1080;
    sf::Image icon;
    icon.loadFromFile("resources/icon.png");

    sf::Texture splashScreen;
    splashScreen.loadFromFile("resources/splash.png");
    sf::Sprite splash(splashScreen);

    sf::RenderWindow renderWindow(sf::VideoMode(gameWidth, gameHeight, 32), "Gyruss",
                                  sf::Style::Titlebar | sf::Style::Close);
    //renderWindow.setKeyRepeatEnabled(false);
    //renderWindow.setMouseCursorVisible(false);
    renderWindow.setVerticalSyncEnabled(true);
    renderWindow.setFramerateLimit(60);
    renderWindow.setIcon(32, 32, icon.getPixelsPtr());

    sf::Event event;
    sf::Clock clock;

    sf::Color color(sf::Color::Black);

    while (renderWindow.isOpen())
    {
        //Check for events since last frame open
        while (renderWindow.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed : renderWindow.close();
                    break;

                case sf::Event::KeyPressed :
                    if ((event.key.code == sf::Keyboard::Q) || (event.key.code == sf::Keyboard::X))
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                            || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                        {
                            renderWindow.close();
                            break;
                        }

                    if ((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::Left))
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                            || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                            color.r = 255;
                        if (color.r < 255)
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
                                || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                                color.r += 5;
                            else
                                color.r += 1;
                    }

                    if ((event.key.code == sf::Keyboard::S) || (event.key.code == sf::Keyboard::Down))
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                            || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                            color.g = 255;
                        if (color.g < 255)
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
                                || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                                color.g += 5;
                            else
                                color.g += 1;
                    }

                    if ((event.key.code == sf::Keyboard::D) || (event.key.code == sf::Keyboard::Right))
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                            || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                            color.b = 255;
                        if (color.b < 255)
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
                                || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                                color.b += 5;
                            else
                                color.b += 1;
                    }

                    if (event.key.code == sf::Keyboard::Space)
                    {
                        color.r = 0;
                        color.g = 0;
                        color.b = 0;

                    }

                    break;

                default :break;
            }
        }

        std::cout << "Elapsed time since last frame: " << clock.getElapsedTime().asMicroseconds() << std::endl;
        clock.restart();

        renderWindow.clear(color);
        renderWindow.display();
    }
}
