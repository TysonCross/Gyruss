/////////////////////////////////////////////////////////////////////
/// \brief   Read in the map of current keypresses
///
/// Reads in the key presses during the last polled game Loop,
/// and maps these keys to actions
/////////////////////////////////////////////////////////////////////

#include "InputHandler.hpp"

InputHandler::InputHandler() : _previousButtonState{false}
{}

void InputHandler::pollInput(game::GameState &gameState,
                             PlayerShip &playerShip,
                             const Event &event)
{
    if (event.type == Event::Closed)
    {
        gameState = game::GameState::Exiting;
    }

    if (Keyboard::isKeyPressed(Keyboard::Q)
        && (Keyboard::isKeyPressed(Keyboard::LControl)
            || Keyboard::isKeyPressed(Keyboard::RControl)))
    {
        gameState = game::GameState::Exiting;
    }


    if (event.type == Event::EventType::KeyPressed)
    {
        if (event.key.code == Keyboard::Left)
        {
            _isMovingLeft = true;
        }
        if (event.key.code == Keyboard::Right)
        {
            _isMovingRight = true;
        }
        if (event.key.code == Keyboard::Space)
            if (_previousButtonState == 0)
            {
                playerShip.setShoot();
                _previousButtonState = 1;
            }
    }

    if (event.type == Event::EventType::KeyReleased)
    {
        if (event.key.code == Keyboard::Left)
        {
            _isMovingLeft = false;
        }
        if (event.key.code == Keyboard::Right)
        {
            _isMovingRight = false;
        }
        if (event.key.code == Keyboard::Space)
        {
            _previousButtonState = 0;
        }
    }
}

void InputHandler::setPlayerShipMove(PlayerShip &playerShip, const float deltaTime)
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

void InputHandler::reset()
{
    _isMovingLeft = false;
    _isMovingRight = false;
    _previousButtonState = false;
}