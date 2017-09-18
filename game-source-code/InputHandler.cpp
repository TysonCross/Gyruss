/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   Read in the map of current keypresses
///
/// Reads in the key presses during the last polled game Loop,
/// and maps these keys to actions
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "InputHandler.hpp"
#include "Game.hpp"

void InputHandler::pollInput(game::GameState &gameState,
                             PlayerShip &playerShip,
                             const sf::Event &event,
                             bool &previousButtonState)
{
    if (event.type == sf::Event::Closed)
    {
        gameState = game::GameState::Exiting;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
        && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
    {
        gameState = game::GameState::Exiting;
    }


    if (event.type == sf::Event::EventType::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left)
        {
            _isMovingLeft = true;
        }
        if (event.key.code == sf::Keyboard::Right)
        {
            _isMovingRight = true;
        }
        if (event.key.code == sf::Keyboard::Space)
            if (previousButtonState == 0)
            {
                playerShip.setShoot();
                previousButtonState = 1;
            }
    }

    if (event.type == sf::Event::EventType::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Left)
        {
            _isMovingLeft = false;
        }
        if (event.key.code == sf::Keyboard::Right)
        {
            _isMovingRight = false;
        }
        if (event.key.code == sf::Keyboard::Space)
        {
            previousButtonState = 0;
        }
    }
}

void InputHandler::update(PlayerShip &playerShip, float deltaTime)
{
    const auto moveAmount = 260.f;
    auto move = 0.f;

    if (_isMovingLeft)
    {
        move -= moveAmount;

    }
    if (_isMovingRight)
    {
        move += moveAmount;
    }

    playerShip.setMove(move * deltaTime);
}
