/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    21/9/17
/// \brief   Head Up Display showing the score, player lives
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_HUD_HPP
#define PROJECT_HUD_HPP

#include "SFML/Graphics.hpp"
#include "ResourceHolder.hpp"
#include "Score.hpp"
#include "PlayerShip.hpp"
#include "common.hpp"

////////////////////////////////////////////////////////////
/// \brief HUD class, to inform the user of remaining lives and other game information
///
/// Sources information from the score object from game
///
/// \see Score.hpp
////////////////////////////////////////////////////////////
class HUD
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief HUD class constructor. Initiated on game start.
    ///
    /// \param resolution stores the size of the screen so the HUD knows where to position itself
    /// \param renderWindow enables the HUD to draw directly onto the game screen
    /// \param fontHolder is used to pass the required fonts to the HUD
    /// \param score object enables the HUD to display the current game score, calculated and stored in score object
    /// \param playerShip provides the playerShip state to the HUD, so the player can see if his is alive/dead/invulnerable
    ///
    /// \see sf::RenderWindow
    /// \see sf::Vector2i
    /// \see PlayerShip.hpp
    ////////////////////////////////////////////////////////////
    HUD(const sf::Vector2i resolution,
        sf::RenderWindow &renderWindow,
        const FontHolder &fontHolder,
        const Score &score,
        const PlayerShip &playerShip);
    ////////////////////////////////////////////////////////////
    /// \brief appends the HUD to the current game renderWindow for the current lives and game score
    ////////////////////////////////////////////////////////////
    void draw();

private:
    ////////////////////////////////////////////////////////////
    /// \brief vector to store the game resultion, to enable the HUD to know its internal deterministically generated dimensions
    ////////////////////////////////////////////////////////////
    const sf::Vector2i _resolution;

    ////////////////////////////////////////////////////////////
    /// \brief reference to the main game renderWindow, to enable the HUD to draw itself over the main game window
    ////////////////////////////////////////////////////////////
    sf::RenderWindow& _renderWindow;
    ////////////////////////////////////////////////////////////
    /// \brief reference to the main font holder, to give the HUD access to its required fonts
    ////////////////////////////////////////////////////////////
    const FontHolder& _fonts;

    ////////////////////////////////////////////////////////////
    /// \brief reference to the main score object, so the HUD to draw the latest player score
    ////////////////////////////////////////////////////////////
    const Score& _score;

    ////////////////////////////////////////////////////////////
    /// \brief reference to the main playerShip, the so HUD can know the ship current state.
    ////////////////////////////////////////////////////////////
    const PlayerShip& _playerShip;
};

#endif //PROJECT_HUD_HPP
