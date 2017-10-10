/////////////////////////////////////////////////////////////////////
/// \brief   Check the FPS
/////////////////////////////////////////////////////////////////////

#include "FPS.hpp"

FPS::FPS() : _frame(0),
        _fps(0) {}

const unsigned int FPS::getFPS() const
{
    return _fps;
}

void FPS::update()
{
    if(_clock.getElapsedTime().asSeconds() >= 1.f)
    {
        _fps = _frame;
        _frame = 0;
        _clock.restart();
    }
    _frame++;
}