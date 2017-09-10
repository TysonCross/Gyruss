//--------------------------------------------------------------------------
// Student  1239448
// @file    SplashScreen.cpp
// @author  Tyson Cross
// @date    2017/09/09
// @brief   Simple Splash Screen.
//
// Implementation of showing a splash screen
//
// Copyright (c) 2017 Tyson Cross, Wits University, All rights reserved.
//--------------------------------------------------------------------------

#include "SplashScreen.hpp"
int SplashScreen::Show(sf::RenderWindow &renderWindow)
{
    sf::Texture splashScreen;
    if (!splashScreen.loadFromFile("resources/splash.png"))
    {
        return -1; //execution error; resource missing
    }

    sf::Sprite splash(splashScreen);

    renderWindow.draw(splash);
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