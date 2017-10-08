/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Base class interface for a "Screen"
///
/// A screen is an additional graphical interface in the game which
/// provides information about the game, before/after playing the game
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
#include "Score.hpp"

////////////////////////////////////////////////////////////
/// \brief Virtual class that is used in other screen-like displays
/// such as ScreenSplash and ScreenGameOver
///
/// \see ScreenGameOver.hpp
/// \see ScreenGameOver.hpp
////////////////////////////////////////////////////////////
class Screen
{
public:

////////////////////////////////////////////////////////////
/// \brief Shows An info screen
///
/// \param window The sf:Window object to draw and render to
/// \param resourceMapper The resourceMapper containing assets for the infoscreen
/// \param resolution used to define where elements on the screen should be placed
///
/// \see sf::Window
/// \see ResourceMapper
////////////////////////////////////////////////////////////
    virtual int draw(sf::RenderWindow &window,
                     const TextureHolder &textureHolder,
                     const FontHolder &fontHolder,
                     const sf::Vector2i resolution)
    {return 0;}

    ////////////////////////////////////////////////////////////
    /// \brief Overloaded Draw function that is used if a score object as well as others are presented.
    /// Used in the case of the end of game screen.
    ///
    /// \param window The sf:Window object to draw and render to
    /// \param textureHolder The resourceMapper containing assets for the infoscreen
    /// \param fontHolder stores the fonts required for the screen object to function
    /// \param resolution used to define where elements on the screen should be placed
    /// \param score track the current game score as well as end game scores
    /// \param timeAlive is used to show the end game screen the longest life that the player had
    ///
    /// \see Score.pp
    /// \see ResourceHolder.hpp
    /// \see sf::Window
    /// \see ResourceMapper
    ////////////////////////////////////////////////////////////
    virtual int draw(sf::RenderWindow &window,
                     const TextureHolder &textureHolder,
                     const FontHolder &fontHolder,
                     const sf::Vector2i resolution,
                     const Score &score,
                     const sf::Clock &timeAlive)
    {return 0;}

protected:
////////////////////////////////////////////////////////////
/// \brief Loops through fading in and out a text object
///
/// \param text The sf:Text object to fade in and out
/// \param color The sf::Color to fade up to
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
