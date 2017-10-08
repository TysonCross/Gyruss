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
#include <fstream>

////////////////////////////////////////////////////////////
/// \brief A Splashscreen, with information on how to play
/// the game, titles, controls and version information
///
/// Inheritance relationship from screen
///
/// \see Screen.hpp
////////////////////////////////////////////////////////////
class ScreenSplash : public Screen
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Shows the Splash screen. This occures at game launch.
    ///
    /// \param window The sf:Window object to draw and render to
    /// \param textureHolder stores the images needed for the splash screen,
    /// such as the background and keyboard bindings image
    /// \param fontHolder is used to store the fonts needed for the splash screen
    /// \param resolution is needed to determine where to place SplashScreen objects
    ///
    /// \return an int is returned to inform the game object what occurred on
    /// the splashScreen: 1 game closed, 0 game continue
    ///
    /// \see ResourceHolder.hpp
    ////////////////////////////////////////////////////////////
    int draw(sf::RenderWindow &window,
             const TextureHolder &textureHolder,
             const FontHolder &fontHolder,
             const sf::Vector2i resolution);

    ////////////////////////////////////////////////////////////
    /// \brief Function used to animate the spinning planet on the SplashScreen
    ///
    /// \param The underlying planet is a sprite to enable the animation by  moving along the images that
    /// constitute the animation.
    /// \param rectArea defines the size of the planet to be drawn
    /// \param columns defines the number columns in the underlying graphic for animation
    /// \param rows defines the number rows in the underlying graphic for animation
    /// \param frameTotal defines how many frames are in the underlying graphic
    /// \param i is an incrementer to define what frame the draw process is currently on
    ////////////////////////////////////////////////////////////
    void animatePlanet(sf::Sprite &sprite,
                       sf::IntRect &rectArea,
                       int columns,
                       int rows,
                       int frameTotal,
                       int &i);
    ////////////////////////////////////////////////////////////
    /// \brief Function used to fetch the highscore from disk when the game runs to show the player the
    /// previous highscores
    ////////////////////////////////////////////////////////////
    std::string getHighScore();

};

#endif //PROJECT_SPLASHSCREEN_H