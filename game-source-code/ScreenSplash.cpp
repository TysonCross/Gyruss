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
#include <iostream>

int ScreenSplash::draw(sf::RenderWindow &renderWindow,
                       const TextureHolder &textureHolder,
                       const FontHolder &fontHolder,
                       const sf::Vector2i resolution)
{
    //Get the Splashscreen image
    sf::Sprite splash(textureHolder.get(textures::SplashScreen));
    auto scaleFactor = resolution.x / splash.getGlobalBounds().width;
    splash.setScale(scaleFactor, scaleFactor);

    // Dramatic spacefight
    sf::Sprite spacefight(textureHolder.get(textures::SplashScreenExtra));
    spacefight.setOrigin(spacefight.getGlobalBounds().width / 2, spacefight.getGlobalBounds().height / 2);
    auto spacefightWidth = resolution.x / 2;
    auto spacefightHeight = resolution.y / 2;
    spacefight.setPosition(spacefightWidth, spacefightHeight);

    // Planet animation
    sf::Sprite planet(textureHolder.get(textures::Planet));
    planet.setOrigin(planet.getLocalBounds().width / 12, planet.getLocalBounds().height / 10);
    auto planetWidth = resolution.x / 2;
    auto planetHeight = resolution.y / 2;
    sf::IntRect rectArea = {0, 0, 256, 256};
    planet.setTextureRect(rectArea);
    planet.setPosition(planetWidth, planetHeight);
//    planet.setScale(1.5,1.5);
    auto frame = 1;
    auto incrementer = 1;
    auto animationFPSLimit = 3;

    // Title Text
    sf::Text title("GYRUSS", fontHolder.get(fonts::Title), resolution.y / 3.8);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    auto titleWidth = resolution.x / 2;
    auto titleHeight = resolution.y / 8;
    title.setPosition(titleWidth, titleHeight);

    // Version text
    sf::Text version("version 3.0", fontHolder.get(fonts::Default), 24);
    sf::Color Gray = {70, 70, 70};
    version.setFillColor(Gray);
    version.setPosition(12, 12);

    // Info Text
    sf::Text info("Press spacebar to start", fontHolder.get(fonts::Default), 42);
    sf::Color Purple = {179, 74, 186};
    info.setFillColor(Purple);
    info.setOrigin(info.getGlobalBounds().width / 2, info.getGlobalBounds().height / 2);
    auto infoWidth = resolution.x / 2;;
    auto infoHeight = resolution.y - 60;
    info.setPosition(infoWidth, infoHeight);

    // Control Info
    sf::Sprite controls(textureHolder.get(textures::SplashControls));
    controls.setOrigin(controls.getGlobalBounds().width / 2, controls.getGlobalBounds().height / 2);
    auto controlsWidth = resolution.x / 2 + resolution.x / 3;
    auto controlHeight = resolution.y / 2 + resolution.y / 12;
    controls.setPosition(controlsWidth, controlHeight);

    // highScore info
    // Title
    auto highScoreTitleFontSize = 37;
    sf::Text highScoreTitle("Top Score", fontHolder.get(fonts::Default),
                            highScoreTitleFontSize);
    highScoreTitle.setFillColor(sf::Color::White);
    highScoreTitle.setOrigin(highScoreTitle.getLocalBounds().width / 2,
                             highScoreTitle.getLocalBounds().height / 2);
    auto highScoreTitlePositionX = resolution.x / 5;
    auto highScoreTitlePositionY = resolution.y / 2 - resolution.y / 12;
    highScoreTitle.setPosition(highScoreTitlePositionX,
                               highScoreTitlePositionY);

    // Text
    auto highScoreFontSize = 32;
    sf::Text highScore(getHighScore(),
                       fontHolder.get(fonts::Default),
                       highScoreFontSize);
    highScore.setFillColor(sf::Color::White);
    highScore.setOrigin(highScore.getLocalBounds().width / 2,
                        highScore.getLocalBounds().height / 2);
    auto highScorePositionX = highScoreTitlePositionX;
    auto highScorePositionY = highScoreTitlePositionY + highScoreFontSize + 20;
    highScore.setPosition(highScorePositionX,
                          highScorePositionY);

    auto number_of_stars = 60;
    StarField starField(resolution, 3, number_of_stars);

    // Render
    sf::Event event;
    sf::Clock timer;
    sf::Clock clock;
    sf::Time timeSinceUpdate = sf::Time::Zero;
    float timeStep = 1.f / 60.f;

    while (true)
    {
        timeSinceUpdate += timer.getElapsedTime();
        timer.restart();

        fadeTextInAndOut(info, Purple, 50, clock);

        while (timeSinceUpdate.asSeconds() >= timeStep)
        {
            timeSinceUpdate = sf::Time::Zero;

            renderWindow.clear();

            if (frame == animationFPSLimit)
            {
                frame = 1;
                animatePlanet(planet, rectArea, 6, 5, 29, incrementer);
            }
            else
            {
                frame++;
            }

            for (const auto &element : starField.getStarField())
                starField.moveAndDrawStars(renderWindow, 0.001, 1);

            renderWindow.draw(planet);
            renderWindow.draw(title);
            renderWindow.draw(spacefight);
            renderWindow.draw(version);
            renderWindow.draw(controls);
            renderWindow.draw(highScoreTitle);
            renderWindow.draw(highScore);


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
}

std::string ScreenSplash::getHighScore()
{

    std::string filename = "highscores.txt";
    std::ifstream inputFile(filename,
                            std::ios::in);

    std::string oldHighScore = "0";
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Game::recordHighScore - Unable to open input file: " + filename);
    }
    inputFile.seekg(0, std::ios::beg);

    inputFile >> oldHighScore;
    
    inputFile.close();
    return oldHighScore;

}

void ScreenSplash::animatePlanet(sf::Sprite &sprite,
                                 sf::IntRect &rectArea,
                                 int columns,
                                 int rows,
                                 int frameTotal,
                                 int &i)
{
    auto spriteWidth = 256;
    auto spriteHeight = 256;
    rectArea.left += spriteWidth;

        if (rectArea.left > (spriteWidth * (columns - 1))) // Sprite tileset width - individual tile
        {
            rectArea.left = 0;
            rectArea.top += spriteHeight;

            if (rectArea.top > (spriteHeight * (rows - 1))) // Sprite tileset width - individual tile
            {
                rectArea.top = 0;
            }
        }

    if (i == frameTotal)
    {
        i = 1;
        rectArea.left = 0;
        rectArea.top = 0;
    } else
    {
        i++;
    }

        sprite.setTextureRect(rectArea);
}
