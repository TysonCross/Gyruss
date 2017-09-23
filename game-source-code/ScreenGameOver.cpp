/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Simple Game Over / Death Screen implementation
///
/// Class Implementation for showing a screen with information on how to the score
/// and asking for input from player as an option to restart the game
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "ScreenGameOver.hpp"

int ScreenGameOver::draw(sf::RenderWindow &renderWindow,
                         const TextureHolder &textureHolder,
                         const FontHolder &fontHolder,
                         const sf::Vector2i resolution,
                         const Score &score)
{
    //Get the ScreenGameOver image
    sf::Sprite gameover(textureHolder.get(textures::GameOverScreen));
    auto scaleFactor = resolution.x/gameover.getGlobalBounds().width;
    gameover.setScale(scaleFactor,scaleFactor);

    // Title Text
    sf::Text title("G A M E   O V E R", fontHolder.get(fonts::Info),resolution.y/6);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    auto titleWidth = resolution.x/2;
    auto titleHeight = resolution.y/13;
    title.setPosition(titleWidth, titleHeight);

    // Info Text
    sf::Text info("Press return to continue", fontHolder.get(fonts::Info), 36);
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

    // Render
    sf::Event event;
    sf::Clock clock;
    while (true)
    {
        renderWindow.clear();
        renderWindow.draw(gameover);
        renderWindow.draw(title);
        renderWindow.draw(credits);

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
