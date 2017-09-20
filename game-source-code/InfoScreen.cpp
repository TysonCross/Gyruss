/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Description of file in project Project
///
/// Detailed description of file
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#include "InfoScreen.hpp"

void InfoScreen::fadeTextInAndOut(sf::Text &text, sf::Color color, int frequency, sf::Clock& clock)
{
    float change = float(clock.getElapsedTime().asSeconds());
    change = common::radToDegree(common::angleFilter(change));
    auto i = fabs(sin(change*1/frequency));
    text.setFillColor(sf::Color(i*color.r,i*color.g,i*color.b));
}