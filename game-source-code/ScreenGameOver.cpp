/////////////////////////////////////////////////////////////////////
/// \brief  GameOVer screen object implementation
///
/// To display a splash screen upon game ending, either by fulfilling
/// the victory conditions (win screen), or by losing all lives (lose screen)
/////////////////////////////////////////////////////////////////////

#include "ScreenGameOver.hpp"

ScreenGameOver::ScreenGameOver(bool gameOutcome) : _wonGame{gameOutcome} {}

int ScreenGameOver::draw(sf::RenderWindow &renderWindow,
                         const TextureHolder &textureHolder,
                         const FontHolder &fontHolder,
                         const sf::Vector2i resolution,
                         const Score &scoreValue)
{
    //Get the ScreenGameOver image
    sf::Sprite gameOver;
    if (_wonGame)
        gameOver.setTexture(textureHolder.get(textures::GameOverWinScreen));
    else
        gameOver.setTexture(textureHolder.get(textures::GameOverLoseScreen));

    auto scaleFactor = resolution.x/gameOver.getGlobalBounds().width;
    gameOver.setScale(scaleFactor,scaleFactor);

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
    auto fontSize = static_cast<unsigned int>(32);
    auto rowPadding = fontSize/3;
    auto sectionPadding = rowPadding*2;
    auto positionX = static_cast<unsigned int>(resolution.x - resolution.x/5.8);
    auto positionY = static_cast<unsigned int>(resolution.y/2.8);


    ///--------------------------------
    // Score
    ///--------------------------------
    // Title
    sf::Text scoreTitle("SCORE", fontHolder.get(fonts::Default),
                        fontSize);
    scoreTitle.setFillColor(sf::Color::White);
    scoreTitle.setOrigin(scoreTitle.getLocalBounds().width/2,
                         scoreTitle.getLocalBounds().height/2);
    auto scoreTitlePositionX = positionX;
    auto scoreTitlePositionY = positionY;
    scoreTitle.setPosition(scoreTitlePositionX,
                           scoreTitlePositionY);

    // Text
    sf::Text score(common::padIntToString(scoreValue.getScore()),
                   fontHolder.get(fonts::Default),
                   fontSize);
    score.setFillColor(sf::Color::White);
    score.setOrigin(score.getLocalBounds().width/2,
                    score.getLocalBounds().height/2);
    auto scorePositionX = positionX;
    auto scorePositionY = scoreTitlePositionY + fontSize + rowPadding;
    score.setPosition(scorePositionX,
                      scorePositionY);

    ///--------------------------------
    // Longest Time Alive
    ///--------------------------------
    // Title
    sf::Text maxTimeTitle("LONGEST LIFE", fontHolder.get(fonts::Default),
                          fontSize);
    maxTimeTitle.setFillColor(sf::Color::White);
    maxTimeTitle.setOrigin(maxTimeTitle.getLocalBounds().width / 2,
                           maxTimeTitle.getLocalBounds().height / 2);
    auto timeTitlePositionX = positionX;
    auto timeTitlePositionY =  scorePositionY + fontSize + sectionPadding;
    maxTimeTitle.setPosition(timeTitlePositionX,
                             timeTitlePositionY);

    // Text
    std::string maxTimeText = common::padIntToString(static_cast<unsigned int>(scoreValue.getLongestTimeAlive()));
    sf::Text maxTime((maxTimeText) + " seconds",
                     fontHolder.get(fonts::Default),
                     fontSize);
    maxTime.setFillColor(sf::Color::White);
    maxTime.setOrigin(maxTime.getLocalBounds().width/2,
                      maxTime.getLocalBounds().height/2);
    auto maxTimePositionX = positionX;
    auto maxTimePositionY = timeTitlePositionY + fontSize + rowPadding;
    maxTime.setPosition(maxTimePositionX,
                        maxTimePositionY);

    ///--------------------------------
    // Bullets Fired
    ///--------------------------------
    // Title
    auto numberBulletsFired = scoreValue.getBulletsFired();
    sf::Text bulletsFiredTitle("PROJECTILES FIRED", fontHolder.get(fonts::Default),
                               fontSize);
    bulletsFiredTitle.setFillColor(sf::Color::White);
    bulletsFiredTitle.setOrigin(bulletsFiredTitle.getLocalBounds().width / 2,
                                bulletsFiredTitle.getLocalBounds().height / 2);
    auto bulletsFiredTitlePositionX = positionX;
    auto bulletsFiredTitlePositionY =  maxTimePositionY + fontSize + sectionPadding;
    bulletsFiredTitle.setPosition(bulletsFiredTitlePositionX,
                                  bulletsFiredTitlePositionY);

    // Text
    sf::Text bulletsFired(common::padIntToString(numberBulletsFired),
                          fontHolder.get(fonts::Default),
                          fontSize);
    bulletsFired.setFillColor(sf::Color::White);
    bulletsFired.setOrigin(bulletsFired.getLocalBounds().width/2,
                           bulletsFired.getLocalBounds().height/2);
    auto bulletsFiredPositionX = positionX;
    auto bulletsFiredPositionY = bulletsFiredTitlePositionY + fontSize + rowPadding;
    bulletsFired.setPosition(bulletsFiredPositionX,
                        bulletsFiredPositionY);

    ///--------------------------------
    // Accuracy
    ///--------------------------------
    // Title
    auto accuracyValue = scoreValue.getPlayerAccuracy();
    sf::Text accuracyTitle("ACCURACY", fontHolder.get(fonts::Default),
                           fontSize);
    accuracyTitle.setFillColor(sf::Color::White);
    accuracyTitle.setOrigin(accuracyTitle.getLocalBounds().width / 2,
                                accuracyTitle.getLocalBounds().height / 2);
    auto accuracyTitlePositionX = positionX;
    auto accuracyTitlePositionY =  bulletsFiredPositionY + fontSize + sectionPadding;
    accuracyTitle.setPosition(accuracyTitlePositionX,
                                  accuracyTitlePositionY);

    // Text
    auto accuracyAmount = static_cast<int>(accuracyValue*100);
    sf::Text accuracy(std::to_string(accuracyAmount) + "%",
                          fontHolder.get(fonts::Default),
                      fontSize);
    accuracy.setFillColor(sf::Color::White);
    accuracy.setOrigin(accuracy.getLocalBounds().width/2,
                           accuracy.getLocalBounds().height/2);
    auto accuracyPositionX = positionX;
    auto accuracyPositionY = accuracyTitlePositionY + fontSize + rowPadding;
    accuracy.setPosition(accuracyPositionX,
                             accuracyPositionY);

    ///--------------------------------
    // Render
    sf::Event event;
    sf::Clock clock;
    while (true)
    {
        renderWindow.clear();
        renderWindow.draw(gameOver);
        renderWindow.draw(title);
        renderWindow.draw(credits);
        renderWindow.draw(scoreTitle);
        renderWindow.draw(score);
        renderWindow.draw(maxTimeTitle);
        renderWindow.draw(maxTime);
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
