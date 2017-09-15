/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/10
/// \brief   Simple Splash Screen
///
/// Implementation of showing a splash screen
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "SplashScreen.hpp"
#include "common.hpp"
#include <iostream>

int SplashScreen::show(sf::RenderWindow &renderWindow, ResourceHolder &resourceMapper, common::Resolution resolution)
{
    //Get the Splashscreen image
    sf::Texture splashScreen;
    if (!splashScreen.loadFromFile(resourceMapper.getResource("SplashScreen")))
    {
        return -1; //execution error; resource missing
    }
    sf::Sprite splash(splashScreen);
    auto scaleFactor = resolution.x/splash.getGlobalBounds().width;
    splash.setScale(scaleFactor,scaleFactor);

    // Title Text
    sf::Font font;
    if (!font.loadFromFile("resources/danube.ttf"))
    {
        return -1; //execution error; resource missing
    }
    sf::Text title("GYRUSS", font, 250);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    auto titleWidth = resolution.x/2;
    auto titleHeight = resolution.y/8;
    title.setPosition(titleWidth,titleHeight);

    // Version text
    sf::Font font_version;
    if (!font_version.loadFromFile("resources/fax_sans_beta.otf"))
    {
        return -1; //execution error; resource missing
    }
    sf::Text version("version 0.1", font_version, 24);
    sf::Color Gray = {70,70,70};
    version.setFillColor(Gray);
    version.setPosition(12,12);

    // Info Text
    sf::Text info("Press any key to start", font_version, 42);
    sf::Color Purple = {179,74,186};
    info.setFillColor(Purple);
    info.setOrigin(info.getGlobalBounds().width / 2, info.getGlobalBounds().height / 2);
    auto infoWidth = resolution.x/2;;
    auto infoHeight = resolution.y-60;
    info.setPosition(infoWidth,infoHeight);

    // Render
    renderWindow.clear();
    renderWindow.draw(splash);
    renderWindow.draw(title);
    renderWindow.draw(version);
    renderWindow.draw(info);
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