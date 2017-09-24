/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Description of file in project Project
///
/// Detailed description of file
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "ScreenGameOver.hpp"

int ScreenGameOver::draw(sf::RenderWindow &renderWindow,
                         const TextureHolder &textureHolder,
                         const FontHolder &fontHolder,
                         const sf::Vector2i resolution,
                         const Score &scoreValue)
{
    //Get the ScreenGameOver image
    sf::Sprite gameover(textureHolder.get(textures::GameOverScreen));
    auto scaleFactor = resolution.x/gameover.getGlobalBounds().width;
    gameover.setScale(scaleFactor,scaleFactor);

    // Title Text
    sf::Text title("G A M E   O V E R", fontHolder.get(fonts::Default),resolution.y/6);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    auto titleWidth = resolution.x/2;
    auto titleHeight = resolution.y/13;
    title.setPosition(titleWidth, titleHeight);

    // Info Text
    sf::Text info("Press return to continue", fontHolder.get(fonts::Default), 36);
    info.setFillColor(sf::Color::White);
    info.setOrigin(info.getGlobalBounds().width / 2, info.getGlobalBounds().height / 2);
    auto infoWidth = resolution.x/2;;
    auto infoHeight = resolution.y - 100;
    info.setPosition(infoWidth, infoHeight);

    // Credit Info
    sf::Sprite credits(textureHolder.get(textures::GameOverCredits));
    credits.setOrigin(credits.getGlobalBounds().width / 2, credits.getGlobalBounds().height / 2);
    auto creditsWidth = resolution.x/2-resolution.x/3;
    auto creditsHeight = resolution.y/2+resolution.y/9;
    credits.setPosition(creditsWidth, creditsHeight);

    ///////////////////////////////////
    // RIGHT SIDE
    ///////////////////////////////////
    auto fontSize = 32;
    auto rowPadding = fontSize/3;
    auto sectionPadding = rowPadding*2;
    auto positionX = resolution.x - resolution.x/5.8;
    auto positionY = resolution.y/2.8;


    ///--------------------------------
    // Score
    ///--------------------------------
    // Title
    auto scoreTitleFontSize = fontSize;
    sf::Text scoreTitle("SCORE", fontHolder.get(fonts::Default),
                        scoreTitleFontSize);
    scoreTitle.setFillColor(sf::Color::White);
    scoreTitle.setOrigin(scoreTitle.getLocalBounds().width/2,
                         scoreTitle.getLocalBounds().height/2);
    auto scoreTitlePositionX = positionX;
    auto scoreTitlePositionY = positionY;
    scoreTitle.setPosition(scoreTitlePositionX,
                           scoreTitlePositionY);

    // Text
    auto scoreFontSize = fontSize;
    sf::Text score(common::padIntToString(scoreValue.getScore()),
                   fontHolder.get(fonts::Default),
                   scoreFontSize);
    score.setFillColor(sf::Color::White);
    score.setOrigin(score.getLocalBounds().width/2,
                    score.getLocalBounds().height/2);
    auto scorePositionX = positionX;
    auto scorePositionY = scoreTitlePositionY + scoreFontSize + rowPadding;
    score.setPosition(scorePositionX,
                      scorePositionY);


    ///--------------------------------
    // Bullets Fired
    ///--------------------------------
    // Title
    auto numberBulletsFired = scoreValue.getBulletsFired();
    auto bulletsFiredTitleFontSize = fontSize;
    sf::Text bulletsFiredTitle("PROJECTILES FIRED", fontHolder.get(fonts::Default),
                               bulletsFiredTitleFontSize);
    bulletsFiredTitle.setFillColor(sf::Color::White);
    bulletsFiredTitle.setOrigin(bulletsFiredTitle.getLocalBounds().width / 2,
                                bulletsFiredTitle.getLocalBounds().height / 2);
    auto bulletsFiredTitlePositionX = positionX;
    auto bulletsFiredTitlePositionY =  scorePositionY + bulletsFiredTitleFontSize + sectionPadding;
    bulletsFiredTitle.setPosition(bulletsFiredTitlePositionX,
                                  bulletsFiredTitlePositionY);

    // Text
    auto bulletsFiredFontSize = fontSize;
    sf::Text bulletsFired(common::padIntToString(numberBulletsFired),
                          fontHolder.get(fonts::Default),
                          bulletsFiredFontSize);
    bulletsFired.setFillColor(sf::Color::White);
    bulletsFired.setOrigin(bulletsFired.getLocalBounds().width/2,
                           bulletsFired.getLocalBounds().height/2);
    auto bulletsFiredPositionX = positionX;
    auto bulletsFiredPositionY = bulletsFiredTitlePositionY + bulletsFiredFontSize + rowPadding;
    bulletsFired.setPosition(bulletsFiredPositionX,
                        bulletsFiredPositionY);

    ///--------------------------------
    // Accuracy
    ///--------------------------------
    // Title
    auto accuracyValue = scoreValue.getPlayerAccuracy();
    auto accuracyTitleFontSize = fontSize;
    sf::Text accuracyTitle("ACCURACY", fontHolder.get(fonts::Default),
                               accuracyTitleFontSize);
    accuracyTitle.setFillColor(sf::Color::White);
    accuracyTitle.setOrigin(accuracyTitle.getLocalBounds().width / 2,
                                accuracyTitle.getLocalBounds().height / 2);
    auto accuracyTitlePositionX = positionX;
    auto accuracyTitlePositionY =  bulletsFiredPositionY + accuracyTitleFontSize + sectionPadding;
    accuracyTitle.setPosition(accuracyTitlePositionX,
                                  accuracyTitlePositionY);

    // Text
    auto accuracyFontSize = fontSize;
    auto accuracyAmount = static_cast<int>(accuracyValue*100);
    sf::Text accuracy(std::to_string(accuracyAmount) + "%",
                          fontHolder.get(fonts::Default),
                          accuracyFontSize);
    accuracy.setFillColor(sf::Color::White);
    accuracy.setOrigin(accuracy.getLocalBounds().width/2,
                           accuracy.getLocalBounds().height/2);
    auto accuracyPositionX = positionX;
    auto accuracyPositionY = accuracyTitlePositionY + accuracyFontSize + rowPadding;
    accuracy.setPosition(accuracyPositionX,
                             accuracyPositionY);

    ///--------------------------------
    // Render
    sf::Event event;
    sf::Clock clock;
    while (true)
    {
        renderWindow.clear();
        renderWindow.draw(gameover);
        renderWindow.draw(title);
        renderWindow.draw(credits);
        renderWindow.draw(scoreTitle);
        renderWindow.draw(score);
        renderWindow.draw(bulletsFiredTitle);
        renderWindow.draw(bulletsFired);
        renderWindow.draw(accuracyTitle);
        renderWindow.draw(accuracy);

        fadeTextInAndOut(info,sf::Color::White, 50, clock);

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
                if (event.key.code == sf::Keyboard::Return)
                {
                    return 0; //continue
                }
            }
        }
    }
}
