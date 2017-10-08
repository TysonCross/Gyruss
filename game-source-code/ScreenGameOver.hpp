/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    20/9/17
/// \brief   Description of file in project Project
///
/// Detailed description of file
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_GAMEOVERSCREEN_HPP
#define PROJECT_GAMEOVERSCREEN_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Screen.hpp"

////////////////////////////////////////////////////////////
/// \brief ScreenGameOver, to display the end game screen
///
/// Inherets from the screen base class
///
/// \see screen.hpp
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
    /// \see screen.hpp
    ////////////////////////////////////////////////////////////
    ScreenGameOver(bool gameOutcome);

    ////////////////////////////////////////////////////////////
    /// \brief draw function displays  the ScreenGameOver to the current display window.
    ///
    /// \param window current game RenderWindow, to enable to GameOverScreen to print directly to it
    /// \param textureHolder enables the GameOverScreen to access the end game background
    /// \param fontHolder stores the fonts needed for the end game screen
    /// \param resolution is used to calculate the game screen size, so the GameOverScreen can position content
    /// on diffrent screen sizes more effectivly and consistently
    /// \param score is used to get the player score, longest life, bullets fired, accuracy and enemies killed.
    ///
    /// \see ResourceHolder.hpp
    /// \see Score.hpp
    /// \see sf::RenderWindow
    /// \see sf:Vector2i
    ////////////////////////////////////////////////////////////
    virtual int draw(sf::RenderWindow &window,
                     const TextureHolder &textureHolder,
                     const FontHolder &fontHolder,
                     const sf::Vector2i resolution,
                     const Score &score);

private:
    ////////////////////////////////////////////////////////////
    /// \brief bool to store the current game won/lose state.
    ///
    /// \see ScreenGameOver()
    ////////////////////////////////////////////////////////////
    bool _wonGame;
};

#endif //PROJECT_GAMEOVERSCREEN_HPP

