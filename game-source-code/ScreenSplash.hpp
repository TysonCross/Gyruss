/////////////////////////////////////////////////////////////////////
/// \brief  Splash Screen
///
/// Class interface for showing a splash screen with information on how to play the game
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_SPLASHSCREEN_H
#define PROJECT_SPLASHSCREEN_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "Screen.hpp"
#include "Starfield.hpp"
#include <fstream>

using sf::Vector2i;

////////////////////////////////////////////////////////////
/// \brief A Splashscreen, with information on how to play
/// the game, titles, controls and version information
///
/// Inheritance relationship from screen
///
/// \see Screen
////////////////////////////////////////////////////////////
class ScreenSplash : public Screen
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Shows the Splash screen. This occurs at game launch.
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
    /// \see ResourceHolder
    /// \see [SFML/RenderWindow](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1RenderWindow.php)
    ////////////////////////////////////////////////////////////
    int draw(sf::RenderWindow &window,
             const TextureHolder &textureHolder,
             const FontHolder &fontHolder,
             const Vector2i resolution) override;

    ////////////////////////////////////////////////////////////
    /// \brief Function used to animate the spinning planet on the SplashScreen
    ///
    /// \param sprite The underlying planet is a sprite to enable the animation by  moving along the images that
    /// constitute the animation.
    /// \param rectArea defines the size of the planet to be drawn
    /// \param columns defines the number columns in the underlying graphic for animation
    /// \param rows defines the number rows in the underlying graphic for animation
    /// \param frameTotal defines how many frames are in the underlying graphic
    /// \param i is an incrementer to define what frame the draw process is currently on
    ///
    /// \see [SFML/Sprite](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Sprite.php)
    ////////////////////////////////////////////////////////////
    void animatePlanet(sf::Sprite &sprite,
                       sf::IntRect &rectArea,
                       int columns,
                       int rows,
                       int frameTotal,
                       int &i);
    ////////////////////////////////////////////////////////////
    /// \brief Function used to fetch the highscore.
    ///
    /// The highscore is fetched from disk when the game runs to
    /// show the player the previous highscores
    ////////////////////////////////////////////////////////////
    std::string getHighScore();

};

#endif //PROJECT_SPLASHSCREEN_H