//--------------------------------------------------------------------------
// Student  1239448
// @file    SplashScreen.cpp
// @author  Tyson Cross and Chris Maree
// @date    2017/09/09
// @brief   Simple Splash Screen.
//
// Implementation of showing a splash screen
//
// Copyright (c) 2017 Tyson Cross and Chris Maree, Wits University, All rights reserved.
//--------------------------------------------------------------------------

#include "SplashScreen.hpp"
#include "common.hpp"

int SplashScreen::Show(sf::RenderWindow &renderWindow)
{
    //Splashscreen image
    sf::Texture splashScreen;
    if (!splashScreen.loadFromFile("resources/splash.png"))
    {
        return -1; //execution error; resource missing
    }
    sf::Sprite splash(splashScreen);

    // Title Text
    sf::Font font;
    if (!font.loadFromFile("resources/danube.ttf"))
    {
        return -1; //execution error; resource missing
    }
    sf::Text text;
    text.setFont(font);
    text.setString("GYRUSS");
    text.setCharacterSize(256); // in pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(resolution.x/2, resolution.y/6);


    renderWindow.clear();
    renderWindow.draw(splash);
    renderWindow.draw(text);
    renderWindow.display();

    sf::Event event;
    while (true)
    {
        while (renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::MouseButtonPressed)
            {
                return 0; //continue
            }
            if (event.type==sf::Event::Closed){
                return 1; //send close program
            }
        }
    }
}