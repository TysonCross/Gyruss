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

int ScreenGameOver::show(sf::RenderWindow &renderWindow,
                       const TextureHolder &textureHolder,
                       const SoundHolder &soundHolder,
                       const FontHolder &fontHolder,
                       const sf::Vector2i resolution)
{
    // Play audio cue
    sf::Sound gameoverSound;
    gameoverSound.setBuffer(soundHolder.get(sounds::GameOverSound));
    gameoverSound.play();
    //Get the ScreenGameOver image
    sf::Sprite gameover(textureHolder.get(textures::GameOverScreen));
    auto scaleFactor = resolution.x/gameover.getGlobalBounds().width;
    gameover.setScale(scaleFactor,scaleFactor);

    // Title Text
    sf::Text title("GAME OVER", fontHolder.get(fonts::Info),resolution.y/6);
    title.setFillColor(sf::Color::Red);
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    auto titleWidth = resolution.x/2;
    auto titleHeight = resolution.y/10;
    title.setPosition(titleWidth, titleHeight);

    // Info Text
    sf::Text info("Press enter to restart", fontHolder.get(fonts::Info), 42);
    info.setFillColor(sf::Color::White);
    info.setOrigin(info.getGlobalBounds().width / 2, info.getGlobalBounds().height / 2);
    auto infoWidth = resolution.x/2;;
    auto infoHeight = resolution.y/4;
    info.setPosition(infoWidth, infoHeight);

    // Render
    sf::Event event;
    sf::Clock clock;
    while (true)
    {
        renderWindow.clear();
        renderWindow.draw(gameover);
        renderWindow.draw(title);

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
