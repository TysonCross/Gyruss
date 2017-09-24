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
         const TextureHolder &textureHolder,
         const FontHolder &fontHolder,
         const Score &scoreValue,
         const PlayerShip &playerShip) : _resolution{resolution},
                                         _renderWindow{renderWindow},
                                         _textures{textureHolder},
                                         _fonts{fontHolder},
                                         _score{scoreValue},
                                         _playerShip{playerShip}{}

void HUD::draw()
{
    auto fontSize = 36;
    auto rowSpacing = fontSize/2;

    ///////////////////////////////////
    // RIGHT SIDE
    ///////////////////////////////////
    // Lives title
    auto livesTitleFontSize = fontSize;
    std::string lifeTitleText;
    if (_playerShip.getLives()>1)
    {
        lifeTitleText = "LIVES";
    }
    else
    {
        lifeTitleText = "LIVES";
    }
    sf::Text livesTitle(lifeTitleText, _fonts.get(fonts::Default), livesTitleFontSize);
    livesTitle.setFillColor(sf::Color::White);
    livesTitle.setOrigin(livesTitle.getGlobalBounds().left,
                         livesTitle.getGlobalBounds().height/2);
    auto livesTitlePositionX =  _resolution.x/8;
    auto livesTitlePositionY =  _resolution.y/8;
    livesTitle.setPosition(livesTitlePositionX,
                           livesTitlePositionY);



    // Life blocks
    auto lifeBlockRadius = fontSize/common::pi;
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

    ///////////////////////////////////
    // LEFT SIDE
    ///////////////////////////////////
    // Score title
    auto scoreTitleFontSize = fontSize;
    sf::Text scoreTitle("SCORE", _fonts.get(fonts::Default),
                        scoreTitleFontSize);
    scoreTitle.setFillColor(sf::Color::White);
    scoreTitle.setOrigin(scoreTitle.getGlobalBounds().width,
                         scoreTitle.getGlobalBounds().height/2);
    auto scoreTitlePositionX = _resolution.x - _resolution.x/8;
    auto scoreTitlePositionY =  _resolution.y/8;


    scoreTitle.setPosition(scoreTitlePositionX,
                           scoreTitlePositionY);

    // Score Text
    auto scoreFontSize = fontSize;
    sf::Text score(common::padIntToString(_score.getScore()),
                   _fonts.get(fonts::Default),
                   scoreFontSize);
    score.setFillColor(sf::Color::White);
    score.setOrigin(score.getGlobalBounds().width,
                    score.getGlobalBounds().height/2);
    auto scorePositionX = scoreTitlePositionX;
    auto scorePositionY = scoreTitlePositionY + scoreFontSize/2 + rowSpacing;
    score.setPosition(scorePositionX,
                      scorePositionY);

    _renderWindow.draw(livesTitle);

    auto numberOfLivesLeft = _playerShip.getLives();
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
        _renderWindow.draw(scoreTitle);
        _renderWindow.draw(score);

    }
}

