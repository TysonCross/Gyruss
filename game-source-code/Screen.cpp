/////////////////////////////////////////////////////////////////////
/// \brief   Base class implementation for a "Screen"
///
/// A screen is an additional graphical interface in the game which
/// provides information about the game, before/after playing the game
/////////////////////////////////////////////////////////////////////

#include "Screen.hpp"

void Screen::fadeTextInAndOut(sf::Text &text, sf::Color color, int frequency, sf::Clock& clock)
{
    float change = clock.getElapsedTime().asSeconds();
    change = common::radToDegree(common::angleFilter(change));
    auto i = fabs(sin(change*1/frequency));
    text.setFillColor(sf::Color(color.r,color.g,color.b,i*255));

}