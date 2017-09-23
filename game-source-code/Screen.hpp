/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Description of file in project Project
///
/// Detailed description of file
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_INFOSCREEN_HPP
#define PROJECT_INFOSCREEN_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include "ResourceHolder.hpp"

class Screen
{
public:

////////////////////////////////////////////////////////////
/// \brief Shows An info screen
///
/// \param window The sf:Window object to draw and render to
/// \param resourceMapper The resourceMapper containing assets for the infoscreen
///
/// \see sf::Window
/// \see ResourceMapper
///
////////////////////////////////////////////////////////////
    virtual int show(sf::RenderWindow &window,
             const TextureHolder &textureHolder,
             const FontHolder &fontHolder,
             const sf::Vector2i)=0;

protected:
////////////////////////////////////////////////////////////
/// \brief Loops through fading in and out a text object
///
/// \param text The sf:Text object to fade in and out
/// \param color The sf::Color to fade up to
/// \param frequency The frequency of the fade
/// \param frequency The frequency of the fade
/// \param clock A changing value to alter the time step
///
/// \see sf:Text
/// \see sf::Color
////////////////////////////////////////////////////////////
    virtual void fadeTextInAndOut(sf::Text &text,
                          sf::Color color,
                          int frequency,
                          sf::Clock &clock);

};

#endif //PROJECT_INFOSCREEN_HPP
