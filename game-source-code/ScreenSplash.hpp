/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/10
/// \brief   Simple Splash Screen
///
/// Class interface for showing a splash screen with information on how to play the game
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_SPLASHSCREEN_H
#define PROJECT_SPLASHSCREEN_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "Screen.hpp"
#include "Starfield.hpp"

////////////////////////////////////////////////////////////
/// \brief A Splashscreen, with information on how to play
/// the game, titles, controls and version information
///
////////////////////////////////////////////////////////////
class ScreenSplash : public Screen
{
public:

////////////////////////////////////////////////////////////
/// \brief Shows the Splash screen
///
/// \param window The sf:Window object to draw and render to
/// \param resourceMapper The resourceMapper containing assets for the splashscreen
///
/// \see sf::Window
/// \see ResourceMapper
///
////////////////////////////////////////////////////////////
    int draw(sf::RenderWindow &window,
             const TextureHolder &textureHolder,
             const FontHolder &fontHolder,
             const sf::Vector2i resolution,
             const Score &score) override;

};

#endif //PROJECT_SPLASHSCREEN_H