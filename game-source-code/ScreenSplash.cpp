/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/10
/// \brief   Simple Splash Screen
///
/// Class implementation for showing a splash screen with information on how to play the game
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "ScreenSplash.hpp"

int ScreenSplash::draw(sf::RenderWindow &renderWindow,
                       const TextureHolder &textureHolder,
                       const FontHolder &fontHolder,
                       const sf::Vector2i resolution)
{
    //Get the Splashscreen image
    sf::Sprite splash(textureHolder.get(textures::SplashScreen));
    auto scaleFactor = resolution.x/splash.getGlobalBounds().width;
    splash.setScale(scaleFactor,scaleFactor);

    // Dramatic spacefight
    sf::Sprite spacefight(textureHolder.get(textures::SplashScreenExtra));
    spacefight.setOrigin(spacefight.getGlobalBounds().width / 2, spacefight.getGlobalBounds().height / 2);
    auto spacefightWidth = resolution.x/2-resolution.x/12;
    auto spacefightlHeight = resolution.y/2 + resolution.y/8;
    spacefight.setPosition(spacefightWidth, spacefightlHeight);

    // Title Text
    sf::Text title("GYRUSS", fontHolder.get(fonts::Title),resolution.y/3.8);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    auto titleWidth = resolution.x/2;
    auto titleHeight = resolution.y/8;
    title.setPosition(titleWidth, titleHeight);

    // Version text
    sf::Text version("version 2.0", fontHolder.get(fonts::Info), 24);
    sf::Color Gray = {70,70,70};
    version.setFillColor(Gray);
    version.setPosition(12,12);

    // Info Text
    sf::Text info("Press spacebar to start", fontHolder.get(fonts::Info), 42);
    sf::Color Purple = {179,74,186};
    info.setFillColor(Purple);
    info.setOrigin(info.getGlobalBounds().width / 2, info.getGlobalBounds().height / 2);
    auto infoWidth = resolution.x/2;;
    auto infoHeight = resolution.y-60;
    info.setPosition(infoWidth, infoHeight);

    // Control Info
    sf::Sprite controls(textureHolder.get(textures::SplashControls));
    controls.setOrigin(controls.getGlobalBounds().width / 2, controls.getGlobalBounds().height / 2);
    auto controlsWidth = resolution.x/2+resolution.x/3;
    auto controlHeight = resolution.y/2+resolution.y/12;
    controls.setPosition(controlsWidth, controlHeight);

    auto number_of_stars = 60;
    StarField starField(resolution, 3, number_of_stars);

    // Render
    sf::Event event;
    sf::Clock clock;
    while (true)
    {

        renderWindow.clear();
        //renderWindow.draw(splash);

        for (const auto &element : starField.getStarField())
            starField.moveAndDrawStars(renderWindow,0.001,1);

        renderWindow.draw(title);
        renderWindow.draw(spacefight);
        renderWindow.draw(version);
        renderWindow.draw(controls);

        fadeTextInAndOut(info,Purple, 50, clock);

        renderWindow.draw(info);
        renderWindow.display();


        while (renderWindow.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
                && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
            {
                return 1; //send close program
            }
            if (event.type == sf::Event::Closed)
            {
                return 1; //send close program
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    return 0; //continue
                }
            }

        }
    }
}

