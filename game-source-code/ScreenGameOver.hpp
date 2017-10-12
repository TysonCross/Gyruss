/////////////////////////////////////////////////////////////////////
/// \brief  GameOver screen object definition
///
/// To display a splash screen upon game ending, either by fulfilling
/// the victory conditions (win screen), or by losing all lives (lose screen)
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_GAMEOVERSCREEN_HPP
#define PROJECT_GAMEOVERSCREEN_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Screen.hpp"

using sf::Vector2i;

////////////////////////////////////////////////////////////
/// \brief ScreenGameOver, to display the end game screen
///
/// Inherits from the screen base class
///
/// \see screen
////////////////////////////////////////////////////////////
class ScreenGameOver : public Screen
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief ScreenGameOver constructor, used to make the screenGameOver object for the main game loop.
    /// Calls the ABC constructors for the inheritance hierarchy from screen.
    ///
    /// Object has two states: if you want the game or lost and changes what is displayed accordingly
    ///
    /// \param gameOutcome defines if the player won or lost the game
    ///
    /// \see screen
    ////////////////////////////////////////////////////////////
    ScreenGameOver(bool gameOutcome);

    ////////////////////////////////////////////////////////////
    /// \brief Draw function displays  the ScreenGameOver to the current display window.
    ///
    /// \param window current game RenderWindow, to enable to GameOverScreen to print directly to it
    /// \param textureHolder enables the GameOverScreen to access the end game background
    /// \param fontHolder stores the fonts needed for the end game screen
    /// \param resolution is used to calculate the game screen size, so the GameOverScreen can position content
    /// on different screen sizes more effectively and consistently
    /// \param score is used to get the player score, longest life, bullets fired, accuracy and enemies killed.
    ///
    /// \see ResourceHolder
    /// \see Score
    /// \see [SFML/RenderWindow](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1RenderWindow.php)
    /// \see [SFML/Vector2](https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php)
    ////////////////////////////////////////////////////////////
    virtual int draw(sf::RenderWindow &window,
                     const TextureHolder &textureHolder,
                     const FontHolder &fontHolder,
                     const Vector2i resolution,
                     const Score &score);

private:
    ////////////////////////////////////////////////////////////
    /// \brief Bool to store the current game won/lose state.
    ///
    /// \see ScreenGameOver
    ////////////////////////////////////////////////////////////
    bool _wonGame;
};

#endif //PROJECT_GAMEOVERSCREEN_HPP

