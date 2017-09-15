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

int SplashScreen::show(sf::RenderWindow &renderWindow,
                       const TextureHolder &textureHolder,
                       const SoundHolder &soundHolder,
                       const FontHolder &fontHolder,
                       common::Resolution resolution)
{
    //Get the Splashscreen image
    sf::Sprite splash(textureHolder.get(textures::SplashScreen));
    auto scaleFactor = resolution.x/splash.getGlobalBounds().width;
    splash.setScale(scaleFactor,scaleFactor);

    // Title Text
    sf::Text title("GYRUSS", fontHolder.get(fonts::Title),250);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    auto titleWidth = resolution.x/2;
    auto titleHeight = resolution.y/8;
    title.setPosition(titleWidth,titleHeight);

    // Version text
    sf::Text version("version 0.1", fontHolder.get(fonts::Info), 24);
    sf::Color Gray = {70,70,70};
    version.setFillColor(Gray);
    version.setPosition(12,12);

    // Info Text
    sf::Text info("Press any key to start", fontHolder.get(fonts::Info), 42);
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