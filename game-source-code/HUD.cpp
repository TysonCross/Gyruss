/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    21/9/17
/// \brief   Head Up Display showing the score, player lives
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////



#include "HUD.hpp"

HUD::HUD(const sf::Vector2i resolution,
         sf::RenderWindow &renderWindow,
         const FontHolder &fontHolder,
         const Score &scoreValue,
         const PlayerShip &playerShip) : _resolution{resolution},
                                         _renderWindow{renderWindow},
                                         _fonts{fontHolder},
                                         _score{scoreValue},
                                         _playerShip{playerShip}{}

void HUD::draw()
{
    auto numberOfLivesLeft = _playerShip.getLives();
    auto fontSize =static_cast<unsigned int>(36);
    auto rowSpacing = fontSize/2;

    ///////////////////////////////////
    // RIGHT SIDE
    ///////////////////////////////////
    // Lives title
    std::string lifeTitleText;
    if (numberOfLivesLeft>1)
    {
        lifeTitleText = "LIVES";
    }
    else
    {
        lifeTitleText = "LIFE";
    }
    sf::Text livesTitle(lifeTitleText, _fonts.get(fonts::Default), fontSize);
    livesTitle.setFillColor(sf::Color::White);
    livesTitle.setOrigin(livesTitle.getGlobalBounds().left,
                         livesTitle.getGlobalBounds().height/2);
    auto livesTitlePositionX =  _resolution.x/8;
    auto livesTitlePositionY =  _resolution.y/8;
    livesTitle.setPosition(livesTitlePositionX,
                           livesTitlePositionY);



    // Life blocks
    auto lifeBlockRadius = fontSize/ M_PI; //common::pi;
    auto lifeBlockSpacing = fontSize*0.9;

    sf::CircleShape lifeBlock1;
    lifeBlock1.setFillColor(sf::Color::White);
    lifeBlock1.setRadius(lifeBlockRadius);
    lifeBlock1.setOrigin(lifeBlock1.getGlobalBounds().left,
                         lifeBlock1.getGlobalBounds().height/2);
    auto lifeBlock1PositionX =  livesTitlePositionX;
    auto lifeBlock1PositionY =  livesTitlePositionY + lifeBlockSpacing + rowSpacing;
    lifeBlock1.setPosition(lifeBlock1PositionX,lifeBlock1PositionY);

    sf::CircleShape lifeBlock2;
    lifeBlock2.setFillColor(sf::Color::White);
    lifeBlock2.setRadius(lifeBlockRadius);
    lifeBlock2.setOrigin(lifeBlock2.getGlobalBounds().left,
                         lifeBlock2.getGlobalBounds().height/2);
    auto lifeBlock2PositionX =  lifeBlock1PositionX + lifeBlockSpacing;
    auto lifeBlock2PositionY =  lifeBlock1PositionY;
    lifeBlock2.setPosition(lifeBlock2PositionX,lifeBlock2PositionY);

    sf::CircleShape lifeBlock3;
    lifeBlock3.setFillColor(sf::Color::White);
    lifeBlock3.setRadius(lifeBlockRadius);
    lifeBlock3.setOrigin(lifeBlock3.getGlobalBounds().left,
                         lifeBlock3.getGlobalBounds().height/2);
    auto lifeBlock3PositionX =  lifeBlock2PositionX + lifeBlockSpacing;
    auto lifeBlock3PositionY =  lifeBlock1PositionY;
    lifeBlock3.setPosition(lifeBlock3PositionX,lifeBlock3PositionY);
    
    // Enemies Killed
    std::string enemiesKilledText = common::padIntToString(int(100 - _score.getEnemiesKilled()));
    sf::Text enemiesKilled(enemiesKilledText,
                       _fonts.get(fonts::Default),
                       fontSize);
    enemiesKilled.setFillColor(sf::Color::White);
    enemiesKilled.setOrigin(enemiesKilled.getGlobalBounds().left,
                        enemiesKilled.getGlobalBounds().height/2);
    auto enemiesKilledPositionX = livesTitlePositionX;
    auto enemiesKilledPositionY = _resolution.y - _resolution.y/8;
    enemiesKilled.setPosition(enemiesKilledPositionX,
                          enemiesKilledPositionY);

    ///////////////////////////////////
    // LEFT SIDE
    ///////////////////////////////////
    // Score title
    sf::Text scoreTitle("SCORE", _fonts.get(fonts::Default),
                        fontSize);
    scoreTitle.setFillColor(sf::Color::White);
    scoreTitle.setOrigin(scoreTitle.getGlobalBounds().width,
                         scoreTitle.getGlobalBounds().height/2);
    auto scoreTitlePositionX = _resolution.x - _resolution.x/8;
    auto scoreTitlePositionY =  _resolution.y/8;


    scoreTitle.setPosition(scoreTitlePositionX,
                           scoreTitlePositionY);

    // Score Text
    sf::Text score(common::padIntToString(_score.getScore()),
                   _fonts.get(fonts::Default),
                   fontSize);
    score.setFillColor(sf::Color::White);
    score.setOrigin(score.getGlobalBounds().width,
                    score.getGlobalBounds().height/2);
    auto scorePositionX = scoreTitlePositionX;
    auto scorePositionY = scoreTitlePositionY + fontSize/2 + rowSpacing;
    score.setPosition(scorePositionX,
                      scorePositionY);

    // Time alive title
    std::string timeAliveText = "ALIVE";
    if (_playerShip.isInvulnerable())
        timeAliveText = "INVULNERABLE";
    if (numberOfLivesLeft==0)
        timeAliveText = "DEAD";
    if (_playerShip.isUpgraded())
        timeAliveText = "UPGRADED";
    sf::Text timeAliveTitle(timeAliveText, _fonts.get(fonts::Default),
                            fontSize);
    timeAliveTitle.setFillColor(sf::Color::White);
    timeAliveTitle.setOrigin(timeAliveTitle.getGlobalBounds().width,
                         timeAliveTitle.getGlobalBounds().height/2);
    auto timeAliveTitlePositionX = scoreTitlePositionX;
    auto timeAliveTitlePositionY = _resolution.y - _resolution.y/8;


    timeAliveTitle.setPosition(timeAliveTitlePositionX,
                           timeAliveTitlePositionY);

    // timeAlive Text
    std::string maxTimeText = common::padIntToString(int(_score.getTimeAlive()));
    sf::Text timeAlive(maxTimeText,
                   _fonts.get(fonts::Default),
                       fontSize);
    timeAlive.setFillColor(sf::Color::White);
    timeAlive.setOrigin(timeAlive.getGlobalBounds().width,
                    timeAlive.getGlobalBounds().height/2);
    auto timeAlivePositionX = timeAliveTitlePositionX;
    auto timeAlivePositionY = timeAliveTitlePositionY - fontSize/2 - rowSpacing;
    timeAlive.setPosition(timeAlivePositionX,
                      timeAlivePositionY);


    _renderWindow.draw(livesTitle);
    if (numberOfLivesLeft > 0)
    {
        _renderWindow.draw(lifeBlock1);
        if (numberOfLivesLeft > 1)
        {
            _renderWindow.draw(lifeBlock2);
            if (numberOfLivesLeft > 2)
            {
                _renderWindow.draw(lifeBlock3);
            }
        }
    }
    _renderWindow.draw(enemiesKilled);

    _renderWindow.draw(scoreTitle);
    _renderWindow.draw(score);

    _renderWindow.draw(timeAliveTitle);
    _renderWindow.draw(timeAlive);
}

