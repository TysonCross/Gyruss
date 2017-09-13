/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/10
/// \brief   Simple Splash Screen
///
/// Implementation of showing a splash screen
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_SPLASHSCREEN_H
#define PROJECT_SPLASHSCREEN_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Game.hpp"
#include "common.hpp"


////////////////////////////////////////////////////////////
/// \brief A Splashscreen, with information on how to play
/// the game, titles, controls and version information
///
////////////////////////////////////////////////////////////
class SplashScreen
{
public:

////////////////////////////////////////////////////////////
/// \brief Shows the Splash screen
///
/// \param window The sf:Window object to draw and render to
/// \param resourceMapper The resourceMapper containing assets for the aplashscreen
///
/// \see sf::Window
/// \see ResourceMapper
///
////////////////////////////////////////////////////////////
    int show(sf::RenderWindow &window, ResourceMapper &resourceMapper, common::Resolution);
};

#endif //PROJECT_SPLASHSCREEN_H