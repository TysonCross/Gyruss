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
                       const sf::Vector2i resolution)
{
    sf::Sound splashSound;
    splashSound.setBuffer(soundHolder.get(sounds::StartSound));
    splashSound.play();

    //Get the Splashscreen image
    sf::Sprite splash(textureHolder.get(textures::SplashScreen));
    auto scaleFactor = resolution.x/splash.getGlobalBounds().width;
    splash.setScale(scaleFactor,scaleFactor);

    // Title Text
    sf::Text title("GYRUSS", fontHolder.get(fonts::Title),resolution.y/3.8);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    auto titleWidth = resolution.x/2;
    auto titleHeight = resolution.y/8;
    title.setPosition(titleWidth, titleHeight);

    // Version text
    sf::Text version("version 1.0", fontHolder.get(fonts::Info), 24);
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
    info.setPosition(infoWidth, infoHeight);

    // Control Info
    sf::Sprite controls(textureHolder.get(textures::SplashControls));
    controls.setOrigin(controls.getGlobalBounds().width / 2, controls.getGlobalBounds().height / 2);
    auto controlsWidth = resolution.x/2+resolution.x/3;
    auto controlHeight = resolution.y/2+resolution.y/9;
    controls.setPosition(controlsWidth, controlHeight);

    // Render
    sf::Event event;
    sf::Clock clock;
    while (true)
    {
        renderWindow.clear();
        renderWindow.draw(splash);
        renderWindow.draw(title);
        renderWindow.draw(version);
        renderWindow.draw(controls);

        fadeTextInAndOut(info,Purple, 50, clock);

        renderWindow.draw(info);
        renderWindow.display();


        while (renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::MouseButtonPressed)
            {
                return 0; //continue
            }
            if (event.type == sf::Event::Closed)
            {
                return 1; //send close program
            }
        }
    }
}


void SplashScreen::fadeTextInAndOut(sf::Text &text, sf::Color color, int frequency, sf::Clock& clock)
{
    float change = float(clock.getElapsedTime().asSeconds());
    change = common::radToDegree(common::angleFilter(change));
    auto i = fabs(sin(change*1/frequency));
    text.setFillColor(sf::Color(i*color.r,i*color.g,i*color.b));
}
