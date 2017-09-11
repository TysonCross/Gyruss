/////////////////////////////////////////////////////////////////////
/// Student  1239448 & 1101946
/// \file    SplashScreen.cpp
/// \authors Tyson Cross and Chris Maree
/// \date    2017/09/10
/// \brief   Simple Splash Screen
///
/// Implementation of showing a splash screen
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "SplashScreen.hpp"
#include "common.hpp"

int SplashScreen::show(sf::RenderWindow &renderWindow, ResourceMapper &resourceMapper)
{
    //Get the Splashscreen image
    sf::Texture splashScreen;
    if (!splashScreen.loadFromFile(resourceMapper.getResource("SplashScreen")))
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
    sf::Text title;
    title.setFont(font);
    title.setString("GYRUSS");
    title.setCharacterSize(256); // in pixels, not points!
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    auto titleWidth = std::stoi(resourceMapper.getResourceValues("Resolution").at(0))/2;
    auto titleHeight = std::stoi(resourceMapper.getResourceValues("Resolution").at(1))/6;
    title.setPosition(titleWidth,titleHeight);

    renderWindow.clear();
    renderWindow.draw(splash);
    renderWindow.draw(title);
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